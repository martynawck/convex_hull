/*
	*
	* Martyna Wi�cek - Pow�oka wypuk�a
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

/* zwr�� wierzcho�ki*/
Vertex Edge::getV1()const {

	return v1;

}


Vertex Edge::getV2()const {

	return v2;

}

/*d�ugo�� kraw�dzie*/
double Edge::getLength(){

	return sqrt(pow((v2.getX() - v1.getX()),2) + pow((v2.getY() - v1.getY()),2) + pow((v2.getZ() - v1.getZ()),2));

}

/*przeci��one operatory*/
bool Edge::operator ==( const Edge & e ) const{

    return ((( this->v1 == e.v1 ) &&( this->v2 == e.v2 )) || (this->v2 == e.v1)&&(this->v1 == e.v2) );

  
}


bool Edge::operator<(const Edge& e) const {

	return ( this->length < e.length);

}
