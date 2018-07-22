/*
	*
	* Martyna Wi�cek - Pow�oka wypuk�a
	*
*/
#pragma once
#include <iostream>
using namespace std;

class Point {

protected:
	double x;
	double y;
	double z;

public:
	/*konstruktory*/
	Point();

	Point(double,double,double);
	
	Point(const Point &p);
	
	~Point();
	
	/*funkcja zwracaj�ca wsp�rz�dn� X*/
	double getX () const;
	
	/*funkcja zwracaj�ca wsp�rz�dn� Y*/
	double getY () const;
	
	/*funkcja zwracaj�ca wsp�rz�dn� Z*/
	double getZ () const;
	
	/*funkcje do sortowania punkt�w po wsp�rzednych X, Y, Z*/
	static bool XWayToSort(Point, Point);
	
	static bool YWayToSort(Point, Point);
	
	static bool ZWayToSort(Point, Point);
	
	/*ustawianie warto�ci punktu*/
	void setX(double);
	
	void setY(double);
	
	void setZ(double);	

};