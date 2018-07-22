#include "Facet.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

Facet::Facet(){
	//is_horizon = true;
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
Vertex Facet::getV1()const {
	return v[0];
}
Vertex Facet::getV2() const{
	return v[1];
}
Vertex Facet::getV3() const{
	return v[2];
}
Edge Facet::getE1() const{
	return e[0];
}
Edge Facet::getE2() const{
	return e[1];
}
Edge Facet::getE3() const{
	return e[2];
}
bool Facet::getVisible(){
	return visible;
}

void Facet::setVisible(bool b) {
	visible = b;
}

string Facet::toString() {
	string val = "";
	val.append(to_string(getV1().getX()));
	val.append(to_string(getV2().getX()));
	val.append(to_string(getV3().getX()));
				//facetsMap.insert(make_pair(val,vector<Vertex>()));
				//facetsMap[val].push_back(vertices[i]);
	return val;

}

double Facet::distanceFromVertex(Vertex p) {
	double *coefficients;
	coefficients = ABCofEquation();

	double vertexValue = vertexIntoEquation(p);
	double finalValue = vertexValue / (sqrt(pow(coefficients[0],2) + pow(coefficients[1],2) + pow(coefficients[2],2)));
	if (finalValue < 0 )
		finalValue = finalValue* (-1);
	return finalValue;
}

double Facet::vertexIntoEquation(Vertex p) {
	double *coefficients;

	coefficients = ABCofEquation();

	double A = coefficients[0];
	double B = coefficients[1];
	double C = coefficients[2];

	double value = A*p.getX() - A*v[0].getX() + B*p.getY() - B*v[0].getY() + C*p.getZ() - C*v[0].getZ();

	return value;
}

double* Facet::ABCofEquation() {
	double coefficients [3] ;// = coefficients;
	Vertex ab = Vertex(v[1].getX() - v[0].getX(), v[1].getY() - v[0].getY(),v[1].getZ() - v[0].getZ(),true);
	Vertex cb = Vertex(v[1].getX() - v[2].getX(), v[1].getY() - v[2].getY(),v[1].getZ() - v[2].getZ(),true);
	Vertex abxcb = Vertex(ab.getY()*cb.getZ() - ab.getZ()*cb.getY(), ab.getZ()*cb.getX()  - ab.getX()*cb.getZ(), ab.getX()*cb.getY() - ab.getY()*cb.getX() ,true);

	coefficients[0] = abxcb.getX(); //A
	coefficients[1] = abxcb.getY(); //B
	coefficients[2] = abxcb.getZ(); //C
	return coefficients;
}

bool Facet::notSameSide(Vertex p, Vertex m) {
/*	Vertex ab = Vertex(v[1].getX() - v[0].getX(), v[1].getY() - v[0].getY(),v[1].getZ() - v[0].getZ(),true);
	Vertex cb = Vertex(v[1].getX() - v[2].getX(), v[1].getY() - v[2].getY(),v[1].getZ() - v[2].getZ(),true);
	Vertex abxcb = Vertex(ab.getY()*cb.getZ() - ab.getZ()*cb.getY(), ab.getZ()*cb.getX()  - ab.getX()*cb.getZ(), ab.getX()*cb.getY() - ab.getY()*cb.getX() ,true);

	double A = abxcb.getX();
	double B = abxcb.getY();
	double C = abxcb.getZ();*/

	double valueForP = vertexIntoEquation (p);//    A*p.getX() - A*v[0].getX() + B*p.getY() - B*v[0].getY() + C*p.getZ() - C*v[0].getZ();
	double valueForM = vertexIntoEquation(m);//A*m.getX() - A*v[0].getX() + B*m.getY() - B*v[0].getY() + C*m.getZ() - C*v[0].getZ();

	if ((valueForP > 0 && valueForM < 0) || (valueForP < 0 && valueForM > 0))
		return true;
	return false;
}


double Facet::halfSpace(Vertex ver) {
	double matrix [3][3] ;
	double vx = ver.getX();
	double vy = ver.getY();
	double vz = ver.getZ();
	//cout<<vx<<vy<<vz<<endl;
	//double g = v[0].getX();
	//cout<<g<<endl;
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
	return  a + b + c - (d+e+f) ;
}
/*
bool Facet::halfSpace(Vertex ver, Vertex mid) {
	double matrix [3][3] ;
	double vx = ver.getX();
	double vy = ver.getY();
	double vz = ver.getZ();
	//cout<<vx<<vy<<vz<<endl;
	//double g = v[0].getX();
	//cout<<g<<endl;
	matrix[0][0] = (vx - v[0].getX());
	matrix[1][0] = (vx - v[1].getX());
	matrix[2][0] = (vx - v[2].getX());
	matrix[0][1] = (vy - v[0].getY());
	matrix[1][1] = (vy - v[1].getY());
	matrix[2][1] = (vy - v[2].getY());
	matrix[0][2] = (vz - v[0].getZ());
	matrix[1][2] = (vz - v[1].getZ());
	matrix[2][2] = (vz - v[2].getZ());

	double a = matrix[0][0]*matrix[1][1]*matrix[2][2];
	double b = matrix[0][1]*matrix[1][2]*matrix[2][0];
	double c = matrix[1][0]*matrix[2][1]*matrix[0][2];
	double d = matrix[2][0]*matrix[1][1]*matrix[0][2];
	double e = matrix[1][0]*matrix[0][1]*matrix[2][2];
	double f = matrix[0][0]*matrix[2][1]*matrix[1][2];

	double vertex_sign =  a + b + c - (d+e+f) ;

	vx = mid.getX();
	vy = mid.getY();
	vz = mid.getZ();

	matrix[0][0] = (vx - v[0].getX());
	matrix[1][0] = (vx - v[1].getX());
	matrix[2][0] = (vx - v[2].getX());
	matrix[0][1] = (vy - v[0].getY());
	matrix[1][1] = (vy - v[1].getY());
	matrix[2][1] = (vy - v[2].getY());
	matrix[0][2] = (vz - v[0].getZ());
	matrix[1][2] = (vz - v[1].getZ());
	matrix[2][2] = (vz - v[2].getZ());

	a = matrix[0][0]*matrix[1][1]*matrix[2][2];
	b = matrix[0][1]*matrix[1][2]*matrix[2][0];
	c = matrix[1][0]*matrix[2][1]*matrix[0][2];
	d = matrix[2][0]*matrix[1][1]*matrix[0][2];
	e = matrix[1][0]*matrix[0][1]*matrix[2][2];
	f = matrix[0][0]*matrix[2][1]*matrix[1][2];

	double mid_sign =  a + b + c - (d+e+f) ;

	//cout<<"vertex"<<vertex_sign<<endl;
	//cout<<"midex"<<mid_sign<<endl;
	if ( ((mid_sign > 0) && (vertex_sign > 0)) || ((mid_sign <= 0)&&(vertex_sign <= 0)) ){
		return false;
	}
	return true;
}

*/
bool Facet::operator<(const Facet& f )const{
	double p = v[0].getZ();
	double pp = v[1].getZ();
	double ppp = (pp-p)/2;

	double p1 = f.v[0].getZ();
	double pp1 = f.v[1].getZ();
	double ppp1 = (pp1-p1)/2;

	return ppp < ppp1;
}
/*
bool Facet::operator == ( const Facet & e )const {
}*/