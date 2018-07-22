#pragma once
#include <iostream>
#include "Point.h"
#include <set>
#include <vector>
using namespace std;

class Generator {

private:
	double x0, y0, z0;
	double r;
	vector <Point> generated_set;

public:
	Generator();
	~Generator();
	void generateInCube(int, double,double,double,double);
	void generateInSphere(int, double,double,double,double);
	void generateOnSphere(int, double,double,double,double);
	void clearSet();
	void writeToFile(string s);
	void readFromFile(string s);
	void onScreen();
	int getSize();
	void sortByX();
	void sortByY();
	void sortByZ();

};