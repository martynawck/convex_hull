/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
	*
*/
#pragma once
#include <iostream>
#include "Point.h"
#include <vector>
#include <map>
using namespace std;

class Minimizer {

public:

	/*œrodek ciê¿koœci obiektu dla którego wygenerowaliœmy punkty*/
	double x0, y0, z0, r;
	
	/*mapa do wokselizacji*/
	map <string,vector<Point>> min_cubes;

	/*2 wektory jeden z wczytanymi danymi, drugi z gotowymi*/
	vector <Point> base_set;
	vector <Point> final_set;
	
	/*na ile szeœcianów zostanie podzielony zbiór = accuracy^3*/
	int accuracy;

public:

	/*konstruktory*/
	Minimizer();

	~Minimizer();

	Minimizer(int accuracy);

	/*zwróæ dok³adnoœæ obliczeñ*/
	int getAccuracy();

	/*wczytaj z pliku*/
	void readFromFile(string s);

	/*wczytaj do pliku*/
	void writeToFile(string s);

	/*inicjalizacja kluczy w mapie*/
	void initializeKeys();

	/*podzia³ obszaru na woksele*/
	void divideIntoCubes();

	/*znalezienie punktów poœrednich dla ka¿dego woksela*/
	void findAveragePoints();

};