/*
	*
	* Martyna Wi¹cek - Pow³oka wypuk³a
	*
*/
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
#include <windows.h>
#include <GL/gl.h>
#include <gl/glu.h>		
#include "glut.h"


float w, h, tip = 0, turn = 0;
float dist = 0;
double x0_1,z0_1,y0_1,r;


/*zmienne s³u¿¹ce do pokolorowania osi ukadu wspó³rzêdnych*/

float ORG[3] = {0,0,0};

float  XP[3] = {1,0,0}, XN[3] = {-1,0,0},
	   YP[3] = {0,1,0}, YN[3] = {0,-1,0},
	   ZP[3] = {0,0,1}, ZN[3] = {0,0,-1};

vector <Vertex> points;
vector <Vertex> modifiedPoints;
vector <Facet> facets;


/* zmiana wielkoœci okna */
void reshape (int nw, int nh) {

	w = nw;
	h = nh;

}


/*zmiana modelu - obracanie i przybli¿anie go */

void turnModel (int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_RIGHT : turn += 3; break;
		case GLUT_KEY_LEFT  : turn -= 3; break;
		case GLUT_KEY_UP    : tip -= 3; break;
		case GLUT_KEY_DOWN  : tip += 3; break;
		case GLUT_KEY_PAGE_UP : dist += 0.1; break;
		case GLUT_KEY_PAGE_DOWN : dist -= 0.1; break;
	}

}


/*rysowanie osi w lewym dolnym rogu */
void drawAxis (void) {

	glPushMatrix ();

		glTranslatef (-2.4, -1.5, -5);
		glRotatef (tip , 1,0,0);
		glRotatef (turn, 0,1,0);
		glScalef (0.25, 0.25, 0.25);

		glLineWidth (2.0);

		glBegin (GL_LINES);
		glColor3f (1,0,0); // X  - czerowna - R.
		glVertex3fv (ORG);
		glVertex3fv (XP );
		glColor3f (0,1,0); // Y - zielona - G.
		glVertex3fv (ORG);
		glVertex3fv (YP );
		glColor3f (0,0,1); // z - niebieska - B.
		glVertex3fv (ORG);
		glVertex3fv (ZP );
		glEnd();

	glPopMatrix ();

}


/*rysowanie punktów*/
void drawPoints (void) {

	glPushMatrix ();

		glTranslatef (0, 0, -5 + dist);
		glRotatef (tip , 1,0,0);
		glRotatef (turn, 0,1,0);

		//wygenerowane punkty
		glPointSize(3.0f);
		
		glBegin( GL_POINTS );
			glColor3f( 0, 0, 1 );
			for ( vector<Vertex>::iterator it = points.begin(); it != points.end(); it++) {
				glVertex3f(it->getX(),it->getY(),it->getZ());
			}
		glEnd();


		//punkty o wokselizacji
		glPointSize(3.0f);
		glBegin( GL_POINTS );
			glColor3f( 1, 0, 0 );
			for ( vector<Vertex>::iterator it = modifiedPoints.begin(); it != modifiedPoints.end(); it++) {
				glVertex3f(it->getX(),it->getY(),it->getZ());
			}
		glEnd();
	glPopMatrix ();

}


/*rysowanie œcian*/
void drawFacets(void) {

	glPushMatrix ();


		glTranslatef (0, 0, -5 + dist);
		glRotatef (tip , 1,0,0);
		glRotatef (turn, 0,1,0);
			

		//pokolorowane œciany
			for ( vector<Facet>::iterator it = facets.begin(); it != facets.end(); it++) {
			/*	glBegin(GL_TRIANGLES);
				//	glLineWidth(0.5f);
					glColor3f(0.75,0.75,0.75);
					glVertex3f(it->getV1().getX(),it->getV1().getY(),it->getV1().getZ());		// Top
					glVertex3f(it->getV2().getX(),it->getV2().getY(),it->getV2().getZ());		// Bottom Left
					glVertex3f(it->getV3().getX(),it->getV3().getY(),it->getV3().getZ());
				glEnd();*/
				
		//krawêdzie ³¹cz¹ce punkty œcian
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


/*narysuj na ekranie*/
void display (void) {

	glViewport (0, 0, w, h);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawPoints ();
	drawFacets();
	drawAxis ();

	glutSwapBuffers ();

}


/*wczytaj punkty z pliku*/
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


/*wczytaj œciany z pliku*/
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


/*inicjalizuj*/
void init(string s1, string s2,string s3) {

	//wczytaj punkty
	readPointsFromFile(s1,points);
	readPointsFromFile(s2,modifiedPoints);
	readFacetsFromFile(s3);
	
	//zrób coœ z oknem
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


/*opcja w menu - wczytanie rêczne*/
void option1() {

	string s1, s2,s3;
	s2 = "minimized.txt";
	int voxel_number;
	double time;

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

		ConvexHull q = ConvexHull();
		time = q.buildIncrementalHull(s2,s3);

	} else {

		ConvexHull q = ConvexHull();
		time = q.buildQuickHull(s2,s3);

	}
	cout<<time<<endl;
	init(s1,s2,s3);

}

/*opcja 2 - generuj punkty */

void option2() {

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

		ConvexHull q = ConvexHull();
		time = q.buildIncrementalHull(s2,s3);

	} else {
		
		ConvexHull q = ConvexHull();
		time = q.buildQuickHull(s2,s3);

	}
	
	init(s1,s2,s3);

}


/*opcja 3 - generuj i poka¿ czas*/
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

		ConvexHull q = ConvexHull();
		time = q.buildIncrementalHull(s2,s3);

	} else {

		ConvexHull q = ConvexHull();
		time = q.buildQuickHull(s2,s3);

	}
	
	cout<<"Algorytm dziala "<<time<<" sekund."<<endl;
	//init(s1,s2,s3);

}


/*funkcja obs³uguj¹ca proste menu programu*/
int menu() {        

	cout <<endl<< "1: Wczytaj dane z pliku" <<endl<< endl;      
    cout << "2: Wygeneruj dane" <<endl<< endl;
    cout << "3: Wygeneruj i uruchom z pomiarem czasu" <<endl<< endl;
    cout << "4: EXIT" <<endl<< endl;

    int key;
    cin >> key; 

    switch(key) {
        case 1: option1();       
            cin>>key;
			break;
        case 2: option2(); 
                break;
		case 3: option3(); 
                break;
    }

    return key;            
}


int main () {

	int wyjscie = 0;  

	//cos robimy a¿ nie bêdzie to 4 albo koniec algorytmu
    do {
		wyjscie = menu();     
	} while (wyjscie != 4);  

                           
    system("PAUSE");
    return 0;
	
}