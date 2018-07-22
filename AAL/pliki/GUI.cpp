#include <stdio.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include "IncrementalHull.h"
//#include "QuickHull.h"
#include <stdlib.h>
#include <GL/glut.h>

float w, h, tip = 0, turn = 0;
double x0_1,z0_1,y0_1,r;

float ORG[3] = {0,0,0};

float  XP[3] = {1,0,0}, XN[3] = {-1,0,0},
	   YP[3] = {0,1,0}, YN[3] = {0,-1,0},
	   ZP[3] = {0,0,1}, ZN[3] = {0,0,-1};

Vertex a;
vector <Vertex> points;
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

		
		glPointSize(4.0f);
		
		glBegin( GL_POINTS );
			glColor3f( 1, 0, 1 );

			glVertex3f(a.getX(),a.getY(),a.getZ());

		 glEnd();

		glBegin( GL_POINTS );
			glColor3f( 0, 0, 1 );
			for ( vector<Vertex>::iterator it = points.begin(); it != points.end(); it++) {
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

				/*glBegin( GL_TRIANGLES );
					glColor3f( 1, 0, 0 );
					//glLineWidth(5.0f);
				//cout<<it->getV1().getX()<<endl;
					glVertex3f(it->getV1().getX(),it->getV1().getY(),it->getV1().getZ());		// Top
					glVertex3f(it->getV2().getX(),it->getV2().getY(),it->getV2().getZ());		// Bottom Left
					glVertex3f(it->getV3().getX(),it->getV3().getY(),it->getV3().getZ());	
				glEnd();*/
				glBegin(GL_TRIANGLES);
				//	glLineWidth(0.5f);
					glColor3f(0.75,0.75,0.75);
					glVertex3f(it->getV1().getX(),it->getV1().getY(),it->getV1().getZ());		// Top
					glVertex3f(it->getV2().getX(),it->getV2().getY(),it->getV2().getZ());		// Bottom Left
					glVertex3f(it->getV3().getX(),it->getV3().getY(),it->getV3().getZ());
				glEnd();
				
			   glBegin(GL_LINES);
					glLineWidth(0.2f);
					glColor3f(0,0,0);
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

void readPointsFromFile(string s) {
	ifstream plik (s);
	double x,y,z;

		plik>>x0_1>>y0_1>>z0_1>>r;
		while(!plik.eof()) {
		 plik >> x >> y >> z;
		 if (plik.eof())
			 continue;
		 Vertex p = Vertex(x,y,z,false);
		 points.push_back(p);
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

void main (void) {
	
	IncrementalHull ih = IncrementalHull();
	//QuickHull ih = QuickHull();
	//ih.buildHull();
	ih.buildAlgorithm();
	a = Vertex(ih.middle);
	readPointsFromFile("nazwa2.txt");
	readFacetsFromFile("nazwa5.txt");
	
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
