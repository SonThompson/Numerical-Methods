#pragma once
#ifndef Cubic_interpolation_spline_h
#define Cubic_interpolation_spline_h

#include <vector>
#include "Point.h"

class Spline
{
protected:

	std::vector<Point> num;

public:

	virtual void UpdateSpline(std::vector<Point>& points, std::vector<double>& values) = 0;
	virtual std::vector<double> GetValue(Point& point) = 0;
};

class Cubic_Interpolation_Spline_1d final : public Spline
{
private:

	std::vector<double> a, b, c, d;

public:

	void UpdateSpline(std::vector<Point>& points, std::vector<double>& values) override;
	std::vector<double> GetValue(Point& point) override;
};

#endif