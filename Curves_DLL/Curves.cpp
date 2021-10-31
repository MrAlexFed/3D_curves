#include "pch.h"
#include "Curves.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

CCircle::CCircle(const double radius) : m_radius(radius)
{
	if (m_radius <= 0)
		throw std::invalid_argument("invalid_argument exception: Circle radius must be positive!\n");
}

// Calculate point on the circle corresponding the t parameter
D3 CCircle::getPoint(const double t) const
{
	D3 pnt;
	pnt.x = m_radius * cos(t);
	pnt.y = m_radius * sin(t);
	pnt.z = 0;
	return pnt;
}

// Calculate first derivative of the circle corresponding the t parameter
D3 CCircle::getDerivative(const double t) const
{
	D3 der;
	der.x = -m_radius * sin(t);
	der.y = m_radius * cos(t);
	der.z = 0;
	return der;
}

CEllipse::CEllipse(double radiusX, double radiusY) : m_radiusX(radiusX), m_radiusY(radiusY)
{
	if (m_radiusX <= 0 || m_radiusY <= 0)
		throw std::invalid_argument("invalid_argument exception: Ellipse radii must be positive!\n");
}

// Calculate point on the ellipse corresponding the t parameter
D3 CEllipse::getPoint(const double t) const
{
	D3 pt;
	pt.x = m_radiusX * cos(t);
	pt.y = m_radiusY * sin(t);
	pt.z = 0;
	return pt;
}

// Calculate first derivative of the ellipse corresponding the t parameter.
D3 CEllipse::getDerivative(const double t) const
{
	D3 der;
	der.x = -m_radiusX * sin(t);
	der.y = m_radiusY * cos(t);
	der.z = 0;
	return der;
}

CHelix::CHelix(const double radius, const double step) : m_radius(radius), m_step(step)
{
	if (m_radius <= 0)
		throw std::invalid_argument("invalid_argument exception: Helix radius must be positive!\n");
}

// Calculate point on the helix corresponding the t parameter
D3 CHelix::getPoint(const double t) const
{
	D3 pt;
	pt.x = m_radius * cos(t);
	pt.y = m_radius * sin(t);
	pt.z = m_step * t / (2 * M_PI);
	return pt;
}

// Calculate first derivative of the helix corresponding the t parameter
D3 CHelix::getDerivative(const double t) const
{
	D3 der;
	der.x = -m_radius * sin(t);
	der.y = m_radius * cos(t);
	der.z = m_step / (2 * M_PI);
	return der;
}