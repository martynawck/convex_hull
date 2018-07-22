#pragma once
#include <iostream>
#include "Facet.h"
#include <vector>
#include <queue>
#include <map>
using namespace std;

class ConvexHull {

public:

	/*œrodek ciê¿koœci bry³y, dla której badamy otoczkê*/
	int x0, y0, z0, r;

	/*wierzcho³ki i krawêdzie*/
	vector <Vertex> vertices;
	vector <Facet> facets;

public:

	/*konstruktory*/
	ConvexHull();
	
	~ConvexHull();
	
	ConvexHull(vector <Point> points);

	/*stwórz otoczkê za pomoc¹ algorytmu przyrostowego*/
	double buildIncrementalHull(string s1, string s2);

	/*stwórz otoczkê za pomoc¹ quick hull*/
	double buildQuickHull(string s1, string s2);

	/*algorytm przyrostowy z liczeniem czasu*/
	void incrementalHull();
	
	/*algorytm quickhull z liczeniem czasu*/
	void quickHull();
	
	void readFromFile(string s);
	
	void writeToFile(string s);

};