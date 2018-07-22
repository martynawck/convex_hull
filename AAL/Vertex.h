/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
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

	/*funkcja sprawdzaj¹ca, czy wierzcho³ek by³ odwiedzany*/
	bool isVisited();

	/*funkcja sprawdzaj¹ca czy 2 wierzcho³ki s¹ wspó³liniowe*/
	bool isColinear(Vertex a, Vertex b);

	/*funkcja zwracaj¹ca wskaŸnik do wierzcho³ka*/
	Vertex& getVertex() { return *this; }

	/*funkcja do ustawiania wartoœci zmiennej visited*/
	void setVisited(bool b);

	/*przeci¹¿one operatory*/
	bool operator ==( const Vertex & v )const;

	bool operator<(const Vertex& v) const;

};