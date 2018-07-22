/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
	*
*/
#include "Facet.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;


/*konstruktory*/
Facet::Facet(){
}


Facet::~Facet(){
}


Facet::Facet(Vertex v1, Vertex v2, Vertex v3){

	this->v[0] = v1;
	this->v[1] = v2;
	this->v[2] = v3;
	this->e[0] = Edge(v1,v2);
	this->e[1] = Edge(v2,v3);
	this->e[2] = Edge(v3,v1);
	visible = true;

}


Facet::Facet(Edge e1, Edge e2, Edge e3){

	this->e[0] = e1;
	this->e[1] = e2;
	this->e[2] = e3;
	this->v[0] = Vertex(e1.getV1());
	this->v[1] = Vertex(e1.getV2());
	this->v[2] = Vertex(e2.getV2());
	visible = true;

}


/*dostêp do pojedynczych wierzcho³ków*/
Vertex Facet::getV1()const {

	return v[0];

}


Vertex Facet::getV2() const{

	return v[1];

}


Vertex Facet::getV3() const{

	return v[2];

}


/*dostêp do pojedynczych krawêdzi*/
Edge Facet::getE1() const{

	return e[0];

}


Edge Facet::getE2() const{

	return e[1];

}


Edge Facet::getE3() const{

	return e[2];

}


/*czy krawêdz jest widzialna z zewn¹trz otoczki*/
bool Facet::getVisible(){

	return visible;

}


/*ustaw, ¿e jest widzialna*/
void Facet::setVisible(bool b) {
	visible = b;
}


/*zamieñ na ci¹g znaków*/
string Facet::toString() {

	string val = "";
	val.append(to_string(getV1().getX()));
	val.append(to_string(getV2().getX()));
	val.append(to_string(getV3().getX()));
	return val;

}


/*oblicz odleg³oœæ od p³aszczyzny*/
double Facet::distanceFromVertex(Vertex p) {

	//wpó³rzêdne
	double *coefficients;
	coefficients = ABCofEquation();

	//wartoœæ x w równaniu
	double vertexValue = vertexIntoEquation(p);

	//pierwiastek z kwadratów wspó³czynników A, B, C
	double finalValue = vertexValue / (sqrt(pow(coefficients[0],2) + pow(coefficients[1],2) + pow(coefficients[2],2)));

	//modu³ z wartoœci
	if (finalValue < 0 )
		finalValue = finalValue* (-1);

	return finalValue;

}


/*wartoœæ równania dla konkretnego wierzcho³ka*/
double Facet::vertexIntoEquation(Vertex p) {

	double *coefficients;

	coefficients = ABCofEquation();

	double A = coefficients[0];
	double B = coefficients[1];
	double C = coefficients[2];

	//wstaw do równania
	double value = A*p.getX() - A*v[0].getX() + B*p.getY() - B*v[0].getY() + C*p.getZ() - C*v[0].getZ();

	return value;

}


/*obliczanie wspó³czynników równania p³aszczyzny*/
double* Facet::ABCofEquation() {

	double coefficients [3] ;

	//obliczenie d³ugoœci odcinka AB-BC
	Vertex ab = Vertex(v[1].getX() - v[0].getX(), v[1].getY() - v[0].getY(),v[1].getZ() - v[0].getZ(),true);
	Vertex cb = Vertex(v[1].getX() - v[2].getX(), v[1].getY() - v[2].getY(),v[1].getZ() - v[2].getZ(),true);

	//iloczyn wektorowy
	Vertex abxcb = Vertex(ab.getY()*cb.getZ() - ab.getZ()*cb.getY(), ab.getZ()*cb.getX()  - ab.getX()*cb.getZ(), ab.getX()*cb.getY() - ab.getY()*cb.getX() ,true);

	coefficients[0] = abxcb.getX(); // A
	coefficients[1] = abxcb.getY(); // B
	coefficients[2] = abxcb.getZ(); // C

	return coefficients;

}


/*czy 2 punkty s¹ po tej samej stronie p³aszczyzny*/
bool Facet::notSameSide(Vertex p, Vertex m) {

	double valueForP = vertexIntoEquation (p);
	double valueForM = vertexIntoEquation(m);

	//jeœli s¹ róznych znaków to prawda
	if ((valueForP > 0 && valueForM < 0) || (valueForP < 0 && valueForM > 0))
		return true;

	return false;

}


/*funkcja obliczaj¹ca czy punkt jest w danej pó³przestrzeni wyznaczonej przez równanie p³aszczyzny*/
double Facet::halfSpace(Vertex ver) {

	double matrix [3][3] ;
	double vx = ver.getX();
	double vy = ver.getY();
	double vz = ver.getZ();

	matrix[0][0] = (v[1].getX() - v[0].getX());
	matrix[1][0] = (v[1].getY() - v[0].getY());
	matrix[2][0] = (v[1].getZ() - v[0].getZ());
	matrix[0][1] = (v[2].getX() - v[0].getX());
	matrix[1][1] = (v[2].getX() - v[0].getY());
	matrix[2][1] = (v[2].getX() - v[0].getZ());
	matrix[0][2] = (vx - v[0].getX());
	matrix[1][2] = (vy - v[1].getY());
	matrix[2][2] = (vz - v[2].getZ());

	double a = matrix[0][0]*matrix[1][1]*matrix[2][2];
	double b = matrix[0][1]*matrix[1][2]*matrix[2][0];
	double c = matrix[1][0]*matrix[2][1]*matrix[0][2];
	double d = matrix[2][0]*matrix[1][1]*matrix[0][2];
	double e = matrix[1][0]*matrix[0][1]*matrix[2][2];
	double f = matrix[0][0]*matrix[2][1]*matrix[1][2];
	//wartosc wyznacznika macierzy

	return  a + b + c - (d+e+f);

}


/*przeci¹¿ony operator*/
bool Facet::operator<(const Facet& f )const{
	double p = v[0].getZ();
	double pp = v[1].getZ();
	double ppp = (pp-p)/2;

	double p1 = f.v[0].getZ();
	double pp1 = f.v[1].getZ();
	double ppp1 = (pp1-p1)/2;

	return ppp < ppp1;
}
