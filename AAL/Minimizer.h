/*
	*
	* Martyna Wi�cek - Pow�oka wypuk�a
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

	/*�rodek ci�ko�ci obiektu dla kt�rego wygenerowali�my punkty*/
	double x0, y0, z0, r;
	
	/*mapa do wokselizacji*/
	map <string,vector<Point>> min_cubes;

	/*2 wektory jeden z wczytanymi danymi, drugi z gotowymi*/
	vector <Point> base_set;
	vector <Point> final_set;
	
	/*na ile sze�cian�w zostanie podzielony zbi�r = accuracy^3*/
	int accuracy;

public:

	/*konstruktory*/
	Minimizer();

	~Minimizer();

	Minimizer(int accuracy);

	/*zwr�� dok�adno�� oblicze�*/
	int getAccuracy();

	/*wczytaj z pliku*/
	void readFromFile(string s);

	/*wczytaj do pliku*/
	void writeToFile(string s);

	/*inicjalizacja kluczy w mapie*/
	void initializeKeys();

	/*podzia� obszaru na woksele*/
	void divideIntoCubes();

	/*znalezienie punkt�w po�rednich dla ka�dego woksela*/
	void findAveragePoints();

};