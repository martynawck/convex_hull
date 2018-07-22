#pragma once
#include <iostream>
#include "ConvexHull.h"
#include <vector>
using namespace std;

class IncrementalHull : public ConvexHull {

public:
	Vertex middle;

public:
	double buildAlgorithm(string s1, string s2);
	void prepare();
	void nextStep();

};