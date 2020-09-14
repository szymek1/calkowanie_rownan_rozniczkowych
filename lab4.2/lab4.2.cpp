#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rk4.h"

double fun1(double t, double y); //funkcja prawych stron
double* T(double* t, double h, int n); //funkcja licząca czas
double* Analytics(double* t, double n, double h); //liczy wwartosc analityczna dla zmieniajacych sie t i n
double errorE(double* e, double* a, int i); //liczy blad metody Eulera
double errorRK(double* rk, double* a, int j); //liczy blad metody RK
double* Euler(double* t, double n, double h, double (*fun)(double, double)); //liczy metoda Eulera dla zmieniajacych sie t i n;

int main()
{
	//zadanie 1, metoda Eulera

	int n = 16, lambda = 2;
	double h; //krok calkowania
	double y0 = 0.8;

	double* t;
	double* ya;
	double* ye;

	t = (double*)malloc(n * sizeof(double));
	ya = (double*)malloc(n * sizeof(double));
	ye = (double*)malloc(n * sizeof(double));
	t[0] = 0.5; //t0
	t[15] = 10.5; //tk
	h = (t[15] - t[0]) / n;
	T(t, h, n); //wypełnienie tablicy ze zmienna czasu
	ya = Analytics(t, n, h); //rozwiązanie analityczne
	ye = Euler(t, n, h, fun1);
	//rozwiązanie analityczne
	for (int i = 0; i < n; i++)
	{
		printf("t(%d)= %lf\tya(%d)= %lf\n", i, t[i], i, ya[i]);
	}

	//metoda Eulera
	printf("\n");
	ye[0] = y0;
	for (int i = 0; i < n; i++)
	{
		//ye[i + 1] = ye[i] + h * fun1(t[1], ye[i]);
		printf("ye(%d)= %lf\n", i, ye[i]);
	}

	//zadanie 2, metoda RK

	printf("\n");
	double* yk = (double*)malloc(n * sizeof(double));
	yk[0] = y0;
	for (int i = 0; i < n; i++)
	{
		yk[i + 1] = rk4(t[i], yk[i], h, fun1);
		printf("yk(%d)= %lf t(%d)= %lf\n", i, yk[i], i, t[i]);
	}

	//zadanie 3
	//wartosc yi oraz ti są wyświetlane już w dwóch powyższych zadaniach zarówno dla metody Eulera, jak i RK tutaj będą wyświetlone tylko błedy

	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("Blad dla metody Eulera przy t(%d)= %lf, wynosi: %lf\n", i, t[i], errorE(ye, ya, i));
		printf("Blad dla metody RK przy t(%d)= %lf, wynosi: %lf\n", i, t[i], errorRK(yk, ya, i));
		printf("\n");
	}


	free(ye);
	free(ya);
	free(t);
	return 0;
}

double fun1(double t, double y)
{
	double lambda = 2;
	return lambda * y;
}
double* T(double* t, double h, int n)
{
	for (int i = 0; i < n; i++)
	{
		t[i] = t[0] + (h * i);
	}
	return t;
}
double* Analytics(double* t, double n, double h)
{
	double y0 = 0.8;
	int lambda = 2;
	double* analytics = (double*)malloc(n * sizeof(double));

	for (int i = 0; i < n; i++)
	{
		analytics[i] = y0 + h * exp(lambda * (t[i] - t[0]));
	}

	return  analytics;
	free(analytics);
}
double errorE(double* e, double* a, int i)
{
	return (fabs(e[i] - a[i]) / fabs(a[i]));
}
double errorRK(double* rk, double* a, int j)
{
	return (fabs(rk[j] - a[j]) / fabs(a[j]));
}
double* Euler(double* t, double n, double h, double (*fun)(double, double))
{
	double* euler = (double*)malloc(n * sizeof(double));
	euler[0] = 0.8; //y0

	for (int i = 0; i < n; i++)
	{
		euler[i + 1] = euler[i] + h * fun1(t[1], euler[i]);
	}

	//double bladE = errorE(euler, Analytics(t, n, h), n - 1);
	return euler;
	free(euler);
}