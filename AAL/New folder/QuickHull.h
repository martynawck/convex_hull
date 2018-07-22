#pragma once
#include <iostream>
#include "ConvexHull.h"

#include <queue>
#include <map>
#include <vector>
using namespace std;

class QuickHull: ConvexHull {

private:
	map <string, vector<Vertex> > facetsMap;
	//queue <Edge> edges;

public:
	double buildAlgorithm(string s1, string s2);
	void prepare();
	void nextStep();

};