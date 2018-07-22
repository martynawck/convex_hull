#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <math.h>
#include <vector>
const int NO_TO_GEN = 10;
#include "Generator.h"
using namespace std;


Generator::Generator() {}
Generator::~Generator() {}

int Generator::getSize() {
	return generated_set.size();
}

void Generator::sortByX() {
	sort(generated_set.begin(), generated_set.end(), Point::XWayToSort);
}

void Generator::sortByY() {
	sort(generated_set.begin(), generated_set.end(), Point::YWayToSort);
}

void Generator::sortByZ() {
	sort(generated_set.begin(), generated_set.end(), Point::ZWayToSort);
}

void Generator::generateInCube(int no_to_generate, double x_axis, double y_axis, double z_axis, double edge_length) {
	int no_generated = 0;
	double xL, xR, yL, yR, zL, zR;
	srand(time(NULL));
	x0 = x_axis;
	y0 = y_axis;
	z0 = z_axis;
	r = edge_length/2;

	xL = x_axis-edge_length/2;
	xR = x_axis+edge_length/2;
	yL = y_axis-edge_length/2;
	yR = y_axis+edge_length/2;
	zL = z_axis-edge_length/2;
	zR = z_axis+edge_length/2;

	while (no_generated < no_to_generate) {
	
		double x = (xR - xL) * ( (double)rand() / (double)RAND_MAX ) + xL;
		double y = (yR - yL) * ( (double)rand() / (double)RAND_MAX ) + yL;
		double z = (zR - zL) * ( (double)rand() / (double)RAND_MAX ) + zL;
		Point p = Point(x,y,z);
		generated_set.push_back(p);
		no_generated++;
	}
}

void Generator::generateInSphere(int no_to_generate, double x_axis, double y_axis, double z_axis, double radius) {
	int no_generated = 0;
	double xL, xR, yL, yR, zL, zR;
	srand(time(NULL));

	x0 = x_axis;
	y0 = y_axis;
	z0 = z_axis;
	r = radius;

	xL = x_axis-radius;
	xR = x_axis+radius;
	yL = y_axis-radius;
	yR = y_axis+radius;

	while (no_generated < no_to_generate) {
	
		double x = (xR - xL) * ( (double)rand() / (double)RAND_MAX ) + xL;
		double y = (yR - yL) * ( (double)rand() / (double)RAND_MAX ) + yL;
		double xy = x*x + y*y;
		double drad = radius*radius;
		if ((xy) > drad )
			continue;
		zL = - sqrt(drad - xy);
		zR = zL *(-1);

		double z = (zR - zL) * ( (double)rand() / (double)RAND_MAX ) + zL;

		Point p = Point(x,y,z);
		generated_set.push_back(p);
		no_generated++;
	}
}

void Generator::generateOnSphere(int no_to_generate, double x_axis, double y_axis, double z_axis, double radius) {
	int no_generated = 0;
	double xL, xR, yL, yR, zL, zR;
	srand(time(NULL));

	x0 = x_axis;
	y0 = y_axis;
	z0 = z_axis;
	r = radius;

	xL = x_axis-radius;
	xR = x_axis+radius;
	yL = y_axis-radius;
	yR = y_axis+radius;
	zL = z_axis-radius;
	zR = z_axis+radius;

	while (no_generated < no_to_generate) {
	
		double x = (xR - xL) * ( (double)rand() / (double)RAND_MAX ) + xL;
		double y = (yR - yL) * ( (double)rand() / (double)RAND_MAX ) + yL;

		double xy = x*x + y*y;
		double drad = radius*radius;

		if ((xy) > drad )
			continue;

		double z = sqrt(drad - xy);

		if (zL < 0) {
		int sign = rand();
			if (z_axis + radius > 0) {
				if (sign%2)
				z = z*(-1);
			} else
				z = z*(-1);
		}

		Point p = Point(x,y,z);
		generated_set.push_back(p);
		no_generated++;
	}
}

void Generator::clearSet() {
     generated_set.clear();
}

void Generator::writeToFile(string s) {
	ofstream plik (s);
    if( plik.good() == true ) {
		plik<<x0<<" "<<y0<<" "<<z0<<" "<<r<<endl;
	for ( vector<Point>::iterator it = generated_set.begin(); it != generated_set.end(); it++) {
		plik<<it->getX()<<"  "<<it->getY()<<"  "<<it->getZ()<<endl;
		plik.flush();
	}
	plik.close();
	}
}

void Generator::readFromFile(string s) {
	ifstream plik (s);
	double x,y,z;

		plik>>x0>>y0>>z0>>r;
		while(!plik.eof()) {
		 plik >> x >> y >> z;
		 if (plik.eof())
			 continue;
		 Point p = Point(x,y,z);
		 generated_set.push_back(p);
		}
	plik.close();
}

void Generator::onScreen() {
	for ( vector<Point>::iterator it = generated_set.begin(); it != generated_set.end(); it++) {
		cout<<it->getX()<<"  "<<it->getY()<<"  "<<it->getZ()<<endl;
	}
}
/*
int main() {
	Generator gen = Generator();
    gen.generateInSphere(200,0.0,0.0,0.0,1.0);
	gen.writeToFile("nazwa2.txt");
	//gen.readFromFile();
	//gen.onScreen();


	return 0;
}*/