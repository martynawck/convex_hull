#include <iostream>
#include "ConvexHull.h"

#include <queue>
#include <vector>
using namespace std;

class QuickHull: ConvexHull {

private:
	//queue <Edge> edges;

public:
	void buildAlgorithm();
	void prepare();
	void nextStep();

};