/*
	*
	* Martyna Wi�cek - Pow�oka wypuk�a
	*
*/
#pragma once
#include <iostream>
#include "Point.h"
using namespace std;

class Vertex : public Point {

private:
	bool visited;

public:
	/*konstruktory*/
	Vertex();

	~Vertex();

	Vertex(const Vertex &v);

	Vertex(double x, double y, double z, bool b);

	/*funkcja sprawdzaj�ca, czy wierzcho�ek by� odwiedzany*/
	bool isVisited();

	/*funkcja sprawdzaj�ca czy 2 wierzcho�ki s� wsp�liniowe*/
	bool isColinear(Vertex a, Vertex b);

	/*funkcja zwracaj�ca wska�nik do wierzcho�ka*/
	Vertex& getVertex() { return *this; }

	/*funkcja do ustawiania warto�ci zmiennej visited*/
	void setVisited(bool b);

	/*przeci��one operatory*/
	bool operator ==( const Vertex & v )const;

	bool operator<(const Vertex& v) const;

};