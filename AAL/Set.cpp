#include <iostream>
#include <algorithm>
#include <fstream>
#include "Set.h"
using namespace std;

Set::Set() {
}
Set::Set(Point[]){
}
Set::~Set(){
}
int Set::sizeOfSet(){
	return points.size();
}
void Set::addPoint(Point a){
	Point p = Point(a.getX(),a.getY(),a.getZ());
	points.push_back(p);
}

void Set::onScreen() {

	for ( vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
		cout<<it->getX()<<"  "<<it->getY()<<"  "<<it->getZ()<<endl;
	}
}
void Set::writeToFile() {
	ofstream plik ("nazwa2.txt");
    if( plik.good() == true ) {
	for ( vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
		plik<<it->getX()<<"  "<<it->getY()<<"  "<<it->getZ()<<endl;
		plik.flush();
	}
	plik.close();
	}
}

void Set::readFromFile() {
	ifstream plik ("nazwa2.txt");
	double x,y,z;

		while(!plik.eof()) {
		 plik >> x >> y >> z;
		 if (plik.eof())
			 continue;
		 Point p = Point(x,y,z);
		 this->addPoint(p);
		}
	plik.close();

}
void Set::copySet(Set s1, Set s2) {

	for (vector<Point>::iterator it = s1.getPoints().begin(); it != s1.getPoints().end(); it++) {
		Point p = Point (it->getX(),it->getY(),it->getZ());
			s2.addPoint(p);
	}
}

void Set::clearSet() {
	this->points.clear();
}

void Set::removePoint(Point a){
	sort(points.begin(), points.end(), Point::XWayToSort);
	for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
		if (it->getX() == a.getX() && it->getY() == a.getY() && it->getZ() == a.getZ())
			points.erase(it);
			return;
	}
}
void Set::sortByX() {
	sort(points.begin(), points.end(), Point::XWayToSort);
}
void Set::sortByY() {
	sort(points.begin(), points.end(), Point::YWayToSort);
}
void Set::sortByZ() {
	sort(points.begin(), points.end(), Point::ZWayToSort);
}
vector <Point> Set::getPoints() {
	return points;
}

