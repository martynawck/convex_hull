/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
	*
*/
#include <iostream>
#include "Edge.h"
#include <math.h>
using namespace std;

/*konstruktory itp*/
Edge::Edge() { }


Edge::~Edge() { }


Edge::Edge(Vertex v1, Vertex v2) {

	this->v1 = v1;
	this->v2 = v2;
	this->length = getLength();

}

/* zwróæ wierzcho³ki*/
Vertex Edge::getV1()const {

	return v1;

}


Vertex Edge::getV2()const {

	return v2;

}

/*d³ugoœæ krawêdzie*/
double Edge::getLength(){

	return sqrt(pow((v2.getX() - v1.getX()),2) + pow((v2.getY() - v1.getY()),2) + pow((v2.getZ() - v1.getZ()),2));

}

/*przeci¹¿one operatory*/
bool Edge::operator ==( const Edge & e ) const{

    return ((( this->v1 == e.v1 ) &&( this->v2 == e.v2 )) || (this->v2 == e.v1)&&(this->v1 == e.v2) );

  
}


bool Edge::operator<(const Edge& e) const {

	return ( this->length < e.length);

}
