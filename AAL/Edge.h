/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
	*
*/
#pragma once
#include <iostream>
#include "Vertex.h"
using namespace std;


class Edge {

private:
	/*2 wierzcho³ki*/
	Vertex v1; 
	Vertex v2; 

	/*d³ugoœæ*/
	double length;

public:

	/*konstruktory*/
	Edge();

	~Edge();

	Edge(Vertex v1, Vertex v2);

	/*pobranie 2 wierzcho³ków*/
	Vertex getV1() const;

	Vertex getV2()const;

	/*pobranie d³ugoœci*/
	double getLength();

	/*operatory*/
	bool operator<(const Edge& e )const;

	bool operator == ( const Edge & e )const;

};