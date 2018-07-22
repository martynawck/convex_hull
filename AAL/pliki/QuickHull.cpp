#include "QuickHull.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

void QuickHull::buildAlgorithm() {
	readFromFile("nazwa2.txt");
	prepare();
	nextStep();
	writeToFile("nazwa5.txt");
}

void QuickHull::prepare() {




	sort (vertices.begin(), vertices.end(), Point::ZWayToSort);
	int median = vertices.size()/2;

	Facet f = Facet(vertices[median-1],vertices[median],vertices[median+1]);
	f.setVisible(true);
	facets.push_back(f);

	for (unsigned i = 0; i < vertices.size(); i++) {


	}


}

void QuickHull::nextStep() {
}