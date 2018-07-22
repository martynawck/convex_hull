#include <iostream>
#include "Edge.h"
using namespace std;

class Facet {

private:
	Vertex v[3];
	Edge e[3];
	bool visible;

public:
	Facet();
	~Facet();
	Facet(Vertex v1, Vertex v2, Vertex v3);
	Facet (Edge e1, Edge e2, Edge e3);
	Vertex getV1()const;
	Vertex getV2()const;
	Vertex getV3()const;
	Edge getE1() const;
	Edge getE2()const;
	Edge getE3()const;
	bool getVisible();
	void setVisible(bool b);
	bool notSameSide(Vertex p, Vertex m);
	double halfSpace(Vertex ver);
	double* ABCofEquation();
	double vertexIntoEquation(Vertex p);
//	bool halfSpace(Vertex ver, Vertex mid);
	bool operator<(const Facet& f )const;
	bool operator == ( const Facet & e )const;

};