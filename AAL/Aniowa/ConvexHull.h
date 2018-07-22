#pragma once
#include <iostream>
#include "Facet.h"
#include <vector>
#include <queue>
#include <map>
using namespace std;

class ConvexHull {

public:

	/*�rodek ci�ko�ci bry�y, dla kt�rej badamy otoczk�*/
	int x0, y0, z0, r;

	/*wierzcho�ki i kraw�dzie*/
	vector <Vertex> vertices;
	vector <Facet> facets;

public:

	/*konstruktory*/
	ConvexHull();
	
	~ConvexHull();
	
	ConvexHull(vector <Point> points);

	/*stw�rz otoczk� za pomoc� algorytmu przyrostowego*/
	double buildIncrementalHull(string s1, string s2);

	/*stw�rz otoczk� za pomoc� quick hull*/
	double buildQuickHull(string s1, string s2);

	/*algorytm przyrostowy z liczeniem czasu*/
	void incrementalHull();
	
	/*algorytm quickhull z liczeniem czasu*/
	void quickHull();
	
	void readFromFile(string s);
	
	void writeToFile(string s);

};