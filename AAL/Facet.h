/*
	*
	* Martyna Wi�cek - Pow�oka wypuk�a
	*
*/
#pragma once
#include <iostream>
#include "Edge.h"
using namespace std;

class Facet {

private:
	
	/*tablica wierzcho�k�w i kraw�dzi*/
	Vertex v[3];
	Edge e[3];

	/*czy �ciana jest widzialna na zewn�trz otoczki*/
	bool visible;

public:

	/*konstruktory*/
	Facet();

	~Facet();

	Facet(Vertex v1, Vertex v2, Vertex v3);

	Facet (Edge e1, Edge e2, Edge e3);

	/*funkcja zwracaj�ca wierzcho�ki*/
	Vertex getV1()const;

	Vertex getV2()const;

	Vertex getV3()const;

	/*i kraw�dzie */
	Edge getE1() const;
	
	Edge getE2()const;
	
	Edge getE3()const;
	
	/*czy �ciana jest widzialna na zewn�trz otoczki*/
	bool getVisible();
	
	/*ustaw to samo co wy�ej*/
	void setVisible(bool b);

	/*funkcja zamieniaj�ca wsp�rz�dne na ci�g znak�w dla �atwiejszego rozpoznania przez map�*/
	string toString();

	/*czy 2 punkty s� po tej samej stronie �ciany - p�aszczyzny*/
	bool notSameSide(Vertex p, Vertex m);

	/*funkcja sprawdzaj�ca po kt�rej stronie p�aszczyzny jest punkt*/
	double halfSpace(Vertex ver);

	/*funkcja zwracaj�ca tablic� wsp�czynnik�w r�wnania p�aszczyzny*/
	double* ABCofEquation();

	/*funkcja sprawdzaj�ca wynik wstawienia punktu do r�wnania p�aszczyzny*/
	double vertexIntoEquation(Vertex p);

	/*funkcja obliczaj�ca odleg�o�� wierzcho�ka od p�aszczyzny*/
	double distanceFromVertex(Vertex p);

	/*przeci��ony operator*/
	bool operator<(const Facet& f )const;

};