#include <GL/glut.h>
#include <iostream>
using namespace std;
GLint winWidth = 600, winHeight = 600; //Initial display-window size.
GLfloat x0 = 100.0, y0 = 50.0, z0 = 50.0; //Viewing-coordinate origin.
GLfloat xref = 50.0, yref = 50.0, zref = 0.0;// Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // View-up vector.

//x0 = y0 = z0 = xref = yref = zref = 0.0;

// Set coordinate limits for the clipping window:
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;
//Set positions for near and far clipping planes:
 GLfloat dnear = 25.0, dfar = 125.0;

void init(void) {
	
	
  // glLoadIdentity();
  // gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
}
void square2D(){
  glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 100.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 100.0);
    glEnd();
	glColor3f(0.0, 1.0, 0.0);
// Set fill color to green.
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE); // Wire-frame back face.
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	glEnd();
}
void displayFcn(void) {
    glClear(GL_COLOR_BUFFER_BIT);
	/* Set parameters for a square fill area. */
    //bottom left corner
    glViewport(0, 0, winHeight/2, winWidth/2);
    glLoadIdentity();
    gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
    square2D();
    //top left corner
    glViewport(0, winHeight/2, winWidth/2, winHeight/2);
    glLoadIdentity();
    gluLookAt(50, 50, 50, 50, 50, 0, Vx, Vy, Vz);
    square2D();

    //top rigth corner
    glViewport(winWidth/2, winWidth/2, winWidth/2, winHeight/2);
    glLoadIdentity();
    gluLookAt(50, 100, 50, 50, 50, 0, Vx, Vy, Vz);
    square2D();

    //bottom right corner
    glViewport(winWidth/2,0, winWidth/2, winHeight/2);
    glLoadIdentity();
    gluLookAt(50, -20, 50, 50, 50, 0, Vx, Vy, Vz);
    square2D();
	  glFlush();
}
void reshapeFcn(GLint newWidth, GLint newHeight) {
  glMatrixMode(GL_PROJECTION);
	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
  glMatrixMode(GL_MODELVIEW);
	
	winWidth = newWidth;
	winHeight = newHeight;
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
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Perspective View of A Square");
  glClearColor(1.0, 1.0, 1.0, 0.0);
	init();
	glutDisplayFunc(displayFcn);
	glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshapeFcn);
	glutMainLoop();

 return 0;
}
