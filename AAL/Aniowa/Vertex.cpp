#include <iostream>
#include "Vertex.h"
using namespace std;

/*konstruktory itd*/
Vertex::~Vertex(){
}

Vertex::Vertex() {

	Point();
	visited = false;

}

Vertex::Vertex(const Vertex &v) {	

	x = v.x;
	y = v.y;
	z = v.z;
	visited = v.visited;

}

Vertex::Vertex(double x,double y,double z, bool b) {

	this->x = x;
	this->y = y;
	this->z = z;
	visited = b;

}


/*funkcja sprawdzaj�ca, czy wierzcho�ek zosta� odwiedzony*/
bool Vertex::isVisited(){

	return visited;

}


/*funkcja sprawdzaj�ca, czy 2 punkty s� wsp�liniowe wg r�wnania prostej*/
bool Vertex::isColinear(Vertex a, Vertex b) {

	double a_val = (a.y - b.y) / (a.x - b.x);
	double b_val = (a.y - this->y) / (a.x - this->x);

	return (a_val == b_val);

}


/*funkcja ustawiaj�ca warto�� zmiennej visited*/
void Vertex::setVisited(bool b) {

	visited = b;

}


/*przeci��one operatory*/
bool Vertex::operator == ( const Vertex & v )const{

    return ((this->getX() == v.getX()) &&(this->getY() == v.getY() ) && (this->getZ() == v.getZ()) );

}


bool Vertex::operator<(const Vertex& v) const {

	return (  ((this->x < v.x )&& (this->y < v.y) && (this->z < v.z)) || ((this->x == v.x) &&(this->y < v.y) && (this->z < v.z))
		|| ((this->x == v.x) &&(this->y == v.y) &&(this->z < v.z)));

}