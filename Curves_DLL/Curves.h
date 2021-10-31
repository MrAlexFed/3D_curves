#pragma once

#ifdef CURVESDLL_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

// Three dimencion coordinate.
struct MATHLIBRARY_API D3
{
	double x;
	double y;
	double z;
};

// Virtual base class of curves.
class MATHLIBRARY_API CCurve
{
public:
	virtual D3 getPoint(const double t) const = 0;
	virtual D3 getDerivative(const double t) const = 0;
	virtual ~CCurve() {}
};

class MATHLIBRARY_API CCircle : public CCurve
{
public:
	CCircle(double radius);
	D3 getPoint(const double t) const override;
	D3 getDerivative(const double t) const override;
	double getRadius() const { return m_radius; }

private:
	double m_radius;
};

class MATHLIBRARY_API CEllipse : public CCurve
{
public:
	CEllipse(double radiusX, double radiusY);
	D3 getPoint(const double t) const override;
	D3 getDerivative(const double t) const override;

private:
	// represents radius of Ellipse along X axis
	double m_radiusX;

	// represents radius of Ellipse along Y axis.
	double m_radiusY;
};

class MATHLIBRARY_API CHelix : public CCurve {

public:
	CHelix(double radius, double step);
	D3 getPoint(const double t) const override;
	D3 getDerivative(const double t) const override;

private:
	double m_radius;

	// represents distance along Z axis between t and t+2*PI parameters.
	double m_step;
};