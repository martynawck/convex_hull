#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <math.h>
#include "Minimizer.h"

const int ACC = 12;
using namespace std;


Minimizer::Minimizer() {
	accuracy = 0;
}

Minimizer::~Minimizer() {
}
	
Minimizer::Minimizer(int accuracy) {
	this->accuracy = accuracy;
}


vector <Point> Minimizer::getBaseSet() {
	return base_set;
}

vector <Point> Minimizer::getFinalSet() {
	return final_set;
}

int Minimizer::getAccuracy() {
	return accuracy;
}

void Minimizer::writeToFile(string s) {
	ofstream plik (s);
    if( plik.good() == true ) {
	plik<<x0<<" "<<y0<<" "<<z0<<" "<<r<<endl;
	for ( vector<Point>::iterator it = final_set.begin(); it != final_set.end(); it++) {
		plik<<it->getX()<<"  "<<it->getY()<<"  "<<it->getZ()<<endl;
		plik.flush();
	}
	plik.close();
	}
}

void Minimizer::readFromFile(string s) {
	ifstream plik (s);
	double x,y,z;
		plik >>x0 >>y0 >>z0>>r;
		while(!plik.eof()) {
		 plik >> x >> y >> z;
		 if (plik.eof())
			 continue;
		 Point p = Point(x,y,z);
		 base_set.push_back(p);
		}
	plik.close();
}

void Minimizer::initializeKeys() {
	string val = "";
	double dr = 2*r;
	for (int zL = z0 - r; zL < accuracy; zL ++) {
		for (int yL = y0 - r; yL < accuracy; yL ++) {
			for (int xL = x0 - r; xL < accuracy; xL ++) {
				val.append(to_string(xL));
				val.append(to_string(yL));
				val.append(to_string(zL));
				min_cubes.insert(make_pair(val,vector<Point>()));
				val.clear();
			}
		}
	}
}

void Minimizer::divideIntoCubes() {
	string val="";
	int temp;
	double cube_length = (-x0 + 2*r)/accuracy;

	if (cube_length < 0)
		cube_length = cube_length* (-1);
	for (vector<Point>::iterator it = base_set.begin(); it != base_set.end(); it++) {
		temp = it->getX()/cube_length;
		val.append(to_string(temp));
		temp = it->getY()/cube_length;
		val.append(to_string(temp));
		temp = it->getZ()/cube_length;
		val.append(to_string(temp));

		Point p = Point(it->getX(),it->getY(),it->getZ());
		if (min_cubes[val].empty()) {
			min_cubes.insert(make_pair(val,vector<Point>()));
		}
		min_cubes[val].push_back(p);
		val.clear();
	}
}

void Minimizer::findAveragePoints(){
	double xf = 0.0, yf = 0.0, zf = 0.0;
	int how_many = 0;
	for(map <string, vector <Point> > ::iterator outer_iter=min_cubes.begin(); outer_iter!=min_cubes.end(); ++outer_iter) {
		for(vector <Point>::iterator inner_iter=outer_iter->second.begin(); inner_iter!=outer_iter->second.end(); ++inner_iter) {
			xf = inner_iter->getX() + xf;
			yf = inner_iter->getY() + yf;
			zf = inner_iter->getZ() + zf;
			++how_many;
		}
		if (xf != 0 && yf != 0 && zf != 0 ) {
			Point p = Point(xf/how_many,yf/how_many,zf/how_many);
			final_set.push_back(p);
		}
		xf = 0.0, yf = 0.0, zf = 0.0;
		how_many = 0;
	}

}

/*
int main() {

	Minimizer min = Minimizer(ACC);
	min.readFromFile();
	//min.writeToFile();
	min.divideIntoCubes();
	min.findAveragePoints();
	min.writeToFile();
	
	return 0;
}
*/