#include "QuickHull.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cstdio>
#include <ctime>
using namespace std;

queue <Facet> facetsToGo;

double QuickHull::buildAlgorithm(string s1, string s2) {

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

void QuickHull::prepare() {

	sort (vertices.begin(), vertices.end(), Point::XWayToSort);
	int median = vertices.size()/2;

	Facet f = Facet(vertices[median-1],vertices[median],vertices[median+1]);
	f.setVisible(true);
	facets.push_back(f);

	//dodaj druga counterclockwise
	f = Facet(vertices[median-1],vertices[median+1],vertices[median]);
	f.setVisible(true);
	facets.push_back(f);

	//zaznacz wierzcholki jako oznaczone
	vertices[median-1].setVisited(true);
	vertices[median].setVisited(true);
	vertices[median+1].setVisited(true);

	string val = "";

	for (unsigned i = 0; i < vertices.size(); i++) {
		if (vertices[i].isVisited() == false) {
			if (facets[0].vertexIntoEquation(vertices[i]) > 0) {
				cout<<facets[0].toString()<<endl;
				facetsMap.insert(make_pair(facets[0].toString(),vector<Vertex>()));
				facetsMap[facets[0].toString()].push_back(vertices[i]);			}
			else {
				cout<<facets[1].toString()<<endl;
				
				//cout<<facets[1].vertexIntoEquation(vertices[i])<<endl;
				facetsMap.insert(make_pair(facets[1].toString(),vector<Vertex>()));
				facetsMap[facets[1].toString()].push_back(vertices[i]);	
			}
		}
	}

	facetsToGo.push(facets[0]);
	facetsToGo.push(facets[1]);
	cout<<"poczatkowy facets to go"<<facetsMap.size()<<endl;

}

void QuickHull::nextStep() {

	int inner = 0;
	double distance = 0.0;
	double max_distance = 0.0;
	int max_inner = 0;

	vector <Facet> tempFacets;
	vector <Edge> tempEdges;
	vector <Edge> tempDeleted;

	while (!facetsToGo.empty()) {
//
		cout<<"rozmiar mapy"<<facetsMap.size()<<endl;
		cout<<"ile w kolejce "<<facetsToGo.size()<<endl;

		//znajdz w mapie odpowiednia sciane
		std::map <string,vector<Vertex>>::iterator it;
		it = facetsMap.find(facetsToGo.front().toString());

		if (it != facetsMap.end()) {

			//znajdz najwiekszy wierzcholek
			int i = 0;
			for (vector <Vertex>::iterator inner_iter = it->second.begin(); inner_iter !=it->second.end(); inner_iter ++) {
				distance = facetsToGo.front().distanceFromVertex(Vertex(inner_iter->getX(), inner_iter->getY(), inner_iter->getZ(),false));
				cout<<"odleglosc"<<distance<<endl;
			
			//Vertex v = Vertex(inner_iter->getX(), inner_iter->getY(), inner_iter->getZ(),false);
				if (distance > max_distance) {
					max_distance = distance;
					max_inner = inner;
				}
				inner++;
			}

			cout<<"max distance "<<max_distance<<"ineer "<<max_inner<<endl;

			//iterator do tego konkretnego elementu
			vector <Vertex>::iterator it2 = it->second.begin() + max_inner;
			Vertex v_max = Vertex(it2->getX(), it2->getY(), it2->getZ(), false);
			cout<<v_max.getX()<<v_max.getY()<<endl;
			std::vector<Vertex>::iterator itVertex = std::find(vertices.begin(), vertices.end(),v_max);
		//if (itVertex != vertices.end())
			itVertex->setVisited(true);

			for (unsigned i =0; i < vertices.size(); i++){
				if(!vertices[i].isVisited());
					cout<<"A"<<endl;
			}
			cout<<"kkk"<<endl;
			
			for (unsigned i = 0; i < facets.size(); i++ ){
				if (facets[i].vertexIntoEquation(v_max) > 0) {
					tempFacets.push_back(facets[i]);
					facets[i].setVisible(false);
				}
			}

			cout<<tempFacets.size()<<endl;

			unsigned l = 0;
			while (l < facets.size() ){
				if (facets[l].getVisible() == false)  {
					facets.erase(facets.begin() + l);
					continue;
				}
				l++;
			}

			cout<<"ilosc facets po wywaleniu"<<facets.size()<<endl;

			//horyzont

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

			//koniec horyzontu
			cout<<"ile krawedzi do dodania"<<tempEdges.size()<<endl;
			for (unsigned l = 0; l < tempEdges.size(); l++) {
				Facet f = Facet(tempEdges[l].getV1(),tempEdges[l].getV2(),v_max);
				f.setVisible(true);
				facets.push_back(f);
				facetsToGo.push(f);
			}

			cout<<"facetsToGo"<<facetsToGo.size()<<endl;
			cout<<"facets normal"<<facets.size()<<endl;

			it2 = it->second.erase(it2);
			cout<<"ile punktow trzeba sprawdzic"<<it->second.size()<<endl;

			int for_how_many = 0;

			it = facetsMap.find(facetsToGo.front().toString());

			if (it->second.size() > 0) {
			cout<<"P"<<endl;
				for (vector <Vertex>::iterator inner_iter = it->second.begin(); inner_iter !=it->second.end();) {
					Vertex v = Vertex(inner_iter->getX(),inner_iter->getY(),inner_iter->getZ(),false);
					for (unsigned i = 0; i < facets.size(); i++) {
					cout<<"a"<<endl;
						if (facets[i].vertexIntoEquation(v) < 0 ) {
							for_how_many++;
						cout<<facets[i].vertexIntoEquation(v)<<endl;
						}
					}

					if (for_how_many == facets.size()) {
						cout<<"fff"<<endl;
						inner_iter = it->second.erase(inner_iter);	
						std::vector<Vertex>::iterator itVertex;
					//zaznacz jako odwiedzony
						Vertex v_max = Vertex(it2->getX(), it2->getY(), it2->getZ(), false);
						itVertex = std::find(vertices.begin(), vertices.end(),v_max);
						itVertex->setVisited(true);

					}
					else {
						++inner_iter;
					
					}
					for_how_many = 0;
				}
			}
		
			if (it->second.size() > 0) {
				for (vector <Vertex>::iterator inner_iter = it->second.begin(); inner_iter !=it->second.end(); inner_iter ++) {
					Vertex v = Vertex(inner_iter->getX(),inner_iter->getY(),inner_iter->getZ(),false);

					for (unsigned i = 0; i < facets.size(); i++) {
						if (facets[i].vertexIntoEquation(v) > 0 ) {
							facetsMap[facets[i].toString()].push_back(v);
							goto next;
						}
					}
					next:;
				}
			}


			cout<<"ppp"<<endl;
			it = facetsMap.erase(it);
			tempFacets.clear();
			tempEdges.clear();
			tempDeleted.clear();
			max_inner = 0;
			max_distance = 0.0;
			inner = 0;
			distance = 0.0;
		}
		cout<<"t"<<endl;
		facetsToGo.pop();
	}

}