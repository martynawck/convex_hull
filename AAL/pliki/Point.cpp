#include <iostream>
//#include "Set.h"
#include "Point.h"
using namespace std;

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
double Point::getX () const {
	return this->x;
}
double Point::getY ()const  {
	return this->y;
}
double Point::getZ () const {
	return this->z;
}
bool Point::XWayToSort(Point a, Point b) {
	return a.getX()>b.getX();
}
bool Point:: YWayToSort(Point a, Point b) {
	return a.getY()>b.getY();
}
bool Point:: ZWayToSort(Point a, Point b) {
	return a.getZ()>b.getZ();
}

void Point::setX(double a) {
	x = a;
}
void Point::setY(double a) {
	y = a;
}
void Point::setZ(double a) {
	z = a;
}

bool Point::operator < (const Point &p) const {
        return ( (p.x < x) &&
                (p.y < y ) && (p.z < z) );
    }

