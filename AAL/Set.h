#include <iostream>
#include "Point.h"
#include <vector>
using namespace std;

class Set {

private:
	vector <Point> points;
	int size;

public:
	Set();
	Set(Point[]);
	~Set();
	vector <Point> getPoints();
	int sizeOfSet();
	void addPoint(Point);
	void removePoint(Point);
	void sortByX();
	void sortByY();
	void sortByZ();
	void onScreen();
	void writeToFile();
	void readFromFile();
	void copySet(Set s1, Set s2);
	void clearSet();

};