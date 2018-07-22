/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
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
	
	/*funkcja zwracaj¹ca wspó³rzêdn¹ X*/
	double getX () const;
	
	/*funkcja zwracaj¹ca wspó³rzêdn¹ Y*/
	double getY () const;
	
	/*funkcja zwracaj¹ca wspó³rzêdn¹ Z*/
	double getZ () const;
	
	/*funkcje do sortowania punktów po wspó³rzednych X, Y, Z*/
	static bool XWayToSort(Point, Point);
	
	static bool YWayToSort(Point, Point);
	
	static bool ZWayToSort(Point, Point);
	
	/*ustawianie wartoœci punktu*/
	void setX(double);
	
	void setY(double);
	
	void setZ(double);	

};