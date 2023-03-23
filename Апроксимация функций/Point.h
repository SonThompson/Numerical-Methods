#pragma once
#ifndef point_h
#define point_h
#include <iostream>

//точка
class Point
{
private:
	//координаты
	double X, Y, Z;
public:
	//конструктор
	Point(double x, double y, double z);

	//доступ к полям
	double x()const;
	double y()const;
	double z()const;
};

#endif
//class Point {
//private:
//	double X, Y, Z;
//public:
//	Point(const double x = 0, const double y = 0, const double z = 0) : X(x), Y(y), Z(z)
//	{ }
//	Point(const double x,const double y, const double z) : X(x), Y(y), Z(z)
//	{ }
//	void GetPoints() {
//		std::cout << "значениея x, y, z соответственно:";
//	}
//	double x()const { return X; }
//	double y()const { return Y; }
//	double z()const { return Z; }
//};