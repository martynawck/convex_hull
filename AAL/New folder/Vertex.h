#pragma once
#include <iostream>
#include "Point.h"
using namespace std;

class Vertex : public Point {

private:
	bool visited;

public:
	Vertex();
	~Vertex();
	Vertex(const Vertex &v);
	Vertex(double x, double y, double z, bool b);
	bool isVisited();
	bool isColinear(Vertex a, Vertex b);
	Vertex& getVertex() { return *this; }
	void setVisited(bool b);
	bool operator ==( const Vertex & v )const;
	bool operator<(const Vertex& v) const;

};