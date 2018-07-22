/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
	*
*/
#include "ConvexHull.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <cstdio>
#include <ctime>
#include <vector>
#include <queue>
#include <map>

using namespace std;

/*konstruktory*/
ConvexHull::ConvexHull() {
}


ConvexHull::~ConvexHull() {
}


ConvexHull::ConvexHull(vector <Point> p) {

	for(vector<Point>::iterator it = p.begin(); it != p.end(); it++) {
		vertices.push_back(Vertex(it->getX(),it->getY(),it->getZ(),false));
	}

}

/*funkcja otaczaj¹ca funkcjê tworz¹c¹ algorytm przyrostowy*/
double ConvexHull::buildIncrementalHull(string s1, string s2) {

	double difference;
	clock_t start,end;
	readFromFile(s1);
	//mierzymy czas
	start = clock();
	incrementalHull();
	end = clock();
	writeToFile(s2);
	//obliczamy ró¿nicê
	difference = (end - start)/(double)CLOCKS_PER_SEC;
	return difference;

}


/*funkcja otaczaj¹ca funkcjê tworz¹c¹ algorytm quickhull*/
double ConvexHull::buildQuickHull(string s1, string s2) {

	double difference;
	clock_t start,end;
	readFromFile(s1);
	//mierzymy czas
	start = clock();
	quickHull();
	end = clock();
	writeToFile(s2);
	//czas trwania
	difference = (end - start)/(double)CLOCKS_PER_SEC;
	return difference;

}

/*wczytywanie punktów z pliku*/
void ConvexHull::readFromFile(string s) {

	ifstream plik (s);
	double x,y,z,r;

		plik>>x0>>y0>>z0>>r;
	
		while(!plik.eof()) {
		 plik >> x >> y >> z;
		 if (plik.eof())
			 continue;
		 Vertex v = Vertex(x,y,z,false);
		 vertices.push_back(v);
		}
	plik.close();

    random_device rd;
    mt19937 g(rd());
 
    //shuffle(vertices.begin(), vertices.end(), g);

}


/*zapisywanie punktów do pliku*/
void ConvexHull::writeToFile(string s) {

	ofstream plik (s);
    if( plik.good() == true ) {
	for ( vector<Facet>::iterator it = facets.begin(); it != facets.end(); it++) {
		if (it->getVisible() == true) {
		plik<<it->getV1().getX()<<" "<<it->getV1().getY()<<" "<<it->getV1().getZ()<<" "
			<<it->getV2().getX()<<" "<<it->getV2().getY()<<" "<<it->getV2().getZ()<<" "
			<<it->getV3().getX()<<" "<<it->getV3().getY()<<" "<<it->getV3().getZ()<<endl;
		}
		plik.flush();
	}
	plik.close();

	}

}


/*algorytm przyrostowy*/
void ConvexHull::incrementalHull() {

	// punkt w œrodku obliczonej ju¿ otoczki
	Vertex middle;

	double x_m = 0.0;
	double y_m = 0.0;
	double z_m = 0.0;
	
	vector<Vertex>::size_type sz = vertices.size();

	//obliczamy wspolrzedne do tego punktu odniesienia w srodku otoczki
	x_m = vertices[0].getX();
	y_m = vertices[0].getY();
	z_m = vertices[0].getZ();

	x_m = x_m + vertices[1].getX();
	y_m = y_m + vertices[1].getY();
	z_m = z_m + vertices[1].getZ();

	//sprawdzamy czy nie le¿y na taj samej linii co te 2 pierwsze punkty
	unsigned i = 2;
	while (i < sz &&(vertices[i].isColinear(vertices[0],vertices[1]))) {
		i++;
	}

	x_m = x_m + vertices[i].getX();
	y_m = y_m + vertices[i].getY();
	z_m = z_m + vertices[i].getZ();

	//zaznaczamy jako odwiedzone
	vertices[0].setVisited(true);
	vertices[1].setVisited(true);
	vertices[i].setVisited(true);

	Facet f = Facet(vertices[0],vertices[i],vertices[1]);
	f.setVisible(true);
	facets.push_back(f);

	unsigned j = 2;

	//czy nie le¿y na tej samej p³aszczyŸnie co 2 pierwsze punkty
	while ((j < sz) &&((f.halfSpace(vertices[j])==0) || (vertices[j].isVisited() == true))) {
		j++;
	}

	vertices[j].setVisited(true);

	x_m = x_m + vertices[j].getX();
	y_m = y_m + vertices[j].getY();
	z_m = z_m + vertices[j].getZ();

	//dodajemy powsta³e œciany do wektora
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

	//struktury s³u¿¹ce nam do oliczenia horyzontu i widzianych przez punkt œcian
	vector <Facet> tempFacets;
	vector <Edge> tempEdges;
	vector <Edge> tempDeleted;

	//dla kazdego wierzcholka
	for (unsigned i = 0; i < vertices.size(); i++) {

		//jesli nie jest odwiedzony
		if(!vertices[i].isVisited()){ 

			//dla kazdej sciany patrzymy czy punkt ja widzi
			for (unsigned j = 0; j < facets.size(); j++ ){
				if (facets[j].notSameSide(vertices[i],middle)) {	
					//wrzucamy do tymczasowego vectora
					tempFacets.push_back(facets[j]);
					//i zmieniamy na niewidzialna
					facets[j].setVisible(false);
				}
			}
			
			//usuwamy te niewidzialne ze zbioru
			unsigned l = 0;
			while (l < facets.size() ){
				if (facets[l].getVisible() == false)  {
					facets.erase(facets.begin() + l);
					continue;
				}
				l++;
			}

			//dla kazdej widzialnej sciany
			for (unsigned k = 0; k < tempFacets.size(); k++) {

				//znajdujemy jej 1 krawedz w zbiorze
				std::vector<Edge>::iterator e = find(tempEdges.begin(), tempEdges.end(),tempFacets[k].getE1());
				std::vector<Edge>::iterator ed = find(tempDeleted.begin(), tempDeleted.end(),tempFacets[k].getE1());
			
				//jesli nie ma to wrzucamy do zbioru krawedzi
				if ((e == tempEdges.end()) && (ed == tempDeleted.end())) {
					tempEdges.push_back(tempFacets[k].getE1());
				} else {
				//jesli jest to usuwamy ja ze zbioru krawedzi
					if (e != tempEdges.end()) {
					tempEdges.erase(e);
					tempDeleted.push_back(tempFacets[k].getE1());
					}
				}
				//znajdujemy 2 krawedz w zbiorze
				e = find(tempEdges.begin(), tempEdges.end(),tempFacets[k].getE2());
				ed = find(tempDeleted.begin(), tempDeleted.end(),tempFacets[k].getE2());
			
				//jesli nie ma wrzucamy do zbioru krawedzi
				if ((e == tempEdges.end()) && (ed == tempDeleted.end())) {
					tempEdges.push_back(tempFacets[k].getE2());
				} else {
				//jesli jest usuwamy ze zbioru
					if (e != tempEdges.end()) {
					tempEdges.erase(e);
					tempDeleted.push_back(tempFacets[k].getE2());
					}
				}

				//szukamy 3 krawedzi
				e = find(tempEdges.begin(), tempEdges.end(),tempFacets[k].getE3());
				ed = find(tempDeleted.begin(), tempDeleted.end(),tempFacets[k].getE3());
			
				//nie ma jej - wrzucamy
				if ((e == tempEdges.end()) && (ed == tempDeleted.end())) {
					tempEdges.push_back(tempFacets[k].getE3());
				} else {
				// jest - usuwamy ja
					if (e != tempEdges.end()) {

					tempEdges.erase(e);
					tempDeleted.push_back(tempFacets[k].getE3());
					}
				}				
			}

			// dla kazdej krawedzi tworzymy sciane z danym punktem i wrzucamy do zbioru scian
			for (unsigned l = 0; l < tempEdges.size(); l++) {
				Facet f = Facet(tempEdges[l].getV1(),tempEdges[l].getV2(),vertices[i]);
				f.setVisible(true);
				facets.push_back(f);
			}
		//czyszczenie przed iteracja
		tempFacets.clear();
		tempEdges.clear();
		tempDeleted.clear();
		vertices[i].setVisited(true);
		}
	}
}


/*algorytm quickhull*/
void ConvexHull::quickHull() {

	//pomocniczna mapa typu sting, zbior punktow oraz kolejka scian
	map <string, vector<Vertex> > facetsMap;
	queue <Facet> facetsToGo;

	//posortuj i znajdz punkt o wspolrzednych mniej wiecej w srodku zbioru
	sort (vertices.begin(), vertices.end(), Point::XWayToSort);
	int median = vertices.size()/2;


	//dodaj sciane clockwise
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

	//rozdziel zbior do dwoch kluczy w mapie
	for (unsigned i = 0; i < vertices.size(); i++) {
		if (vertices[i].isVisited() == false) {
			if (facets[0].vertexIntoEquation(vertices[i]) > 0) {
				facetsMap.insert(make_pair(facets[0].toString(),vector<Vertex>()));
				facetsMap[facets[0].toString()].push_back(vertices[i]);			}
			else {
				facetsMap.insert(make_pair(facets[1].toString(),vector<Vertex>()));
				facetsMap[facets[1].toString()].push_back(vertices[i]);	
			}
		}
	}

	//dodaj te sciany do kolejki
	facetsToGo.push(facets[0]);
	facetsToGo.push(facets[1]);


	int inner = 0;
	double distance = 0.0;
	double max_distance = 0.0;
	int max_inner = 0;

	//podobnie jak w poprzednim algorytmie pomocnicze wektory
	vector <Facet> tempFacets;
	vector <Edge> tempEdges;
	vector <Edge> tempDeleted;

	//dopoki niepusta kolejka
	while (!facetsToGo.empty()) {

		//znajdz w mapie odpowiednia sciane
		std::map <string,vector<Vertex>>::iterator it;
		it = facetsMap.find(facetsToGo.front().toString());

		if (it != facetsMap.end()) {

			//znajdz najwiekszy wierzcholek i jego pozycje w wartosci mapy dla konkretnego klucza
			int i = 0;
			for (vector <Vertex>::iterator inner_iter = it->second.begin(); inner_iter !=it->second.end(); inner_iter ++) {
				distance = facetsToGo.front().distanceFromVertex(Vertex(inner_iter->getX(), inner_iter->getY(), inner_iter->getZ(),false));
			
			//Vertex v = Vertex(inner_iter->getX(), inner_iter->getY(), inner_iter->getZ(),false);
				if (distance > max_distance) {
					max_distance = distance;
					max_inner = inner;
				}
				inner++;
			}


			//iterator do tego konkretnego elementu
			vector <Vertex>::iterator it2 = it->second.begin() + max_inner;
			Vertex v_max = Vertex(it2->getX(), it2->getY(), it2->getZ(), false);
			std::vector<Vertex>::iterator itVertex = std::find(vertices.begin(), vertices.end(),v_max);
		//if (itVertex != vertices.end())
			itVertex->setVisited(true);
			
			//jesli wierzcholek widzi sciane
			for (unsigned i = 0; i < facets.size(); i++ ){
				if (facets[i].vertexIntoEquation(v_max) > 0) {
					tempFacets.push_back(facets[i]);
					facets[i].setVisible(false);
				}
			}


			//usun ja z e zbioru scian
			unsigned l = 0;
			while (l < facets.size() ){
				if (facets[l].getVisible() == false)  {
					facets.erase(facets.begin() + l);
					continue;
				}
				l++;
			}

			//obliczanie horyzonu jak w powyzszym algorytmie

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

			//dla kazdej utworzonej sciany wrzucmy ja do kolejki scian oraz do zbioru scian
			for (unsigned l = 0; l < tempEdges.size(); l++) {
				Facet f = Facet(tempEdges[l].getV1(),tempEdges[l].getV2(),v_max);
				f.setVisible(true);
				facets.push_back(f);
				facetsToGo.push(f);
			}

			//iterator do konkretnego elementu
			it2 = it->second.erase(it2);

			int for_how_many = 0;

			it = facetsMap.find(facetsToGo.front().toString());

			int shift = tempEdges.size();
			//dla kazdego wierzcholka 
			if (it->second.size() > 0) {
				for (vector <Vertex>::iterator inner_iter = it->second.begin(); inner_iter !=it->second.end();) {
					Vertex v = Vertex(inner_iter->getX(),inner_iter->getY(),inner_iter->getZ(),false);
					//dla nowo dodanych scian bo dla starych na pewno jest dobrze
					for (unsigned i = 0 + shift; i < facets.size(); i++) {
						//jesli nie widac sciany to zwiekszmy zmienna
						if (facets[i].vertexIntoEquation(v) < 0 ) {
							for_how_many++;
						}
					}

					//jesli liczba scian == zmiennej to znaczy, ze wierzcholek nie widzi zadnej sciany - usuwamy go
					if (for_how_many == facets.size()) {
						inner_iter = it->second.erase(inner_iter++);
						std::vector<Vertex>::iterator itVertex;
					//zaznacz jako odwiedzony
						itVertex = std::find(vertices.begin(), vertices.end(),v);
						itVertex->setVisited(true);

					}
					else {
						inner_iter++;
					
					}
					for_how_many = 0;
				}
			}
		
			if (it->second.size() > 0) {
				//dla kazdego wierzcholka
				for (vector <Vertex>::iterator inner_iter = it->second.begin(); inner_iter !=it->second.end(); inner_iter ++) {
					Vertex v = Vertex(inner_iter->getX(),inner_iter->getY(),inner_iter->getZ(),false);
					//dodajmy punkt do mapy do pierwszego klucza ktory pasuje
					for (unsigned i = 0; i < facets.size(); i++) {
						if (facets[i].vertexIntoEquation(v) > 0 ) {
							facetsMap[facets[i].toString()].push_back(v);
							break;
						}
					}
				}
			}
			
			//wyczysc przed nastepna petla w kolejce
			it = facetsMap.erase(it);
			tempFacets.clear();
			tempEdges.clear();
			for_how_many = 0;
			tempDeleted.clear();
			max_inner = 0;
			max_distance = 0.0;
			inner = 0;
			distance = 0.0;
		}
		//juz przejrzelismy, wyrzuc z kolejki
		facetsToGo.pop();
	}

}
	