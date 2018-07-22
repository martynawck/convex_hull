/*
	*
	* Martyna Wi�cek - Pow�oka wypuk�a
	*
*/
#pragma once
#include <iostream>
#include "Vertex.h"
using namespace std;


class Edge {

private:
	/*2 wierzcho�ki*/
	Vertex v1; 
	Vertex v2; 

	/*d�ugo��*/
	double length;

public:

	/*konstruktory*/
	Edge();

	~Edge();

	Edge(Vertex v1, Vertex v2);

	/*pobranie 2 wierzcho�k�w*/
	Vertex getV1() const;

	Vertex getV2()const;

	/*pobranie d�ugo�ci*/
	double getLength();

	/*operatory*/
	bool operator<(const Edge& e )const;

	bool operator == ( const Edge & e )const;

};