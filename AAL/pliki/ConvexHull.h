#include <iostream>
#include "Facet.h"
#include <vector>
using namespace std;

class ConvexHull {

public:
	int x0, y0, z0, r;
	vector <Vertex> vertices;
	vector <Facet> facets;

public:
	ConvexHull();
	~ConvexHull();
	ConvexHull(vector <Point> points);
	Vertex& getVertex(int i) { 
		return vertices[i].getVertex();
	}
	void buildHull(); 
	virtual void buildAlgorithm() {
	}
	void readFromFile(string s);
	void writeToFile(string s);
	double det(int n, int w, int * WK, double ** A);
	double volume(Facet f, Vertex v);

};