#include <iostream>
#include "Edge.h"
#include <math.h>
using namespace std;


Edge::Edge() {
	is_horizon = true;
}
Edge::~Edge() {}

Edge::Edge(Vertex v1, Vertex v2) {
	is_horizon = true;
	this->v1 = v1;
	this->v2 = v2;
	this->length = getLength();
}
Vertex Edge::getV1()const {
	return v1;
}
Vertex Edge::getV2()const {
	return v2;
}
//Facet Edge::getF1(){
	//return f1;
//}
//Facet Edge::getF2(){
	//return f2;
//}
double Edge::getLength(){
	return sqrt(pow((v2.getX() - v1.getX()),2) + pow((v2.getY() - v1.getY()),2) + pow((v2.getZ() - v1.getZ()),2));
}

void Edge::setHorizon(bool b) {
	is_horizon = b;
}

bool Edge::operator ==( const Edge & e ) const{
    return ((( this->v1 == e.v1 ) &&( this->v2 == e.v2 )) || (this->v2 == e.v1)&&(this->v1 == e.v2) );
       //  --return true;
   // else
     //    return false;
   
}

bool Edge::operator<(const Edge& e) const {
	return ( this->length < e.length);

}

bool Edge::getHorizon() {
	return is_horizon;
}