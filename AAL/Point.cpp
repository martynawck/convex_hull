/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
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


/*funkcja zwracaj¹ca wspó³rzêdn¹ X*/
double Point::getX () const {

	return this->x;

}


/*funkcja zwracaj¹ca wspó³rzêdn¹ Y*/
double Point::getY ()const  {

	return this->y;

}


/*funkcja zwracaj¹ca wspó³rzêdn¹ Z*/
double Point::getZ () const {

	return this->z;

}


/*funkcja slu¿¹ca do sortowania wektora po wspó³rzêdnej X*/
bool Point::XWayToSort(Point a, Point b) {

	return a.getX()>b.getX();

}


/*funkcja slu¿¹ca do sortowania wektora po wspó³rzêdnej Y*/
bool Point:: YWayToSort(Point a, Point b) {

	return a.getY()>b.getY();

}


/*funkcja slu¿¹ca do sortowania wektora po wspó³rzêdnej Z*/
bool Point:: ZWayToSort(Point a, Point b) {

	return a.getZ()>b.getZ();

}


/*funkcja s³u¿¹ca do zmiany wspó³rzêdnej X*/
void Point::setX(double a) {

	x = a;

}


/*funkcja s³u¿¹ca do zmiany wspó³rzêdnej Y*/
void Point::setY(double a) {

	y = a;

}


/*funkcja s³u¿¹ca do zmiany wspó³rzêdnej Z*/
void Point::setZ(double a) {

	z = a;

}
