#pragma once
#include <iostream>
#include "Point.h"
#include <set>
#include <vector>
using namespace std;

class Generator {

private:

	/*œrodek ciê¿koœci bry³y, dla któryj chcemy generowac punkty*/
	double x0, y0, z0;

	/*promieñ od œrodka ciê¿koœci do p³aszczyzny otaczaj¹cej bry³ê*/
	double r;
	
	/*zbiór punktów wygenerowany*/

	vector <Point> generated_set;

public:

	/*konstruktory*/
	Generator();

	~Generator();
	
	/*funkcja generuj¹ca punkty w szeœcianie*/
	void generateInCube(int, double,double,double,double);
	
	/*funkcja generuj¹ca punkty w kuli*/
	void generateInSphere(int, double,double,double,double);
	
	/*funkcja generuj¹ca punkty na kuli*/
	void generateOnSphere(int, double,double,double,double);
	
	/*funkcja usuwaj¹ca punkty ze zbioru*/
	void clearSet();
	
	/*zapisz zbiór do pliku*/
	void writeToFile(string s);
	
	/*jak du¿y jest zbiór*/
	int getSize();
	/*
	void sortByX();
	
	void sortByY();
	
	void sortByZ();
	*/
};