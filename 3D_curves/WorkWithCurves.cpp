#include "Curves.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <memory>
#include <algorithm>
#include <omp.h>

double makeRandomDouble()
{
	return static_cast<double>(rand() % 10000 + 1) / 100;
}

int main()
{
	std::vector<std::shared_ptr<CCurve>> aCurve;
	const size_t nCurve = 25;
	aCurve.reserve(nCurve);
	//Random filling curveContainer with different curves with various parameters.
	srand(time(NULL));
	for(int i = 0; i < nCurve; i++)
	{
		switch (rand() % 3) 
		{
		case 0:
			aCurve.push_back(std::make_shared<CCircle>(makeRandomDouble()));
			break;
		case 1:
			aCurve.push_back(std::make_shared<CEllipse>(makeRandomDouble(), makeRandomDouble()));
			break;
		case 2:
			aCurve.push_back(std::make_shared<CHelix>(makeRandomDouble(), makeRandomDouble()));
		}
	}

	// Compute points and derivatives per parameter t=PI/4 of various curves from container.
	int num = 1;
	for(const auto& pCurve : aCurve)
	{
		D3 pt = pCurve->getPoint(M_PI / 4);
		D3 der = pCurve->getDerivative(M_PI / 4);
		std::cout << num << ". ";
		std::cout << " point at t = PI/4 :\t\t " << pt.x << "  " << pt.y << "  " << pt.z << "\n   ";
		std::cout << " derivative at t = PI/4 :\t" << der.x << "  " << der.y << "  " << der.z << "\n\n";
		++num;
	}

	std::vector<std::shared_ptr<CCircle>> aCircle;
	for (const auto& curve : aCurve)
	{
		if(auto pCircle = std::dynamic_pointer_cast<CCircle>(curve); pCircle != nullptr)
			aCircle.push_back(std::shared_ptr<CCircle>(pCircle));
	}

	//Sorting of circles from aCircle by radius.
	auto compare = [](const std::shared_ptr<CCircle>& leftCircle, const std::shared_ptr<CCircle>& rightCircle) {
		return leftCircle->getRadius() < rightCircle->getRadius();
	};
	std::sort(aCircle.begin(), aCircle.end(), compare);

	//Computing total sum of radii of circles from aCircle.
	double sum = 0;
	const int nCirc = aCircle.size();
	if(nCirc > 1)
	{
		std::vector<double> vec(nCirc / 2);
#pragma omp parallel for shared(aCircle, vec, nCirc)
		for(int i = 0; i < nCirc / 2; ++i)
			vec[i] = aCircle[i]->getRadius() + aCircle[nCirc - i - 1]->getRadius();

		if(nCirc % 2 == 1)
			vec[0] += aCircle[nCirc / 2]->getRadius();

		while(vec.size() > 1)
		{
			const int nVec = vec.size();
#pragma omp parallel for shared(vec, nVec)
			for (int i = 0; i < nVec / 2; ++i)
				vec[i] = vec[i] + vec[nVec - i - 1];

			vec.resize(nVec / 2);
		}
		sum = vec[0];
	}
	else if(nCirc == 1)
	{
		sum = aCircle[0]->getRadius();
	}

	std::cout << "\nThe sum of all the radii of the second container: " << sum << "\n";
	return 0;
}