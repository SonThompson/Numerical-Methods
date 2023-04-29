#include "pch.h"
#include "Integration_Scheme_Interval.h"

namespace Com_Methods
{
	//�����������: �� ���� ������� ��� ������������ �������
	Integration_Scheme_Interval::Integration_Scheme_Interval(Integration_Scheme_Type Type)
	{
		//���������� �������� ����� � ����� ��������������
		switch (Type)
		{
			//����� ������ �����-1
		case Gauss1:
		{
			Weight = { 2 };
			Points = { Point(0, 0, 0) };
			break;
		}
		
		    //����� ������ �����-2
		case Gauss2:
		{
			Weight = { 1, 1 };
			Points = { Point(-1.0/sqrt(3.0), 0, 0), Point(1.0/sqrt(3.0), 0, 0)};
			break;
		}

			//����� ������ �����-3
		case Gauss3:
		{
			Weight = { 5.0/9.0, 8.0/9.0, 5.0/9.0 };
			Points = { Point(-sqrt(3.0/5.0), 0, 0), Point(0, 0, 0), Point(sqrt(3.0/5.0), 0, 0)};
			break;
		}

			//����� ������ �����-4
		case Gauss4:
		{
			Weight = { (18.0 - sqrt(30)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };
			Points = { Point(-sqrt((3 + 2 * sqrt(6.0 / 5.0)) / 7.0), 0, 0),
					   Point(-sqrt((3 - 2 * sqrt(6.0 / 5.0)) / 7.0), 0, 0),
					   Point(-sqrt((3 - 2 * sqrt(6.0 / 5.0)) / 7.0), 0, 0),
					   Point(-sqrt((3 + 2 * sqrt(6.0 / 5.0)) / 7.0), 0, 0) };
			break;
		}

			//����� ������ �����-5
		case Gauss5: 
		{
			Weight = { (322.0 - 13.0 * sqrt(70.0)) / 900,
					   (322.0 + 13.0 * sqrt(70.0)) / 900,
					   128.0/225.0,
					   (322.0 + 13.0 * sqrt(70.0)) / 900,
					   (322.0 - 13.0 * sqrt(70.0)) / 900, };
			Points = { Point(-sqrt(5.0 + 2.0 * sqrt(10.0 / 7.0)) / 3.0, 0, 0),
					   Point(-sqrt(5.0 - 2.0 * sqrt(10.0 / 7.0)) / 3.0, 0, 0),
					   Point(0, 0, 0), 
					   Point( sqrt(5.0 - 2.0 * sqrt(10.0 / 7.0)) / 3.0, 0, 0),
					   Point( sqrt(5.0 + 2.0 * sqrt(10.0 / 7.0)) / 3.0, 0, 0) };
			break;
		}

			//����� ������ ��������
		case Trap:
		{
			Weight = { 1, 1 };
			Points = { Point(-1.0, 0, 0), Point(1.0, 0, 0) };
			break;
		}
		/*case Parab:
		{
			Weight = { 1.0 / 3.0, 4.0 / 3.0, 1.0 / 3.0 };
			Points = { Point()}
		}*/
		}
	}

	//����� ��� ���������� ������������ ���������: 
	//Begin � End - ������ � ����� ������� 
	//Num_Segments - ����� ���������
	//Func - ��������������� �������
	double Integration_Scheme_Interval::Calculate_Integral(
		const Point& Begin,
		const Point& End,
		int Number_Segments,
		const std::function<double(const Point& P)>& Func) const
	{
		//��������� (������������ �����)
		double Result = 0.0;
		//��������� ����� ��������
		double X0;
		//��� �� �������
		double h = (End.x() - Begin.x()) / Number_Segments;
		//����� �� ���� ��������� ���������
		for (int i = 0; i < Number_Segments; i++)
		{
			//��������� ����� ��������
			X0 = Begin.x() + i * h;
			//����� �� ����� ��������������
			for (int Integ_Point = 0; Integ_Point < Points.size(); Integ_Point++)
			{
				//������� � ������-�������� [-1, 1]
				auto P = Point(X0 + (1 + Points[Integ_Point].x()) * h / 2.0, 0, 0);
				Result += Weight[Integ_Point] * Func(P);
			}
		}
		//��������� ��������� � ������ �������� �� ������� [-1, 1] ��� ��� ���� ������� ������ � ��������� 
		return Result * (h / 2.0);
	}
}
