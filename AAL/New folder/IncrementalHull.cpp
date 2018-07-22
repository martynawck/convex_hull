#include "IncrementalHull.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <ctime>
using namespace std;

double IncrementalHull::buildAlgorithm(string s1, string s2){
	double difference;
	clock_t start,end;
	readFromFile(s1);
	start = clock();
	prepare();
	nextStep();
	end = clock();
	writeToFile(s2);
	difference = (end - start)/(double)CLOCKS_PER_SEC;
	return difference;

}

void IncrementalHull::prepare() {

	double x_m = 0.0;
	double y_m = 0.0;
	double z_m = 0.0;
	
	vector<Vertex>::size_type sz = vertices.size();

	x_m = vertices[0].getX();
	y_m = vertices[0].getY();
	z_m = vertices[0].getZ();

	x_m = x_m + vertices[1].getX();
	y_m = y_m + vertices[1].getY();
	z_m = z_m + vertices[1].getZ();

	unsigned i = 2;
	while (i < sz &&(vertices[i].isColinear(vertices[0],vertices[1]))) {
		i++;
	}

	x_m = x_m + vertices[i].getX();
	y_m = y_m + vertices[i].getY();
	z_m = z_m + vertices[i].getZ();

	vertices[0].setVisited(true);
	vertices[1].setVisited(true);
	vertices[i].setVisited(true);

	Facet f = Facet(vertices[0],vertices[i],vertices[1]);
	f.setVisible(true);
	facets.push_back(f);

	unsigned j = 2;

	while ((j < sz) &&((f.halfSpace(vertices[j])==0) || (vertices[j].isVisited() == true))) {
		j++;
	}

	vertices[j].setVisited(true);

	x_m = x_m + vertices[j].getX();
	y_m = y_m + vertices[j].getY();
	z_m = z_m + vertices[j].getZ();

	Facet f2 = Facet(vertices[i],vertices[j],vertices[1]);
	f2.setVisible(true);
	facets.push_back(f2);
	f2 = Facet(vertices[j],vertices[i],vertices[0]);
	f2.setVisible(true);
	facets.push_back(f2);
	f2 = Facet(vertices[j],vertices[0],vertices[1]);
	f2.setVisible(true);
	facets.push_back(f2);

	x_m = x_m/4;
	y_m = y_m/4;
	z_m = z_m/4;

	middle = Vertex(x_m,y_m,z_m,true);

}

void IncrementalHull::nextStep(){
	vector <Facet> tempFacets;
	vector <Edge> tempEdges;
	vector <Edge> tempDeleted;

	for (unsigned i = 0; i < vertices.size(); i++) {
		if(!vertices[i].isVisited()){ 
		for (unsigned j = 0; j < facets.size(); j++ ){
			if (facets[j].notSameSide(vertices[i],middle)) {	
			//if (volume(facets[j],vertices[i]) < 0) {
				tempFacets.push_back(facets[j]);
				facets[j].setVisible(false);
			}
		}
		
		unsigned l = 0;
		while (l < facets.size() ){
			if (facets[l].getVisible() == false)  {
				facets.erase(facets.begin() + l);
				continue;
			}
			l++;
		}

		for (unsigned k = 0; k < tempFacets.size(); k++) {

			std::vector<Edge>::iterator e = find(tempEdges.begin(), tempEdges.end(),tempFacets[k].getE1());
			std::vector<Edge>::iterator ed = find(tempDeleted.begin(), tempDeleted.end(),tempFacets[k].getE1());
			
			if ((e == tempEdges.end()) && (ed == tempDeleted.end())) {
					tempEdges.push_back(tempFacets[k].getE1());
				} else {
					
					if (e != tempEdges.end()) {
					tempEdges.erase(e);
					tempDeleted.push_back(tempFacets[k].getE1());
					}
				}

			e = find(tempEdges.begin(), tempEdges.end(),tempFacets[k].getE2());
			ed = find(tempDeleted.begin(), tempDeleted.end(),tempFacets[k].getE2());
			
			if ((e == tempEdges.end()) && (ed == tempDeleted.end())) {
					tempEdges.push_back(tempFacets[k].getE2());
				} else {
					
					if (e != tempEdges.end()) {
					tempEdges.erase(e);
					tempDeleted.push_back(tempFacets[k].getE2());
					}
				}

			e = find(tempEdges.begin(), tempEdges.end(),tempFacets[k].getE3());
			ed = find(tempDeleted.begin(), tempDeleted.end(),tempFacets[k].getE3());
			
			if ((e == tempEdges.end()) && (ed == tempDeleted.end())) {
					tempEdges.push_back(tempFacets[k].getE3());
				} else {
					
					if (e != tempEdges.end()) {

					tempEdges.erase(e);
					tempDeleted.push_back(tempFacets[k].getE3());
					}
				}				
		}

		for (unsigned l = 0; l < tempEdges.size(); l++) {
			Facet f = Facet(tempEdges[l].getV1(),tempEdges[l].getV2(),vertices[i]);
			f.setVisible(true);
			facets.push_back(f);
		}

		tempFacets.clear();
		tempEdges.clear();
		tempDeleted.clear();
		vertices[i].setVisited(true);
		}
	}
}


