#include "ConvexHull.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>

using namespace std;

ConvexHull::ConvexHull() {
}
ConvexHull::~ConvexHull() {
}
ConvexHull::ConvexHull(vector <Point> p) {
	for(vector<Point>::iterator it = p.begin(); it != p.end(); it++) {
		vertices.push_back(Vertex(it->getX(),it->getY(),it->getZ(),false));
	}

}

void ConvexHull::buildHull() {
	//readFromFile();
	//buildAlgorithm();
}

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

double ConvexHull::volume(Facet f, Vertex v) {

	double **A = new double*[4];                         // tworzymy macierz wskaŸników
	int* WK = new int[4];                              // tworzymy wiersz kolumn

	for(int i = 0; i < 4; i++) {
	    A[i] = new double[4];                       // tworzymy wiersz
	}

	A[0][0] = f.getV1().getX();
	A[0][1] = f.getV2().getX();
	A[0][2] = f.getV3().getX();
	A[0][3] = v.getX();
	A[1][0] = f.getV1().getY();
	A[1][1] = f.getV2().getY();
	A[1][2] = f.getV3().getY();
	A[1][3] = v.getY();
	A[2][0] = f.getV1().getZ();
	A[2][1] = f.getV2().getZ();
	A[2][2] = f.getV3().getZ();
	A[2][3] = v.getZ();
	A[3][0] = 1.0;
	A[3][1] = 1.0;
	A[3][2] = 1.0;
	A[3][3] = 1.0;

	for(int i = 0; i < 4; i++)                        // wype³niamy go numerami kolumn
		WK[i] = i;

	double determinant = det(4, 0, WK, A);
	double volume = determinant / 6;

	delete [] WK;                                 // usuwamy tablice dynamiczne

	for(int i = 0; i < 4; i++) 
		delete [] A[i];
	delete [] A;

	return volume;
}

double ConvexHull::det(int n, int w, int * WK, double ** A) {
	int i, j, k, m, * KK;
	double s;

	if(n == 1) {                                   // sprawdzamy warunek zakoñczenia rekurencji
	    return A[w][WK[0]];                         // macierz 1 x 1, wyznacznik równy elementowi

	} else {

		KK = new int[n - 1];                        // tworzymy dynamiczny wektor kolumn

		s = 0;                                      // zerujemy wartoœæ rozwiniêcia
		m = 1;                                      // pocz¹tkowy mno¿nik

		for(i = 0; i < n; i++)    {                  // pêtla obliczaj¹ca rozwiniêcie
			k = 0;                                    // tworzymy wektor kolumn dla rekurencji

				for(j = 0; j < n - 1; j++) {               // ma on o 1 kolumnê mniej ni¿ WK
					if(k == i)
						k++;                         // pomijamy bie¿¹c¹ kolumnê
					KK[j] = WK[k++];                        // pozosta³e kolumny przenosimy do KK
				}
			s += m * A[w][WK[i]] * det(n - 1,w  + 1, KK, A);
			m = -m;                                   // kolejny mno¿nik
		}

		delete [] KK;                               // usuwamy zbêdn¹ ju¿ tablicê dynamiczn
		return s;                                   // ustalamy wartoœæ funkcji
	}
}