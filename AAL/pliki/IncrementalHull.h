#include <iostream>
#include "ConvexHull.h"
#include <vector>
using namespace std;

class IncrementalHull : public ConvexHull {

public:
	Vertex middle;

public:
	void buildAlgorithm();
	void prepare();
	void nextStep();

};