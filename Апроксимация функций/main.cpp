#include "Cubic_interpolation_spline.h"
#include "Generator.h"
#include <iostream>


int main()
{
	// f(x) = sin(x) [0; pi/6]

	double a = 0, b = 3.141592653589793 / 6;
	int parts = 5; // h = (b - a) / parts

	std::vector<double> values;
	std::vector<Point> grid = grid_partitions_generator(a, b, parts);
	for (auto& elem : grid)
	{
		values.push_back(sin(elem.x()));
	}

	Cubic_Interpolation_Spline_1d spline;
	spline.UpdateSpline(grid, values);

	//std::cout << "s(x), f(x):\n\n";
	//for (auto& elem : grid_partitions_generator(a /*+ 1e-2*/, b /*- 1e-2*/, parts + 17))
	//{
	//	std::cout << "(" << elem.x() << "," << spline.GetValue(elem)[0] << ")" << "\n";
	//	std::cout << "(" << elem.x() << "," << -sin(elem.x()) + cos(elem.x()) << ")" << "\n\n";
	//}

	//std::cout << "\ns'(x), f'(x):\n\n";
	//for (auto& elem : grid_partitions_generator(a /*+ 1e-2*/, b /*- 1e-2*/, parts + 17))
	//{
	//	std::cout << "(" << elem.x() << "," << spline.GetValue(elem)[1] << ")" << "\n";
	//	std::cout << "(" << elem.x() << "," << -cos(elem.x()) - sin(elem.x()) << ")" << "\n\n";
	//}

	//std::cout << "\ns\"(x), f\"(x):\n\n";
	//for (auto& elem : grid_partitions_generator(a /*+ 1e-2*/, b /*- 1e-2*/, parts + 17))
	//{
	//	std::cout << "(" << elem.x() << "," << spline.GetValue(elem)[2] << ")" << "\n";
	//	std::cout << "(" << elem.x() << "," << sin(elem.x()) - cos(elem.x()) << ")" << "\n\n";
	//}

	std::cout << "s(x), f(x):\n\n";
	for (auto& elem : grid_partitions_generator(a /*+ 1e-2*/, b /*- 1e-2*/, 21))
	{
		std::cout << elem.x() << "\t" << spline.GetValue(elem)[0] << "\t" << sin(elem.x())
			<< "\t" << spline.GetValue(elem)[1] << "\t" << cos(elem.x())
			<< "\t" << spline.GetValue(elem)[2] << "\t" << -sin(elem.x()) << "\n";
	}
}