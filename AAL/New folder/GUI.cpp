#include <stdio.h>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "Generator.h"
#include "Minimizer.h"
#include "IncrementalHull.h"
#include "QuickHull.h"
#include <stdlib.h>
#include <GL/glut.h>

float w, h, tip = 0, turn = 0;
double x0_1,z0_1,y0_1,r;

float ORG[3] = {0,0,0};

float  XP[3] = {1,0,0}, XN[3] = {-1,0,0},
	   YP[3] = {0,1,0}, YN[3] = {0,-1,0},
	   ZP[3] = {0,0,1}, ZN[3] = {0,0,-1};

vector <Vertex> points;
vector <Vertex> modifiedPoints;
vector <Facet> facets;

void reshape (int nw, int nh) {
	w = nw;
	h = nh;
}

void turnModel (int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_RIGHT : turn += 3; break;
		case GLUT_KEY_LEFT  : turn -= 3; break;
		case GLUT_KEY_UP    : tip -= 3; break;
		case GLUT_KEY_DOWN  : tip += 3; break;
	}
}


void drawAxis (void) {
	glPushMatrix ();

		glTranslatef (-2.4, -1.5, -5);
		glRotatef (tip , 1,0,0);
		glRotatef (turn, 0,1,0);
		glScalef (0.25, 0.25, 0.25);

		glLineWidth (2.0);

		glBegin (GL_LINES);
		glColor3f (1,0,0); // X axis is red.
		glVertex3fv (ORG);
		glVertex3fv (XP );
		glColor3f (0,1,0); // Y axis is green.
		glVertex3fv (ORG);
		glVertex3fv (YP );
		glColor3f (0,0,1); // z axis is blue.
		glVertex3fv (ORG);
		glVertex3fv (ZP );
		glEnd();

	glPopMatrix ();
}

void drawPoints (void) {
	glPushMatrix ();

		glTranslatef (0, 0, -5);
		glRotatef (tip , 1,0,0);
		glRotatef (turn, 0,1,0);

		
		glPointSize(3.0f);
		
		glBegin( GL_POINTS );
			glColor3f( 0, 0, 1 );
			for ( vector<Vertex>::iterator it = points.begin(); it != points.end(); it++) {
				glVertex3f(it->getX(),it->getY(),it->getZ());
			}
		glEnd();

		glPointSize(3.0f);
		glBegin( GL_POINTS );
			glColor3f( 1, 0, 0 );
			for ( vector<Vertex>::iterator it = modifiedPoints.begin(); it != modifiedPoints.end(); it++) {
				glVertex3f(it->getX(),it->getY(),it->getZ());
			}
		glEnd();
	glPopMatrix ();
}

void drawFacets(void) {
	glPushMatrix ();

		glTranslatef (0, 0, -5);
		glRotatef (tip , 1,0,0);
		glRotatef (turn, 0,1,0);
			
			for ( vector<Facet>::iterator it = facets.begin(); it != facets.end(); it++) {
			/*	glBegin(GL_TRIANGLES);
				//	glLineWidth(0.5f);
					glColor3f(0.75,0.75,0.75);
					glVertex3f(it->getV1().getX(),it->getV1().getY(),it->getV1().getZ());		// Top
					glVertex3f(it->getV2().getX(),it->getV2().getY(),it->getV2().getZ());		// Bottom Left
					glVertex3f(it->getV3().getX(),it->getV3().getY(),it->getV3().getZ());
				glEnd();*/
				
			   glBegin(GL_LINES);
					glLineWidth(0.2f);
					glColor3f(0.75,0.75,0.75);
					glVertex3f(it->getV1().getX(),it->getV1().getY(),it->getV1().getZ());		// Top
					glVertex3f(it->getV2().getX(),it->getV2().getY(),it->getV2().getZ());		// Bottom Left
					glVertex3f(it->getV1().getX(),it->getV1().getY(),it->getV1().getZ());
					glVertex3f(it->getV3().getX(),it->getV3().getY(),it->getV3().getZ());
					glVertex3f(it->getV2().getX(),it->getV2().getY(),it->getV2().getZ());
					glVertex3f(it->getV3().getX(),it->getV3().getY(),it->getV3().getZ());
				glEnd();
			}
 
		 glEnd();

	glPopMatrix ();
}



void display (void) {
	glViewport (0, 0, w, h);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawPoints ();
	drawFacets();
	drawAxis ();

	glutSwapBuffers ();
}

void readPointsFromFile(string s, vector <Vertex> &v) {
	ifstream plik (s);
	double x,y,z;

		plik>>x0_1>>y0_1>>z0_1>>r;
		while(!plik.eof()) {
		 plik >> x >> y >> z;
		 if (plik.eof())
			 continue;
		 Vertex p = Vertex(x,y,z,false);
		 v.push_back(p);
		}
	plik.close();
}

void readFacetsFromFile(string s) {
	ifstream plik (s);
	double v1x,v1y,v1z,v2x,v2y,v2z,v3x,v3y,v3z;

		while(!plik.eof()) {
		 plik >> v1x>>v1y>>v1z>>v2x>>v2y>>v2z>>v3x>>v3y>>v3z;
		 if (plik.eof())
			 continue;
		 Vertex pv1 =  Vertex(v1x,v1y,v1z,false);
		 Vertex pv2 =  Vertex(v2x,v2y,v2z,false);
		 Vertex pv3 =  Vertex(v3x,v3y,v3z,false);
		 facets.push_back(Facet(pv1,pv2,pv3));
		}
	plik.close();
}

void init(string s1, string s2,string s3) {

	//IncrementalHull ih = IncrementalHull();
	//QuickHull ih = QuickHull();
	//ih.buildHull();
	//ih.buildAlgorithm();
//	a = Vertex(ih.middle);
	readPointsFromFile(s1,points);
	readPointsFromFile(s2,modifiedPoints);
	readFacetsFromFile(s3);
	
	glutInitWindowSize (700, 450);
	glutInitWindowPosition (100, 100);
	glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow ("Convex Hull 3D");
	
	glutDisplayFunc (display);
	glutIdleFunc (display);
	glutReshapeFunc (reshape);
	glutSpecialFunc (turnModel);

	glClearColor (1, 1, 1, 1);
	glEnable (GL_DEPTH_TEST);
	glMatrixMode (GL_PROJECTION);
	gluPerspective (40.0, 1.5, 1.0, 10.0);
	glMatrixMode (GL_MODELVIEW);

	glutMainLoop ();
}

void option1() {
	string s1, s2,s3;
	s2 = "minimized.txt";
	int voxel_number;

	cout<<endl<<"Podaj nazwe pliku, z ktorego chcesz wczytac dane:"<<endl;
	cin >> s1;

	cout <<"Podaj nazwe pliku, do ktorego chcesz zapisac dane"<<endl;
	cin >> s3;

	cout <<"Podaj dokladnosc z jaka chcesz wykonac pomiar (podaj n wokseli, przy zalozeniu, ze obszar zostanie podzielony na n^3 wokseli)."<<endl;
	cin >> voxel_number;

	Minimizer m = Minimizer(voxel_number);
	m.readFromFile(s1);
	m.divideIntoCubes();
	m.findAveragePoints();
	m.writeToFile(s2);

	cout<<"Podaj, ktorym algorytmem chcesz wykonac pomiar."<<endl;
	cout<<"1: Incremental Hull"<<endl;
	cout<<"2: Quick Hull"<<endl;
	
	int number;
	cin >>number;

	if (number == 1) {
		IncrementalHull q = IncrementalHull();
		double a = q.buildAlgorithm(s2,s3);
		cout << a<<endl;

	} else {
		QuickHull q = QuickHull();
		double a = q.buildAlgorithm(s2,s3);
		cout << a<< endl;

	}
	init(s1,s2,s3);
}

void option2() {
	string s1, s2, s3;
	s1 = "generated.txt";
	s2 = "minimized.txt";
	int voxel_number;
	int vertex_number;

	cout<<endl<<"Podaj liczbe punktow, ktora chcesz wygenerowac:"<<endl;
	cin >> vertex_number;

	cout<<"Podaj dokladnosc z jaka chcesz wykonac pomiar (podaj n wokseli, przy zalozeniu, ze obszar zostanie podzielony na n^3 wokseli)."<<endl;
	cin >> voxel_number;

	cout<<"Podaj w jakim obszarze chcesz wygenerowac punkty:"<<endl;
	cout<<"1: W kuli"<<endl;
	cout<<"2: W szescianie"<<endl;
	cout<<"3: Na sferze"<<endl;
	
	int number;
	cin >> number;
	
	Generator g = Generator();
	
	cout<<"Podaj nazwe pliku, do ktorego chcesz zapisac punkty:"<<endl;
	cin>>s3;
	
	if (number == 1) {
		g.generateInSphere(vertex_number,0.0,0.0,0.0,1.0);
	}
	if (number == 2) {
		g.generateInCube(vertex_number,0.0,0.0,0.0,1.0);
	}
	if (number == 3) {
		g.generateOnSphere(vertex_number,0.0,0.0,0.0,1.0);
	}
	g.writeToFile(s1);

	Minimizer m = Minimizer(voxel_number);
	m.readFromFile(s1);
	m.divideIntoCubes();
	m.findAveragePoints();
	m.writeToFile(s2);

	cout<<"Podaj, ktorym algorytmem chcesz wykonac pomiar."<<endl;
	cout<<"1: Incremental Hull"<<endl;
	cout<<"2: Quick Hull"<<endl;
	
	int number_2;
	cin >>number_2;

	if (number_2 == 1) {
		IncrementalHull q = IncrementalHull();
		double a = q.buildAlgorithm(s2,s3);

	} else {
		QuickHull q = QuickHull();
		double a = q.buildAlgorithm(s2,s3);

	}
	
	init(s1,s2,s3);
}

void option3() {

	string s1, s2, s3;
	s1 = "generated.txt";
	s2 = "minimized.txt";
	int voxel_number;
	int vertex_number;
	double time;

	cout<<endl<<"Podaj liczbe punktow, ktora chcesz wygenerowac:"<<endl;
	cin >> vertex_number;

	cout<<"Podaj dokladnosc z jaka chcesz wykonac pomiar (podaj n wokseli, przy zalozeniu, ze obszar zostanie podzielony na n^3 wokseli)."<<endl;
	cin >> voxel_number;

	cout<<"Podaj w jakim obszarze chcesz wygenerowac punkty:"<<endl;
	cout<<"1: W kuli"<<endl;
	cout<<"2: W szescianie"<<endl;
	cout<<"3: Na sferze"<<endl;
	
	int number;
	cin >> number;
	Generator g = Generator();
	
	cout<<"Podaj nazwe pliku, do ktorego chcesz zapisac punkty:"<<endl;
	cin>>s3;
	
	if (number == 1) {
		g.generateInSphere(vertex_number,0.0,0.0,0.0,1.0);
	}
	if (number == 2) {
		g.generateInCube(vertex_number,0.0,0.0,0.0,1.0);
	}
	if (number == 3) {
		g.generateOnSphere(vertex_number,0.0,0.0,0.0,1.0);
	}
	
	g.writeToFile(s1);

	Minimizer m = Minimizer(voxel_number);
	m.readFromFile(s1);
	m.divideIntoCubes();
	m.findAveragePoints();
	m.writeToFile(s2);

	cout<<"Podaj, ktorym algorytmem chcesz wykonac pomiar."<<endl;
	cout<<"1: Incremental Hull"<<endl;
	cout<<"2: Quick Hull"<<endl;
	
	int number_2;
	cin >>number_2;

	if (number_2 == 1) {
		IncrementalHull q = IncrementalHull();
		time = q.buildAlgorithm(s2,s3);

	} else {
		QuickHull q = QuickHull();
		time = q.buildAlgorithm(s2,s3);

	}
	
	cout<<"Algorytm dzia³a "<<time<<" sekund."<<endl;
	init(s1,s2,s3);
}

int menu() {         // funkcja menu zwracaj¹ca wartoœæ int

	cout <<endl<< "1: Wczytaj dane z pliku" <<endl<< endl;      // wyœwietlenie menu
    cout << "2: Wygeneruj dane" <<endl<< endl;
    cout << "3: Wygeneruj i uruchom z pomiarem czasu" <<endl<< endl;
    cout << "4: EXIT" <<endl<< endl;

    int key;
    cin >> key;  // pobranie wartoœci

    switch(key) {
        case 1: option1();       // przy wartoœci 1 wykonujemy funkcjê wstêp()
            cin>>key;
			break;
        case 2: option2(); // gdy 2 to rozwiniêcie()
                break;
		case 3: option3(); // gdy 3 to zakoñczenie()
                break;
    }

    return key;            // zwraca wartoœæ do porównania.
}


int main () {

	QuickHull q = QuickHull();
	q.buildAlgorithm("nazwa3.txt","data.txt");
	init("nazwa3.txt","nazwa3.txt","data.txt");

	/*
	int wyjscie = 0;  // tworzymy zmienn¹ int która bêdzie siê równaæ 0

    do {
		wyjscie = menu();     // wywo³anie funkcji menu()
	} while (wyjscie != 4);  // sprawdzenie co zwraca funkcja menu 

                            // gdy inna ni¿ 4 menu pojawi siê od nowa
    system("PAUSE");*/
    return 0;
	
}