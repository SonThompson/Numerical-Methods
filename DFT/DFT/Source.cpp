#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <chrono>

#define PI 3.1415926535897932

//ƒискретное преобразование ‘урье
void DFT(const std::vector<std::complex<double>>& Data, std::vector<std::complex<double>>& Result)
{
	int N = Data.size();
	Result.clear(); Result.resize(N);
	std::complex<double> Exp;
	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < N; m++)
		{
			Exp._Val[0] = cos(-2.0 * PI * m * n / N);
			Exp._Val[1] = sin(-2.0 * PI * m * n / N);
			Result[n] += Data[m] * Exp;
			/*Result[n]._Val[0] += Data[m]._Val[0] * Exp._Val[0];
			Result[n]._Val[1] += Data[m]._Val[1] * Exp._Val[1];*/

		}
	}
	//ƒл€ пункта 6 (обнуление шумов)
	Result[146] = 0.0;
	Result[N - 146] = 0.0;
}

//ќбратное дискретное преобразование ‘урье
void IDFT(const std::vector<std::complex<double>>& Data, std::vector<std::complex<double>>& Result)
{
	int N = Data.size();
	DFT(Data, Result);
	std::complex<double> Exp;
	std::vector<std::complex<double>> IDFT_Data;
	IDFT_Data.resize(N);
	for (int n = 0; n < N; n++)
	{
		IDFT_Data[n] = 0.0;
		for (int m = 0; m < N; m++)
		{
			Exp._Val[0] = cos(2.0 * PI * m * n / N);
			Exp._Val[1] = sin(2.0 * PI * m * n / N);
			IDFT_Data[n] += Result[m] * Exp;
			/*IDFT_Data[n]._Val[0] += Result[m]._Val[0] * Exp._Val[0];
			IDFT_Data[n]._Val[1] += Result[m]._Val[1] * Exp._Val[1];*/
		}
		IDFT_Data[n] /= double(N);
	}
	Result = IDFT_Data;
}


//------------------------------------------------------------------------------------------

//быстрое преобразование (длина вектора - чЄтное число)
//Data - входные данные, Result - массив результата
void FFT(const std::vector<std::complex<double>>& Data, std::vector<std::complex<double>>& Result)
{
	int N = Data.size(), M = N / 2;
	Result.clear(); Result.resize(N);
	std::complex<double> Exp, U, V;

	for (int m = 0; m < M; m++)
	{
		U._Val[0] = 0.0; U._Val[1] = 0.0;
		V._Val[0] = 0.0; V._Val[1] = 0.0;
		for (int n = 0; n < M; n++)
		{
			Exp._Val[0] = cos(-2.0 * PI * m * n / M);
			Exp._Val[1] = sin(-2.0 * PI * m * n / M);
			U += Data[2 * n] * Exp;
			V += Data[2 * n + 1] * Exp;
		}

		Exp._Val[0] = cos(-2.0 * PI * m / N);
		Exp._Val[1] = sin(-2.0 * PI * m / N);
		Result[m] = U + Exp * V;
		Result[m + M] = U - Exp * V;
	}
}



//обратное быстрое преобразование (длина вектора чЄтна€)
//Data - входные данные, Result - массив результата
void IFFT(const std::vector<std::complex<double>>& Data, std::vector<std::complex<double>>& Result)
{
	int N = Data.size();
	FFT(Data, Result);
	std::complex<double> Val;
	for (int i = 1; i <= N / 2; i++)
	{
		Val = Result[i];
		Result[i] = Result[N - i] / double(N);
		Result[N - i] = Val / double(N);
	}

	Result[0] /= double(N);
}

//------------------------------------------------------------------------------------------


//¬ычисление амплитуды
void Amplitude_Cal(const std::vector<std::complex<double>>& Data, std::vector<double>& Amplitude)
{
	int N = Data.size();
	for (int i = 0; i < N; i++)
	{
		Amplitude[i] = sqrt(pow(Data[i]._Val[0], 2) + pow(Data[i]._Val[1], 2));
		if (abs(Amplitude[i]) < 1e-7)
			Amplitude[i] = 0;
	}
}

//------------------------------------------------------------------------------------------

int main()
{
	//мерность векторного пространства
	int N = 512;

	//TRY - переменна€ отвечающа€ за количество повторений операций. Ќужна дл€ замера времени работы
	int TRY = 1;

	//Z - данные, DFT_Data - пр€мое DFT, IDFT_Data - обратное DFT, FFT_Data - быстрое, IFFT_Data - обратное быстрое
	std::vector<std::complex<double>> Z(N), DFT_Data(N), IDFT_Data(N), FFT_Data(N), IFFT_Data(N);

	//Amplitude - амплитуда, Phase - фаза
	std::vector<double> Amplitude(N), Phase(N);

	//заполнение данных (вещественна€ гармоника с частотой 100)
	for (int i = 0; i < N; i++)
	{
		Z[i]._Val[0] = /*91 - 0.61 * cos(2 * PI * i * 394 / N + PI / 4);*/cos(2 * PI * i / N) + 0.01 * cos(2 * PI * i * 146 / N);
		Z[i]._Val[1] = 0;
	}

	//пр€мое дискретное преобразование ‘урье
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < TRY; i++) {
		DFT(Z, DFT_Data);
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	double time = std::chrono::duration<double>((t2 - t1) / double(TRY)).count();
	std::cout << "Time of DFT: " << time << std::endl;

	//обратное дискретное преобразование ‘урье
	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < TRY; i++) {
		IDFT(Z, IDFT_Data);
	}
	t2 = std::chrono::high_resolution_clock::now();
	time = std::chrono::duration<double>((t2 - t1) / double(TRY)).count();
	std::cout << "Time of IDFT: " << time << std::endl;

	//пр€мое быстрое преобразование
	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < TRY; i++) {
		FFT(Z, FFT_Data);
	}
	t2 = std::chrono::high_resolution_clock::now();
	time = std::chrono::duration<double>((t2 - t1) / double(TRY)).count();
	std::cout << "Time of FFT: " << time << std::endl;

	//обратное преобразование
	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < TRY; i++) {
		IFFT(FFT_Data, IFFT_Data);
	}
	t2 = std::chrono::high_resolution_clock::now();
	time = std::chrono::duration<double>((t2 - t1) / double(TRY)).count();
	std::cout << "Time of IFFT: " << time << std::endl;

	//ѕоиск амплитуды
	Amplitude_Cal(DFT_Data, Amplitude);

	//ѕоиск фазы
	for (int i = 0; i < N; i++)
	{
		if (abs(DFT_Data[i].real()) > 1e-7 && abs(DFT_Data[i].imag()) > 1e-7)
			Phase[i] = arg(DFT_Data[i]);
	}

	//вывод результата
	int SETW = 22;

	std::cout << std::left << std::setw(SETW) << "Number"
		<< std::left << std::setw(SETW) << "Re(Z)"
		/*<< std::left << std::setw(SETW) << "Im(Z)"*/
		<< std::left << std::setw(SETW) << "Re(DFT_Data)"
		<< std::left << std::setw(SETW) << "Im(DFT_Data)"
		<< std::left << std::setw(SETW) << "Amplitude"
		<< std::left << std::setw(SETW) << "Phase"
		/*<< std::left << std::setw(SETW) << "Re(FFT_Data)"
		<< std::left << std::setw(SETW) << "Im(FFT_Data)"*/
		/*<< std::left << std::setw(SETW) << "Re(IDFT_Data)"
	   << std::left << std::setw(SETW) << "Im(IDFT_Data)"
	   << std::left << std::setw(SETW) << "Re(IFFT_Data)"
	   << std::left << std::setw(SETW) << "Im(IFFT_Data)"*/ << std::endl;

	for (int i = 0; i < N; i++)
	{
		//условие дл€ просмотра частот только не нулевых амплитудных и фазовых спектров
		/*if (Amplitude[i] != 0 || Phase[i] != 0)*/
			std::cout << std::left << std::setw(SETW) /*<< i*/
			<< std::left << std::setw(SETW) /*<< Z[i].real()*/
			/*<< std::left << std::setw(SETW) << Z[i].imag()*/
			/*<< std::left << std::setw(SETW) << DFT_Data[i].real()
			<< std::left << std::setw(SETW) << DFT_Data[i].imag()
			<< std::left << std::setw(SETW) << Amplitude[i]
			<< std::left << std::setw(SETW) << Phase[i]*/
			/*<< std::left << std::setw(SETW) << FFT_Data[i].real()
			<< std::left << std::setw(SETW) << FFT_Data[i].imag()*/
			<< std::left << std::setw(SETW) << IDFT_Data[i].real()
		  /* << std::left << std::setw(SETW) << IDFT_Data[i].imag()*/
		   /*<< std::left << std::setw(SETW) << IFFT_Data[i].real()*/
		   /*<< std::left << std::setw(SETW) << IFFT_Data[i].imag()*/ << std::endl;
	}
}