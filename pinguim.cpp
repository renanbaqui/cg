/*
 * pinguim.cpp
 *
 *  Created on: 29 de mar de 2021
 *      Author: Flavia, Renan e Silvio
 */
#include <GL/glut.h>
#include <math.h>
const double PI = 3.1415926535898;

int frameNumber = 0;

void init();
void display();
void keyboard(unsigned char key, int x, int y);

GLint wsize_x = 750;
GLint wsize_y = 550;

float xPos, yPos;

void init() {
  // define a cor de background da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-6, 6, -6, 6, -6, 6);

}

// rotinas para conversao de coordenadas do mouse
float Xc(float x){
	xPos = x*(12.0/wsize_x) -6;
	return xPos;
}

float Yc(float y){
	yPos = 6 - y*(12.0/wsize_y);
	return yPos;
}

void grama()
{
  glBegin(GL_POLYGON);
  glVertex3f(Xc(5.0), Yc(540.0), 0.0);
  glVertex3f(Xc(5.0), Yc(429.0), 0.0);
  glVertex3f(Xc(374.0), Yc(429.0), 0.0);
  glVertex3f(Xc(374.0), Yc(540.0), 0.0);
  glEnd();
}

void agua()
{
  glBegin(GL_POLYGON);
  glVertex3f(Xc(375.0), Yc(429.0), 0.0);
  glVertex3f(Xc(375.0), Yc(540.0), 0.0);
  glVertex3f(Xc(745.0), Yc(540.0), 0.0);
  glVertex3f(Xc(745.0), Yc(429.0), 0.0);
  glEnd();
}

void circulo(double raio)
{
	int pontos = 100;
  	double ang = 0;
  	int i = 0;
  	glBegin(GL_POLYGON);
  		for (i = 0; i < pontos; i++) {
  			ang = 2*PI*i / pontos;
  			glVertex2f(cos(ang)*raio, sin(ang)*raio);
  		}
  	glEnd();

}

void triangulo()
{
	glBegin(GL_POLYGON);
	glVertex2f( 0.0f, 0.0f);
	glVertex2f( 0.25f, 0.75f);
	glVertex2f( 0.50f, 0.0f);
	glEnd();
}

void cabeca()
{
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f( 0.8f, 0.5f);
	glVertex2f( 1.32f, -0.5f);
	glVertex2f( -0.8f, -0.5f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 0.8, 0.0);
	circulo(1);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.5, 0.3, 0.0);
	circulo(0.3);
	glPopMatrix();
}
void corpo()
{
	glColor3f(0.0, 0.0, 0.0);
	glScalef(1.0, 2.0, 0.0);
	circulo(1);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.3, 0.0, 0.0);
	glScalef(0.5, 0.8, 0.0);
	circulo(1);
}

void pata()
{
  	glColor3f(0.7, 0.0, 0.0);
  	glPushMatrix();
	glTranslatef(-0.60, -2.55, 0.0);
	triangulo();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.10, -2.55, 0.0);
	triangulo();
	glPopMatrix();
}

void pinguim()
{
	glPushMatrix();
	glTranslatef(0.1, 2.5, 0.0);
	glScalef(0.5, 0.5, 0.0);
	cabeca();
	glPopMatrix();
	pata();
	corpo();
}

void filhote()
{
	// Cabeça
	glPushMatrix();
	glTranslatef(0.0, 1.5, 0.0);
	glScalef(0.7, 0.7, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f( 0.8f, 0.5f);
	glVertex2f( 1.32f, -0.5f);
	glVertex2f( -0.8f, -0.5f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.5, 0.0);
	glScalef(0.7, 0.7, 0.0);
	glColor3f(0.0, 0.8, 0.0);
	circulo(1);
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.5, 0.3, 0.0);
	circulo(0.3);
	glPopMatrix();

	// Corpo
	glTranslatef(0.0, -0.7, 0.0);
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glScalef(1.0, 1.5, 0.0);
	circulo(1);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.3, 0.0, 0.0);
	glScalef(0.5, 0.6, 0.0);
	circulo(1);
	glPopMatrix();
    // Patas
	glTranslatef(0.0, 0.5, 0.0);
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	pata();
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.0, 0.725, 0.0);
	grama();

	glColor3f(0.0, 0.0, 1.0);
	agua();

	glPushMatrix();
	glTranslatef(-1.0, -2.4, 0.0);
	glScalef(0.4, 0.4, 0.0);
	pinguim();
	glPopMatrix();

	glTranslatef(-5.0, -2.8, 0.0);
	glScalef(0.2, 0.2, 0.0);
	filhote();

	glutSwapBuffers();
}

int main(int argc, char** argv) {

  //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
  //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
  glutInit(&argc, argv);

  //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
  // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
  // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
  glutInitWindowSize(wsize_x, wsize_y);
  glutInitWindowPosition(100, 100);

  // Cria uma janela e define seu título
  glutCreateWindow("Trabalho");

  //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
  init();

  // Define display() como a função de desenho (display callback) para a janela corrente.
  // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
  glutDisplayFunc(display);

  // Indica que sempre que uma tecla for pressionada no teclado, GLUT deverá chama a função keyboard() para tratar eventos de teclado (keyboard callback).
  // A função de teclado deve possuir o seguinte protótipo:
  //glutKeyboardFunc(keyboard);

  //Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}
