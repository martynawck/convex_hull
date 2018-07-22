#include <iostream>
#include "Vertex.h"
using namespace std;


class Edge {

private:
	Vertex v1;
	Vertex v2;
	bool is_horizon;
	double length;

public:
	Edge();
	~Edge();
	Edge(Vertex v1, Vertex v2);
	Vertex getV1() const;
	Vertex getV2()const;
	bool getHorizon();
	double getLength();
	void setHorizon(bool b);
	bool operator<(const Edge& e )const;
	bool operator == ( const Edge & e )const;

};