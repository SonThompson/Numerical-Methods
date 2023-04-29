#include "pch.h"
#include <iostream>
#include <iomanip>
#include <functional>
#include "Point.h"
#include "Integration_Scheme_Interval.h"

int main()
{
	//подынтегральная функция f(x) = exp^(-x/2)+1
	std::function<double(const Com_Methods::Point& P)> f =
		[](const Com_Methods::Point& P) { return exp(-P.x()/2) + 1; };
	//первообразная F(x) = x-2/exp^(x/2)
	std::function<double(const Com_Methods::Point& P)> F =
	[](const Com_Methods::Point& P) { return P.x() - 2/(exp(P.x()/2)); };

	//квадратурная формула Гаусс-3
	Com_Methods::Integration_Scheme_Interval Quadrature_Formula1(Com_Methods::Integration_Scheme::Gauss3);
	//квадратурная формула Трапеции
	Com_Methods::Integration_Scheme_Interval Quadrature_Formula2(Com_Methods::Integration_Scheme::Trap);

	//начало и конец отрезка интегрирования
	auto Begin = Com_Methods::Point(0, 0, 0);
	auto End = Com_Methods::Point(1, 0, 0);

	//число сегментов
	const int Num_Segments = 1;

	//точное значение интеграла (ф. Ньютона-Лейбница)
	double I_True = F(End) - F(Begin);

	long double I1[3];
	long double I2[3];
	for (int i = 0; i < 3; i++) {
		//численное значение интеграла методом Гаусс 3
		I1[i] = Quadrature_Formula1.Calculate_Integral(Begin, End, Num_Segments * pow(2,i), f);
		std::cout << std::fixed;
		std::cout << "h = " << (End.x() - Begin.x()) / double(Num_Segments * pow(2, i)) << std::setw(15);
		std::cout << "I = " << I1[i] << std::endl;
		std::cout << std::scientific;
		std::cout << "I_True = " << I_True << std::endl;
		std::cout << "|I - I_True| = " << fabs(I1[i] - I_True) << std::endl;
		
	}

	double Runge1 = fabs(pow(2, 6) * ((I1[1] - I1[2]) / (I1[0] - I1[2])) - 1);
	std::cout << "Runge = " << Runge1 << std::endl;
	if (Runge1 < 0.1) {
		double Rich1 = (I1[2] + ((I1[2] - I1[1]) / 63));
		std::cout << "Richardson = " << Rich1 << std::endl;
		if (fabs(Rich1 - I_True) < 1E-7) {
			std::cout << "Richardson - I_True = 0\n";
		}
		else {
			std::cout << "Richardson - I_True = " << Rich1 - I_True << std::endl;
		}
	}

	std::cout << "--------------------------------------------------------------------------" << std::endl << std::endl;

	std::vector<double> integral;

	for (int i = 0; i < 3; i++) {
		//численное значение интеграла методом Трапеции
		I2[i] = Quadrature_Formula2.Calculate_Integral(Begin, End, Num_Segments * pow(2, i), f);
		std::cout << "h = " << (End.x() - Begin.x()) / double(Num_Segments * pow(2, i)) << std::setw(15);
		std::cout << "I = " << I2[i] << std::endl;
		std::cout << std::scientific;
		std::cout << "I_True = " << I_True << std::endl;
		std::cout << "|I - I_True| = " << fabs(I2[i] - I_True) << std::endl;
	}

	double Runge2 = fabs(pow(2, 2) * ((I2[1] - I2[2]) / (I2[0] - I2[2])) - 1);
	std::cout << "Runge = " << Runge2 << std::endl;
	if (Runge2 < 0.1) {
		double Rich2 = (I2[2] + ((I2[2] - I2[1]) / 3));
		std::cout << "Richardson = " << Rich2 << std::endl;
		if (fabs(Rich2 - I_True) < 1E-7) {
			std::cout << "Richardson - I_True = 0\n";
		}
		else {
			std::cout << "Richardson - I_True = " << Rich2 - I_True << std::endl;
		}
	}
}
