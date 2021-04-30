// https://cs.lmu.edu/~ray/notes/openglexamples/
// g++ litsolids.cpp -lX11 -lGL -lGLU -lglut -g -Wall -O2 -o r.exe
//
// This program shows three cyan objects illuminated with a single yellow
// light source.  It illustrates several of the lighting parameters.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
GLfloat x0 = 1.0, y0 = 2.0, z0 = 3.0; //Viewing-coordinate origin.
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;// Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // View-up vector.

GLint width, height;
// Clears the window and depth buffer and draws three solids.
//
// The solids are placed so that they either sit or float above the x-z plane;
// therefore note one of the first things that is done is to rotate the whole
// scene 20 degrees about x to turn the top of the scene toward the viewer.
// This lets the viewer see how the torus goes around the cone.
void torus_cone(){
  glPushMatrix();

  // Rotate the scene so we can see the tops of the shapes.
  glRotatef(-20.0, 1.0, 0.0, 0.0);

  // Make a torus floating 0.5 above the x-z plane.  The standard torus in
  // the GLUT library is, perhaps surprisingly, a stack of circles which
  // encircle the z-axis, so we need to rotate it 90 degrees about x to
  // get it the way we want.
  glPushMatrix();
  glTranslatef(-0.75, 0.5, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glutSolidTorus(0.275, 0.85, 16, 40);
  glPopMatrix();

  // Make a cone.  The standard cone "points" along z; we want it pointing
  // along y, hence the 270 degree rotation about x.
  glPushMatrix();
  glTranslatef(-0.75, -0.5, 0.0);
  glRotatef(270.0, 1.0, 0.0, 0.0);
  glutSolidCone(1.0, 2.0, 70, 12);
  glPopMatrix();

  // Add a sphere to the scene.
  glPushMatrix();
  glTranslatef(0.75, 0.0, -1.0);
  glutSolidSphere(1.0, 30, 30);
  glPopMatrix();

  glPopMatrix();
}
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //bottom left
  glViewport(0, 0, width/2, height/2);
  glLoadIdentity();
  //   gluLookAt(1, 2, 1, 1, 1, 0, 0, 1, 0);
  gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
  torus_cone();
  //top left
  glViewport(0, height/2, width/2, height/2);
  glLoadIdentity();
  //   gluLookAt(1, 2, 1, 1, 1, 0, 0, 1, 0);
  gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
  torus_cone();
  //top right
  glViewport(width/2, height/2, width/2, height/2);
  glLoadIdentity();
  //   gluLookAt(1, 2, 1, 1, 1, 0, 0, 1, 0);
  gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
  torus_cone();
  //bottom right
  glViewport(width/2, 0, width/2, height/2);
  glLoadIdentity();
  //   gluLookAt(1, 2, 1, 1, 1, 0, 0, 1, 0);
  gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
  torus_cone();
  glFlush();
}
void keyboard (unsigned char key, int x, int y){
  switch (key) {
  case 'x':
    x0 += 0.2;
    cout << "x0: "<<x0<<endl;
    break;
  case 'X':
    x0 -= 0.2;
    cout << "x0: "<<x0<<endl;
    break;
  case 'y':
    y0 += 0.2;
    cout << "y0: "<<y0<<endl;
    break;
  case 'Y':
    y0 -= 0.2;
    cout << "y0: "<<y0<<endl;
    break;
  case 'z':
    z0 += 0.2;
    cout << "z0: "<<z0<<endl;
    break;
  case 'Z':
    z0 -= 0.2;
    cout << "z0: "<<z0<<endl;
    break;
  case 'i':
    xref += 0.2;
    cout << "xref: "<<xref<<endl;
    break;
  case 'I':
    xref -= 0.2;
    cout << "xref: "<<xref<<endl;
    break;
  case 'j':
    yref += 0.2;
    cout << "yref: "<<yref<<endl;
    break;
  case 'J':
    yref -= 0.2;
    cout << "yref: "<<yref<<endl;
    break;
  case 'k':
    zref += 0.2;
    cout << "zref: "<<zref<<endl;
    break;
  case 'K':
    zref -= 0.2;
    cout << "zref: "<<zref<<endl;
    break;
  case 'r':
    Vx += 0.2;
    cout << "Vx: "<<Vx<<endl;
    break;
  case 'R':
    Vx -= 0.2;
    cout << "Vx: "<<Vx<<endl;
    break;
  case 's':
    Vy += 0.2;
    cout << "Vy: "<<Vy<<endl;
    break;
  case 'S':
    Vy -= 0.2;
    cout << "Vy: "<<Vy<<endl;
    break;
  case 't':
    Vz += 0.2;
    cout << "Vz: "<<Vz<<endl;
    break;
  case 'T':
    Vz -= 0.2;
    cout << "Vz: "<<Vz<<endl;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

// We don't want the scene to get distorted when the window size changes, so z =9, yref 31, x0 = 3.4, y0 = 0.3, zref=-0.46, xref = 26
// we need a reshape callback.  We'll always maintain a range of -2.5..2.5 in
// the smaller of the width and height for our viewbox, and a range of -10..10
// for the viewbox depth.
void reshape(GLint w, GLint h) {
  //glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  width = w, height = h;
  GLfloat aspect = GLfloat(w) / GLfloat(h);
  glLoadIdentity();
//   if (w <= h) {
//     // width is smaller, so stretch out the height
//     glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
//   } else {
//     // height is smaller, so stretch out the width
//     glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
//   }
  gluPerspective(50, aspect, 0.2, 50.0);
  glMatrixMode(GL_MODELVIEW);
}

// Performs application specific initialization.  It defines lighting
// parameters for light source GL_LIGHT0: black for ambient, yellow for
// diffuse, white for specular, and makes it a directional source
// shining along <-1, -1, -1>.  It also sets a couple material properties
// to make cyan colored objects with a fairly low shininess value.  Lighting
// and depth buffer hidden surface removal are enabled here.
void init() {
  GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
  GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);

  glLightfv(GL_LIGHT0, GL_AMBIENT, black);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glLightfv(GL_LIGHT0, GL_POSITION, direction);

  glEnable(GL_LIGHTING);                // so the renderer considers light
  glEnable(GL_LIGHT0);                  // turn LIGHT0 on
  glEnable(GL_DEPTH_TEST);              // so the renderer considers depth
}

// The usual application statup code.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Cyan Shapes in Yellow Light");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  init();
  glutKeyboardFunc(keyboard);
  glutMainLoop();
}
