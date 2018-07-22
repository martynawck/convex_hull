#pragma once
#include <iostream>
#include "Point.h"
#include <set>
#include <vector>
using namespace std;

class Generator {

private:

	/*�rodek ci�ko�ci bry�y, dla kt�ryj chcemy generowac punkty*/
	double x0, y0, z0;

	/*promie� od �rodka ci�ko�ci do p�aszczyzny otaczaj�cej bry��*/
	double r;
	
	/*zbi�r punkt�w wygenerowany*/

	vector <Point> generated_set;

public:

	/*konstruktory*/
	Generator();

	~Generator();
	
	/*funkcja generuj�ca punkty w sze�cianie*/
	void generateInCube(int, double,double,double,double);
	
	/*funkcja generuj�ca punkty w kuli*/
	void generateInSphere(int, double,double,double,double);
	
	/*funkcja generuj�ca punkty na kuli*/
	void generateOnSphere(int, double,double,double,double);
	
	/*funkcja usuwaj�ca punkty ze zbioru*/
	void clearSet();
	
	/*zapisz zbi�r do pliku*/
	void writeToFile(string s);
	
	/*jak du�y jest zbi�r*/
	int getSize();
	/*
	void sortByX();
	
	void sortByY();
	
	void sortByZ();
	*/
};