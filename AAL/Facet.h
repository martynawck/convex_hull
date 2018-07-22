/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
	*
*/
#pragma once
#include <iostream>
#include "Edge.h"
using namespace std;

class Facet {

private:
	
	/*tablica wierzcho³ków i krawêdzi*/
	Vertex v[3];
	Edge e[3];

	/*czy œciana jest widzialna na zewn¹trz otoczki*/
	bool visible;

public:

	/*konstruktory*/
	Facet();

	~Facet();

	Facet(Vertex v1, Vertex v2, Vertex v3);

	Facet (Edge e1, Edge e2, Edge e3);

	/*funkcja zwracaj¹ca wierzcho³ki*/
	Vertex getV1()const;

	Vertex getV2()const;

	Vertex getV3()const;

	/*i krawêdzie */
	Edge getE1() const;
	
	Edge getE2()const;
	
	Edge getE3()const;
	
	/*czy œciana jest widzialna na zewn¹trz otoczki*/
	bool getVisible();
	
	/*ustaw to samo co wy¿ej*/
	void setVisible(bool b);

	/*funkcja zamieniaj¹ca wspó³rzêdne na ci¹g znaków dla ³atwiejszego rozpoznania przez mapê*/
	string toString();

	/*czy 2 punkty s¹ po tej samej stronie œciany - p³aszczyzny*/
	bool notSameSide(Vertex p, Vertex m);

	/*funkcja sprawdzaj¹ca po której stronie p³aszczyzny jest punkt*/
	double halfSpace(Vertex ver);

	/*funkcja zwracaj¹ca tablicê wspó³czynników równania p³aszczyzny*/
	double* ABCofEquation();

	/*funkcja sprawdzaj¹ca wynik wstawienia punktu do równania p³aszczyzny*/
	double vertexIntoEquation(Vertex p);

	/*funkcja obliczaj¹ca odleg³oœæ wierzcho³ka od p³aszczyzny*/
	double distanceFromVertex(Vertex p);

	/*przeci¹¿ony operator*/
	bool operator<(const Facet& f )const;

};