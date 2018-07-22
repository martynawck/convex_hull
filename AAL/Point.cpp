/*
	*
	* Martyna Wi�cek - Pow�oka wypuk�a
	*
*/
#include <iostream>
#include "Point.h"
using namespace std;

/*konstruktory*/
Point::Point(double x,double y,double z) {

	this->x = x;
	this->y=y;
	this->z = z;

}


Point::Point() {

	x = 0.0;
	y = 0.0;
	z = 0.0;

}


Point::Point(const Point &p) {	

	x = p.x;
	y = p.y;
	z = p.z;

}


Point::~Point(){
}


/*funkcja zwracaj�ca wsp�rz�dn� X*/
double Point::getX () const {

	return this->x;

}


/*funkcja zwracaj�ca wsp�rz�dn� Y*/
double Point::getY ()const  {

	return this->y;

}


/*funkcja zwracaj�ca wsp�rz�dn� Z*/
double Point::getZ () const {

	return this->z;

}


/*funkcja slu��ca do sortowania wektora po wsp�rz�dnej X*/
bool Point::XWayToSort(Point a, Point b) {

	return a.getX()>b.getX();

}


/*funkcja slu��ca do sortowania wektora po wsp�rz�dnej Y*/
bool Point:: YWayToSort(Point a, Point b) {

	return a.getY()>b.getY();

}


/*funkcja slu��ca do sortowania wektora po wsp�rz�dnej Z*/
bool Point:: ZWayToSort(Point a, Point b) {

	return a.getZ()>b.getZ();

}


/*funkcja s�u��ca do zmiany wsp�rz�dnej X*/
void Point::setX(double a) {

	x = a;

}


/*funkcja s�u��ca do zmiany wsp�rz�dnej Y*/
void Point::setY(double a) {

	y = a;

}


/*funkcja s�u��ca do zmiany wsp�rz�dnej Z*/
void Point::setZ(double a) {

	z = a;

}
