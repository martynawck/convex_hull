#pragma once
#include <iostream>
#include "Vertex.h"
using namespace std;


class Edge {

private:
	/*2 wierzchołki*/
	Vertex v1; 
	Vertex v2; 

	/*długość*/
	double length;

public:

	/*konstruktory*/
	Edge();

	~Edge();

	Edge(Vertex v1, Vertex v2);

	/*pobranie 2 wierzchołków*/
	Vertex getV1() const;

	Vertex getV2()const;

	/*pobranie długości*/
	double getLength();

	/*operatory*/
	bool operator<(const Edge& e )const;

	bool operator == ( const Edge & e )const;

};