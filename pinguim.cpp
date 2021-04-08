/*
 * pinguim.cpp
 *
 *  Created on: 29 de mar de 2021
 *      Author: Renan e Silvio
 */
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <random>
//#include <chrono>
//#include <thread>


const double PI = 3.1415926535898;

int frameNumber = 0;
GLfloat moveping = 0.0, alturaping = -2.4, rotaping = 0.0, escalaping = 0.4;
GLfloat movepeixe1 = 2.5, alturapeixe1 = -3.8, rotapeixe1 = 0.0, escalapeixe1 = 0.15;
GLfloat movepeixe2 = 5.0, alturapeixe2 = -4.5, rotapeixe2 = 0.0, escalapeixe2 = 0.18;
GLfloat movepeixe3 = 1.0, alturapeixe3 = -5.5, rotapeixe3 = 0.0, escalapeixe3 = 0.18;
GLfloat movepeixe4 = 3.5, alturapeixe4 = -5.1, rotapeixe4 = 0.0, escalapeixe4 = 0.15;
GLfloat movepetrel = -5.5, alturapetrel = 4.0; // rotapetrel = 0.0, escalapetrel = 0.15;

GLint direcao = 2, direcaopeixe1 = 0, direcaopeixe2 = 0, direcaopeixe3 = 0, direcaopeixe4 = 0, direcaopetrel = 0;
GLint gerar=0, tempoConta = 2000, texto = 7.0;

GLfloat pfilx = -5.0, pfily = -2.8;

bool pesc = false;


// numeros aleatorios para as coordenadas dos pontos do petrel
GLfloat p1y, p2x, p3x, p3y, p4x, p4y;

// numeros aleatorios para as alturas dos peixes
GLfloat a1, a2, a3, a4;

std::random_device rd; 		// obtem um numero aleatorio do hardware
std::mt19937 gen(rd()); 	// alimenta o gerador

std::uniform_real_distribution<> distr(1, 4); 		// define o range // distr
std::uniform_real_distribution<> distr2(-4, -2); 	// define o range // distr2
std::uniform_real_distribution<> distr3(2, 4); 		// define o range // distr3
std::uniform_real_distribution<> distr4(3, 5); 		// define o range // distr4
std::uniform_real_distribution<> distr5(-2, -1); 	// define o range // distr5

std::uniform_real_distribution<> distr6(-5.5, -3.5); 	// define o range // distr6
std::uniform_real_distribution<> distr7(-5.5, -3.5); 	// define o range // distr7
std::uniform_real_distribution<> distr8(-5.5, -3.5); 	// define o range // distr8
std::uniform_real_distribution<> distr9(-5.5, -3.5); 	// define o range // distr9

//m�todo de geracao de coordenadas aleatorias
void gera(){

	p1y = distr(gen);
	p2x = distr2(gen);
	p3x = distr3(gen);
	p3y = distr4(gen);
	// ponto medio p2x e p3x
	p4x = ((p2x + p3x)/2);
	p4y = distr5(gen);

	a1 = distr6(gen);
	a2 = distr7(gen);
	a3 = distr8(gen);
	a4 = distr9(gen);

}

/*
GLfloat L0 = (((movepetrel-p4x)*(movepetrel-p3x))/((p2x-p4x)*(p2x-p3x)));
GLfloat L1 = (((movepetrel-p2x)*(movepetrel-p3x))/((p4x-p2x)*(p4x-p3x)));
GLfloat L2 = (((movepetrel-p2x)*(movepetrel-p4x))/((p3x-p2x)*(p3x-p4x)));
*/

void init();
void display();
void move(int passo);
void movepetrelgigante(int passo);
// alteracao na funcao keyboard para adequar a glutSpecialFunc
void keyboard(int key, int x, int y);



GLint wsize_x = 750;
GLint wsize_y = 550;

float xPos, yPos;


void init() {
  // define a cor de background da janela
  glClearColor(0.592, 0.807, 0.921, 1.0);

  // define o sistema de visualiza��o - tipo de proje��o
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

void circulovazio(double raio)
{
	int pontos = 100;
	  	double ang = 0;
	  	int i = 0;
	  	glBegin(GL_LINE_LOOP);
	  		for (i = 0; i < pontos; i++) {
	  			ang = 2*PI*i / pontos;
	  			glVertex2f(cos(ang)*raio, sin(ang)*raio);
	  		}
	  	glEnd();
}

void semicirculo(double raio)
{
	int pontos = 100;
	double ang = 0;
	int i = 0;
	glBegin(GL_POLYGON);
		for (i = 0; i < pontos; i++)
		{
		  	ang = (2*PI*i)/4 / pontos;
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
	// Cabe�a
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



void peixe()
{
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glLineWidth(3);
	glScalef(0.5, 1.5, 0.0);
	circulovazio(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -1.8, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f( 0.0f, 0.35f, 0.0f);
	glVertex3f(-0.35f,-0.35f, 0.0f);
	glVertex3f( 0.35f,-0.35f, 0.0f);
	glEnd();
	glPopMatrix();
}

void passaro()
{
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 0.0);
	glRotatef(52.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.9, 0.0);
	semicirculo(1);
	glPopMatrix();
	glPushMatrix();
	glScalef(1.0, 1.0, 0.0);
	glRotatef(38.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.9, 0.0, 0.0);
	semicirculo(1);
	glPopMatrix();
}

void pinguimcompeixe()
{
	glPushMatrix();
	glTranslatef(0.7, 2.3, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(0.165, 0.4, 0.0);
	peixe();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.1, 2.5, 0.0);
	glScalef(0.5, 0.5, 0.0);
	cabeca();
	glPopMatrix();
	pata();
	corpo();
}

void pescado()
{
	glPushMatrix();
	glTranslatef((moveping + 0.38), alturaping + 0.8, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(0.14, 0.14, 0.0);
	peixe();
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
    // pinguim
	glPushMatrix();
	glTranslatef(moveping, alturaping, 0.0);
	glRotatef(rotaping, 0.0, 0.0, 1.0);
	glScalef(escalaping, 0.4, 0.0);
	pinguim();
	glPopMatrix();
    // filhote
	glPushMatrix();
	glTranslatef(pfilx, pfily, 0.0);
	glScalef(0.2, 0.2, 0.0);
	filhote();
	glPopMatrix();
    // peixe1
	glPushMatrix();
	glTranslatef(movepeixe1, alturapeixe1, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(0.15, escalapeixe1, 0.0);
	peixe();
	glPopMatrix();
    // peixe2
	glPushMatrix();
	glTranslatef(movepeixe2, alturapeixe2, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(0.18, escalapeixe2, 0.0);
	peixe();
	glPopMatrix();
    // peixe3
	glPushMatrix();
	glTranslatef(movepeixe3, alturapeixe3, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	glScalef(0.18, escalapeixe3, 0.0);
	peixe();
	glPopMatrix();
    // peixe4
	glPushMatrix();
	glTranslatef(movepeixe4, alturapeixe4, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	glScalef(0.15, escalapeixe4, 0.0);
	peixe();
	glPopMatrix();
	// passaro petrel
	glPushMatrix();
	glTranslatef(movepetrel, alturapetrel, 0.0); // p1y = alturapetrel
	glScalef(1.0, 1.0, 0.0);
	passaro();
	glPopMatrix();

    // mensagem fim de jogo
	glColor4f(1.0, 0.0, 0.0, 0.0);
	const unsigned char* t = reinterpret_cast<const unsigned char *>("FIM DE JOGO");
    glRasterPos2i( -1.8, texto );
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);

    if (pesc==true)
	{
		// pinguim com peixe na boca
		glPushMatrix();
		glTranslatef(moveping, alturaping, 0.0);
		glRotatef(rotaping, 0.0, 0.0, 1.0);
		glScalef(escalaping, 0.4, 0.0);
		pinguimcompeixe();
		glPopMatrix();
	}

	if (moveping <= pfilx + 0.5)
	{
		pesc = false;
		glPushMatrix();
		glTranslatef(moveping, alturaping, 0.0);
		glRotatef(rotaping, 0.0, 0.0, 1.0);
		glScalef(escalaping, 0.4, 0.0);
		pinguim();
		glPopMatrix();
	}

    glutSwapBuffers();
}

void keyboard(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_LEFT:
	direcao = 0;
	//exit(0);
	break;
  case GLUT_KEY_RIGHT:
	direcao = 1;
	//exit(0);
	break;
  case GLUT_KEY_UP:
	direcao = 3;
	//exit(0);
	break;
  case GLUT_KEY_DOWN:
	direcao = 4;
	//exit(0);
	break;
  default:
    direcao = 2;
    break;
  }
}
// movimentacao pinguim
void move(int passo)
{
	if(direcao==1)
	{
		moveping += (float)passo/50;
		escalaping = 0.4;
		// limite direito de movimento
		if(moveping>0.5){
	      direcao = 0;
		  rotaping = 0;
		}
	}
	if(direcao==0)
	{
		moveping -= (float)passo/50;
		escalaping = -0.4;
		// limite esquerdo de movimento
		if(moveping<-5.5)
			direcao = 1;
	}
	if(direcao==2)
	{
		moveping += 0;
	}
	// ao entrar na agua o pinguim eh rotacionado e muda posicao
	if(moveping>0.0){
		rotaping = 270;
	//	alturaping = -4.0;
		// nadando para cima
		if(direcao==3){
			alturaping += (float)passo/50;
			escalaping = -0.4;
		}
		// nadando para baixo
		if(direcao==4){
			alturaping -= (float)passo/50;
			escalaping = 0.4;
		}
		// limite superior
		if(alturaping>-3.5)
			alturaping = -3.5;
        // limite inferior
		if(alturaping<-5.5)
			direcao = 3;
	}
	// ao entrar na grama o pinguim eh rotacionado e muda posicao
	if(moveping<0.0){
		rotaping = 0;
		alturaping = -2.4;
    // se o pinguim estiver na agua e nadando para esquerda, rotaciona para olhar para baixo
	}
	if(direcao==0 && moveping>0.0){
		rotaping = 90;
	}

	if ((moveping + 0.95 >= movepeixe1 - 0.5) && (alturaping < alturapeixe1 + 0.5 && alturaping > alturapeixe1 - 0.5) && pesc == false){
		pesc = true;
	    alturapeixe1 = a1;
	}
	else if ((moveping + 0.95 >= movepeixe2 - 0.5) && (alturaping < alturapeixe2 + 0.5 && alturaping > alturapeixe2 - 0.5) && pesc == false){
		pesc = true;
		alturapeixe2 = a2;
	}
	else if ((moveping + 0.95 >= movepeixe3 - 0.5) && (alturaping < alturapeixe3 + 0.5 && alturaping > alturapeixe3 - 0.5) && pesc == false){
		pesc = true;
		alturapeixe3 = a3;
	}
	else if ((moveping + 0.95 >= movepeixe4 - 0.5) && (alturaping < alturapeixe4 + 0.5 && alturaping > alturapeixe4 - 0.5) && pesc == false){
		pesc = true;
		alturapeixe4 = a4;
	}	
	

// tentativa de consertar bug que quando esta nadando para o lado esquerdo e digita qualquer tecla, ele olha para cima
//	if(direcao==2 && moveping>0.0){
//		rotaping = 90;
//	}

glutPostRedisplay();
glutTimerFunc(10,move,1);
}
// movimentacao peixe1
void move2(int passo){
	//movimenta para direita
	if(direcaopeixe1==0)
	{
		movepeixe1 += (float)passo/50;
		escalapeixe1 = -0.15;
		// limite direito
		if(movepeixe1>5.5)
			direcaopeixe1 = 1;
	}
	//movimenta para esquerda
	if(direcaopeixe1==1)
	{
		movepeixe1 -= (float)passo/50;
		escalapeixe1 = 0.15;
		// limite esquerdo
		if(movepeixe1<0.5)
			direcaopeixe1 = 0;
	}
glutPostRedisplay();
glutTimerFunc(10,move2,1);
}

void move3(int passo){
	//movimenta para direita
	if(direcaopeixe2==0)
	{
		movepeixe2 += (float)passo/50;
		escalapeixe2 = -0.18;
		// limite direito
		if(movepeixe2>5.5)
			direcaopeixe2 = 1;
	}
	//movimenta para esquerda
	if(direcaopeixe2==1)
	{
		movepeixe2 -= (float)passo/50;
		escalapeixe2 = 0.18;
		// limite esquerdo
		if(movepeixe2<0.5)
			direcaopeixe2 = 0;
	}
glutPostRedisplay();
glutTimerFunc(10,move3,1);
}

void move4(int passo){
	//movimenta para direita
	if(direcaopeixe3==0)
	{
		movepeixe3 += (float)passo/50;
		escalapeixe3 = 0.18;
		// limite direito
		if(movepeixe3>5.5)
			direcaopeixe3 = 1;
	}
	//movimenta para esquerda
	if(direcaopeixe3==1)
	{
		movepeixe3 -= (float)passo/50;
		escalapeixe3 = -0.18;
		// limite esquerdo
		if(movepeixe3<0.5)
			direcaopeixe3 = 0;
	}
glutPostRedisplay();
glutTimerFunc(10,move4,1);
}

void move5(int passo){
	//movimenta para direita
	if(direcaopeixe4==0)
	{
		movepeixe4 += (float)passo/50;
		escalapeixe4 = 0.15;
		// limite direito
		if(movepeixe4>5.5)
			direcaopeixe4 = 1;
	}
	//movimenta para esquerda
	if(direcaopeixe4==1)
	{
		movepeixe4 -= (float)passo/50;
		escalapeixe4 = -0.18;
		// limite esquerdo
		if(movepeixe4<0.5)
			direcaopeixe4 = 0;
	}
glutPostRedisplay();
glutTimerFunc(10,move5,1);
}


void movepetrelgigante(int passo){

	//movimenta para direita
	if(direcaopetrel==0)
	{
		// quando muda a direcao novas coordenadas sao geradas
		if(gerar==1){
		    gera();
			gerar=0;
		}

		movepetrel += (float)passo/50;
		// movimento parabolico com interpolacao polinomial
	    if(p2x<movepetrel && movepetrel<p3x){

	    	//alturapetrel = (pow (movepetrel, 2.00)) - 2;
	    	GLfloat L0 = (((movepetrel-p4x)*(movepetrel-p3x))/((p2x-p4x)*(p2x-p3x)));
	    	GLfloat L1 = (((movepetrel-p2x)*(movepetrel-p3x))/((p4x-p2x)*(p4x-p3x)));
	    	GLfloat L2 = (((movepetrel-p2x)*(movepetrel-p4x))/((p3x-p2x)*(p3x-p4x)));
	    	alturapetrel = ((p1y*L0) + (p4y*L1) + (p3y*L2));
	    }

	    // limite direito
	    if(movepetrel>5.5){
	        direcaopetrel=1;
	    }
	 }
	/*	escalapetrel = ;
		 limite direito
		if(movepetrel>8.0)
			direcaopetrel = 1;
		if(movepetrel>7.5)
			alturapetrel = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    */

//	movimenta para esquerda
	if(direcaopetrel==1)
	{
	    // quando muda a direcao novas coordenadas sao geradas
		if(gerar==0){
		    gera();
			gerar=1;
		}
		movepetrel -= (float)passo/50;
	    if(p2x<movepetrel && movepetrel<p3x){

	    	//alturapetrel = (pow (movepetrel, 2.00)) - 2;
	    	GLfloat L0 = (((movepetrel-p4x)*(movepetrel-p3x))/((p2x-p4x)*(p2x-p3x)));
	    	GLfloat L1 = (((movepetrel-p2x)*(movepetrel-p3x))/((p4x-p2x)*(p4x-p3x)));
	    	GLfloat L2 = (((movepetrel-p2x)*(movepetrel-p4x))/((p3x-p2x)*(p3x-p4x)));
	    	alturapetrel = ((p1y*L0) + (p4y*L1) + (p3y*L2));
	    }
	    // limite esquerdo
	    if(movepetrel<-5.5){
	        direcaopetrel=0;
	    }
	}
		// escalapetrel = ;
		// limite esquerdo
	//	if(movepetrel<-8.0)
	//		direcaopetrel = 0;
      //  if(movepetrel<-7.5)
        //
		//if(movepetrel<4){
		//	alturapetrel = (pow (movepetrel, 2.00)) - 2;
		//}
	//}*/

    	//alturapetrel = (pow (movepetrel, 2.00)) - 2;

glutPostRedisplay();
glutTimerFunc(10,movepetrelgigante,1);
}

// tempo de jogo
void tempo(int passo){
	tempoConta -= (float)passo/50;

	if(tempoConta<100){
		moveping = -3.0;
		movepetrel = 0.0;
		alturapetrel = 1.0;
		texto = 4.0;
	}

	glutPostRedisplay();
	glutTimerFunc(10,tempo,1);
}


int main(int argc, char** argv) {

  // necessario para o numero aleatorio
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  gera();
  //Inicializa a biblioteca GLUT e negocia uma se��o com o gerenciador de janelas.
  //� poss�vel passar argumentos para a fun��o glutInit provenientes da linha de execu��o, tais como informa��es sobre a geometria da tela
  glutInit(&argc, argv);

  //Informa � biblioteca GLUT o modo do display a ser utilizado quando a janela gr�fica for criada.
  // O flag GLUT_SINGLE for�a o uso de uma janela com buffer simples, significando que todos os desenhos ser�o feitos diretamente nesta janela.
  // O flag GLUT_RGB determina que o modelo de cor utilizado ser� o modelo RGB.
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  //Define o tamanho inicial da janela, 256x256 pixels, e a posi��o inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
  glutInitWindowSize(wsize_x, wsize_y);
  glutInitWindowPosition(100, 100);

  // Cria uma janela e define seu t�tulo
  glutCreateWindow("Trabalho");

  //Nesta fun��o � definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usu�rio nessa fun��o.
  init();

  // Define display() como a fun��o de desenho (display callback) para a janela corrente.
  // Quando GLUT determina que esta janela deve ser redesenhada, a fun��o de desenho � chamada.
  glutDisplayFunc(display);

  // movimentacao pinguim
  glutTimerFunc(10,move,1);
  // movimentacao peixe1
  glutTimerFunc(10,move2,1);
  // movimentacao peixe2
  glutTimerFunc(10,move3,1);
  // movimentacao peixe3
  glutTimerFunc(10,move4,1);
  // movimentacao peixe4
  glutTimerFunc(10,move5,1);
  // movimentacao petrel
  glutTimerFunc(10,movepetrelgigante,1);
  // tempo de jogo
  glutTimerFunc(10,tempo,1);


  // Indica que sempre que uma tecla for pressionada no teclado, GLUT dever� chama a fun��o keyboard() para tratar eventos de teclado (keyboard callback).
  // A fun��o de teclado deve possuir o seguinte prot�tipo:
  // glutKeyboardFunc(keyboard);

  // Funcao especial do GLUT para teclas de setas
  glutSpecialFunc(keyboard);
  // Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}
