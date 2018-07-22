#include <iostream>
using namespace std;

class Point {

protected:
	double x;
	double y;
	double z;

public:
	Point(double,double,double);
	Point();
	Point(const Point &p);
	~Point();
	double getX () const ;
	double getY () const;
	double getZ () const;
	static bool XWayToSort(Point, Point);
	static bool YWayToSort(Point, Point);
	static bool ZWayToSort(Point, Point);
	void setX(double);
	void setY(double);
	void setZ(double);	
    bool operator < (const Point &p) const;

};