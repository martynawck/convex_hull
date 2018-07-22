//  OpenGL problem
/*
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

void passive(int,int);
void reshape(int,int);
void init(void);
void display(void);
void camera(void);

int cursorX,cursorY,width,height;
double centerX,centerY,centerZ;
//GLfloat modelviewMatrix[16],projectionMatrix[16];
GLdouble modelviewMatrix[16],projectionMatrix[16];
GLint viewport[4];
/*
int main (int argc,char **argv) {
    glutInit (&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(1364,689);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Sample");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutPassiveMotionFunc(passive);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}*/
/*
void display() {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Render 3D content
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(GLfloat)width/(GLfloat)height,1.0,100.0);    // create 3D perspective projection matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    camera();
    glTranslatef(-6,-2,0);
    glColor3f(1,0,0);
    glutSolidSphere(5,50,50);
    glPopMatrix();

    glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);
    // get 3D coordinates based on window coordinates  
    gluProject(-6, -2, 0, modelviewMatrix, projectionMatrix, viewport, &centerX, &centerY, &centerZ);

    // Render 2D content
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width,height, 0);                 // create 2D orthographic projection matrix
    glMatrixMode(GL_MODELVIEW);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2f( centerX,centerY );          // coordinate of center of the sphere in orthographic projection
        glVertex2f( cursorX,cursorY );
    glEnd();

    glutSwapBuffers();
}

void camera(void) {
    glRotatef(0.0,1.0,0.0,0.0);
    glRotatef(0.0,0.0,1.0,0.0);
    glTranslated(0,0,-20);
}

void init(void) {
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_COLOR_MATERIAL);
}

void reshape(int w, int h) {
    width=w; height=h;
}

void passive(int x1,int y1) {
    cursorX=x1; cursorY=y1;
}*/