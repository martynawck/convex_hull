#pragma once
#include <iostream>
#include "Point.h"
#include <vector>
#include <map>
using namespace std;

class Minimizer {

public:
	double x0, y0, z0, r;
	map <string,vector<Point>> min_cubes;
	vector <Point> base_set;
	vector <Point> final_set;
	int accuracy;

public:

	Minimizer();
	~Minimizer();
	Minimizer(int accuracy);
	vector<Point> getBaseSet();
	vector<Point> getFinalSet();
	int getAccuracy();
	void readFromFile(string s);
	void writeToFile(string s);
	void initializeKeys();
	void divideIntoCubes();
	void findAveragePoints();

};