/*
 * pinguim.cpp
 *
 *  Created on: 29 de mar de 2021
 *      Author: Renan Almeida Baqui e Silvio Pereira dos Santos
 */
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream> 	// biblioteca auxiliar para numeros aleatorios
#include <random>		// biblioteca auxiliar para numeros aleatorios

const double PI = 3.1415926535898;

int frameNumber = 0;
// moveping = x do pinguim, alturaping = y do pinguim, rotaping = rotacao do pinguim, escalaping = escala do pinguim
GLfloat moveping = 0.0, alturaping = -2.4, rotaping = 0.0, escalaping = 0.4;
// movepeixe1 = x do peixe 1, alturapeixe1 = y do peixe 1, rotapeixe1 = rotacao do peixe 1, escalapeixe1 = escala do peixe 1
GLfloat movepeixe1 = 2.5, alturapeixe1 = -3.8, rotapeixe1 = 0.0, escalapeixe1 = 0.15;
// movepeixe2 = x do peixe 2, alturapeixe2 = y do peixe 2, rotapeixe2 = rotacao do peixe 2, escalapeixe2 = escala do peixe 2
GLfloat movepeixe2 = 5.0, alturapeixe2 = -4.5, rotapeixe2 = 0.0, escalapeixe2 = 0.18;
// movepeixe1 = x do peixe 3, alturapeixe1 = y do peixe 3, rotapeixe3 = rotacao do peixe 3, escalapeixe3 = escala do peixe 3
GLfloat movepeixe3 = 1.0, alturapeixe3 = -5.5, rotapeixe3 = 0.0, escalapeixe3 = 0.18;
// movepeixe1 = x do peixe 4, alturapeixe1 = y do peixe 4, rotapeixe4 = rotacao do peixe 4, escalapeixe4 = escala do peixe 4
GLfloat movepeixe4 = 3.5, alturapeixe4 = -5.1, rotapeixe4 = 0.0, escalapeixe4 = 0.15;
// movepetrel = x do passaro, alturapetrel = y do passado
GLfloat movepetrel = -5.5, alturapetrel = 4.0; // rotapetrel = 0.0, escalapetrel = 0.15;
// direcao = numero inteiro que da direcao do pinguim
// direcaopeixe1, direcaopeixe2, direcaopeixe3, direcaopeixe4 = numeros inteiros que dao direcao dos peixes
GLint direcao = 2, direcaopeixe1 = 0, direcaopeixe2 = 0, direcaopeixe3 = 0, direcaopeixe4 = 0, direcaopetrel = 0;
// gerar = numero inteiro que indica a geracao de numeros aleatorios
// texto, texto2, texto3, texto4 = posicao do texto na tela (inicializado em 7.0 para ficar escondido)
GLint gerar=0, texto = 7.0, texto2 = 7.0, texto3 = 7.0, texto4 = 7.0;
// tempoConta = contador de tempo total do jogo (5 minutos)
GLint tempoConta = 18000;
// tempoFilhote = contador de tempo de vida do filhote (1 minuto)
GLint tempoFilhote = 3600;

// pfilx = x do filhote, pfily = y do filhote
GLfloat pfilx = -5.0, pfily = -2.8;
// pesc = booleana se o pinguim pescou o peixe
bool pesc = false;

// p1y, p2x, p3x, p3y, p4x, p4y = numeros aleatorios para as coordenadas dos pontos do petrel
GLfloat p1y, p2x, p3x, p3y, p4x, p4y;

// a1, a2, a3, a4 = numeros aleatorios para as alturas dos peixes
GLfloat a1, a2, a3, a4;
// obtem um numero aleatorio do hardware
std::random_device rd;
// alimenta o gerador de numeros
std::mt19937 gen(rd());

std::uniform_real_distribution<> distr(1, 4); 		// funcao que define a variacao de p1y
std::uniform_real_distribution<> distr2(-4, -2); 	// funcao que define a variacao de p2x
std::uniform_real_distribution<> distr3(2, 4); 		// funcao que define a variacao de p3x
std::uniform_real_distribution<> distr4(3, 5); 		// funcao que define a variacao de p3y
std::uniform_real_distribution<> distr5(-2, -1); 	// funcao que define a variacao de p4y

std::uniform_real_distribution<> distr6(-5.5, -3.5); 	// funcao que define a variacao de a1
std::uniform_real_distribution<> distr7(-5.5, -3.5); 	// funcao que define a variacao de a2
std::uniform_real_distribution<> distr8(-5.5, -3.5); 	// funcao que define a variacao de a3
std::uniform_real_distribution<> distr9(-5.5, -3.5); 	// funcao que define a variacao de a4

// gera = funcao de geracao de coordenadas aleatorias dentro da variacao definida previamente
void gera(){

	p1y = distr(gen);
	p2x = distr2(gen);
	p3x = distr3(gen);
	p3y = distr4(gen);
	// p4x = ponto medio p2x e p3x
	p4x = ((p2x + p3x)/2);
	p4y = distr5(gen);

	a1 = distr6(gen);
	a2 = distr7(gen);
	a3 = distr8(gen);
	a4 = distr9(gen);

}

void init();
void display();
// move = funcao de movimento do pinguim
void move(int passo);
// movepetrelgigante = funcao de movimento do passaro petrel gigante
void movepetrelgigante(int passo);
// keyboard = alteracao na funcao keyboard original para adequar a glutSpecialFunc
void keyboard(int key, int x, int y);

GLint wsize_x = 750;
GLint wsize_y = 550;

// xPos, yPos = variaveis para conversao de coordenadas do mouse
float xPos, yPos;

void init() {
  // define a cor de background da janela
  glClearColor(0.592, 0.807, 0.921, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-6, 6, -6, 6, -6, 6);

}

// Xc, Yc = rotinas para conversao de coordenadas do mouse
float Xc(float x){
	xPos = x*(12.0/wsize_x) -6;
	return xPos;
}

float Yc(float y){
	yPos = 6 - y*(12.0/wsize_y);
	return yPos;
}

// grama = funcao de desenho da grama
void grama()
{
  glBegin(GL_POLYGON);
  glVertex3f(Xc(5.0), Yc(540.0), 0.0);
  glVertex3f(Xc(5.0), Yc(429.0), 0.0);
  glVertex3f(Xc(374.0), Yc(429.0), 0.0);
  glVertex3f(Xc(374.0), Yc(540.0), 0.0);
  glEnd();
}
// agua = funcao de desenho da agua
void agua()
{
  glBegin(GL_POLYGON);
  glVertex3f(Xc(375.0), Yc(429.0), 0.0);
  glVertex3f(Xc(375.0), Yc(540.0), 0.0);
  glVertex3f(Xc(745.0), Yc(540.0), 0.0);
  glVertex3f(Xc(745.0), Yc(429.0), 0.0);
  glEnd();
}
// circulo = funcao de desenho de circulo
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
// circulovazio = funcao de desenho de circulo vazio
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
// semicirculo = funcao de desenho de semi circulo
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
// triangulo = funcao de desenho de triangulo
void triangulo()
{
	glBegin(GL_POLYGON);
	glVertex2f( 0.0f, 0.0f);
	glVertex2f( 0.25f, 0.75f);
	glVertex2f( 0.50f, 0.0f);
	glEnd();
}
// cabeca = funcao de desenho de cabeca
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
// corpo = funcao de desenho de corpo
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
// pata = funcao de desenho de pata
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
// pinguim = funcao de desenho do pinguim
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
// filhote = funcao de desenho do filhote
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
// peixe = funcao de desenho do peixe
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
// passaro = funcao de desenho do passaro petrel gigante
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
// pinguimcompeixe = funcao de desenho do pinguim com peixe na boca
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
// pescado = funcao de desenho do peixe pescado
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
	// desenho da grama
	glColor3f(0.0, 0.725, 0.0);
	grama();
	// desenho da agua
	glColor3f(0.0, 0.0, 1.0);
	agua();
    // desenho do pinguim
	glPushMatrix();
	glTranslatef(moveping, alturaping, 0.0);
	glRotatef(rotaping, 0.0, 0.0, 1.0);
	glScalef(escalaping, 0.4, 0.0);
	pinguim();
	glPopMatrix();
    // desenho do filhote
	glPushMatrix();
	glTranslatef(pfilx, pfily, 0.0);
	glScalef(0.2, 0.2, 0.0);
	filhote();
	glPopMatrix();
    // desenho do peixe 1
	glPushMatrix();
	glTranslatef(movepeixe1, alturapeixe1, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(0.15, escalapeixe1, 0.0);
	peixe();
	glPopMatrix();
    // desenho do peixe 2
	glPushMatrix();
	glTranslatef(movepeixe2, alturapeixe2, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(0.18, escalapeixe2, 0.0);
	peixe();
	glPopMatrix();
    // desenho do peixe 3
	glPushMatrix();
	glTranslatef(movepeixe3, alturapeixe3, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	glScalef(0.18, escalapeixe3, 0.0);
	peixe();
	glPopMatrix();
    // desenho do peixe 4
	glPushMatrix();
	glTranslatef(movepeixe4, alturapeixe4, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	glScalef(0.15, escalapeixe4, 0.0);
	peixe();
	glPopMatrix();
	// desenho do passaro petrel gigante
	glPushMatrix();
	glTranslatef(movepetrel, alturapetrel, 0.0); // p1y = alturapetrel
	glScalef(1.0, 1.0, 0.0);
	passaro();
	glPopMatrix();

    // mensagem: fim de jogo
	glColor4f(1.0, 0.0, 0.0, 0.0);
	const unsigned char* t = reinterpret_cast<const unsigned char *>("FIM DE JOGO");
    glRasterPos2i( -1.8, texto );
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);

    // mensagem: o filhote morreu
	glColor4f(1.0, 0.0, 0.0, 0.0);
	const unsigned char* u = reinterpret_cast<const unsigned char *>("O FILHOTE MORREU");
    glRasterPos2i( -2.0, texto2 );
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, u);

    // mensagem: você perdeu
	glColor4f(1.0, 0.0, 0.0, 0.0);
	const unsigned char* x = reinterpret_cast<const unsigned char *>("VOCÊ PERDEU");
    glRasterPos2i( -1.8, texto4 );
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, x);

    // condicao se o pinguim pescar o peixe
    if (pesc==true)
	{
		// desenho do pinguim com peixe na boca
		glPushMatrix();
		glTranslatef(moveping, alturaping, 0.0);
		glRotatef(rotaping, 0.0, 0.0, 1.0);
		glScalef(escalaping, 0.4, 0.0);
		pinguimcompeixe();
		glPopMatrix();
	}
    // condicao do pinguim alimentar o filhote
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
	// condicao do pinguim alimentar o filhote
	if ((moveping <= pfilx + 0.55) && (pesc == true)){
		tempoFilhote += 3500;
	}

    glutSwapBuffers();
}

void keyboard(int key, int x, int y){
  switch (key) {
  // seta esquerda: mover para direcao 0 (esquerda)
  case GLUT_KEY_LEFT:
	direcao = 0;
	break;
  // seta direita: mover para direcao 1 (direita)
  case GLUT_KEY_RIGHT:
	direcao = 1;
	break;
  // seta cima: mover para direcao 3 (cima)
  case GLUT_KEY_UP:
	direcao = 3;
	break;
  // seta beixo: mover para direcao 4 (baixo)
  case GLUT_KEY_DOWN:
	direcao = 4;
	break;
  // padrao: mover para direcao 2 (parado)
  default:
    direcao = 2;
    break;
  }
}
// move = funcao de movimentacao do pinguim
void move(int passo)
{
	// condicao de direcao 1 (direita)
	if(direcao==1)
	{
		// movimentacao de x do pinguim
		moveping += (float)passo/70;
		// desenho do pinguim na direcao do movimento
		escalaping = 0.4;
		// limite direito de movimento
		if(moveping>0.2){
			moveping -= (float)passo/70;
		}
	}
	// condicao de direcao 0 (esquerda)
	if(direcao==0)
	{
		// movimentacao de x do pinguim
		moveping -= (float)passo/70;
		// desenho do pinguim na direcao do movimento
		escalaping = -0.4;
		// limite esquerdo de movimento
		if(moveping<-4.5)
			direcao = 1;
	}
	// condicao de direcao 2 (parado)
	if(direcao==2)
	{
		moveping += 0;
	}
	// ao entrar na agua o pinguim eh rotacionado e muda posicao
	if(moveping>0.0){
		rotaping = 270;

		// nadando para cima
		if(direcao==3){
			alturaping += (float)passo/70;
			escalaping = -0.4;
		}
		// nadando para baixo
		if(direcao==4){
			alturaping -= (float)passo/70;
			escalaping = 0.4;
		}
		// limite superior na agua
		if(alturaping>-3.5)
			alturaping = -3.5;
        // limite inferior na agua
		if(alturaping<-5.5)
			direcao = 3;
	}
	// ao entrar na grama o pinguim eh rotacionado e muda posicao
	if(moveping<0.0){
		rotaping = 0;
		alturaping = -2.4;
    // caso o pinguim estiver na agua e nadando para esquerda, rotaciona para olhar para baixo
	}
	if(direcao==0 && moveping>0.0){
		rotaping = 90;
	}
    // condicao de colisao com o peixe 1, pescaria do peixe e novo peixe
	if ((moveping + 0.95 >= movepeixe1 - 0.5) && (alturaping < alturapeixe1 + 0.5 && alturaping > alturapeixe1 - 0.5) && pesc == false){
		pesc = true;
	    alturapeixe1 = a1;
	}
	// condicao de colisao com o peixe 2, pescaria do peixe e novo peixe
	else if ((moveping + 0.95 >= movepeixe2 - 0.5) && (alturaping < alturapeixe2 + 0.5 && alturaping > alturapeixe2 - 0.5) && pesc == false){
		pesc = true;
		alturapeixe2 = a2;
	}
	// condicao de colisao com o peixe 3, pescaria do peixe e novo peixe
	else if ((moveping + 0.95 >= movepeixe3 - 0.5) && (alturaping < alturapeixe3 + 0.5 && alturaping > alturapeixe3 - 0.5) && pesc == false){
		pesc = true;
		alturapeixe3 = a3;
	}
	// condicao de colisao com o peixe 4, pescaria do peixe e novo peixe
	else if ((moveping + 0.95 >= movepeixe4 - 0.5) && (alturaping < alturapeixe4 + 0.5 && alturaping > alturapeixe4 - 0.5) && pesc == false){
		pesc = true;
		alturapeixe4 = a4;
	}
    // condicao de colisao com o passaro petrel gigante
	if ((moveping >= movepetrel - 0.5) && (moveping <= movepetrel + 0.5) && (alturaping >= alturapetrel -1.3)){
		// em caso de colisao, encerra o tempo e insere o texto
		tempoConta = -10;
		texto4 = 3.0;
	}

glutPostRedisplay();
glutTimerFunc(10,move,1);
}
// move2 = funcao de movimentacao do peixe 1
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
// move3 = funcao de movimentacao do peixe 2
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
// move4 = funcao de movimentacao do peixe 3
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
// move5 = funcao de movimentacao do peixe 4
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
// movepetrelgigante = funcao de movimentacao do passaro petrel gigante
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

	    	// interpolacao polinomial dos pontos aleatorios
	    	GLfloat L0 = (((movepetrel-p4x)*(movepetrel-p3x))/((p2x-p4x)*(p2x-p3x)));
	    	GLfloat L1 = (((movepetrel-p2x)*(movepetrel-p3x))/((p4x-p2x)*(p4x-p3x)));
	    	GLfloat L2 = (((movepetrel-p2x)*(movepetrel-p4x))/((p3x-p2x)*(p3x-p4x)));
	    	alturapetrel = ((p1y*L0) + (p4y*L1) + (p3y*L2));
	    }

	    // limite direito de movimento
	    if(movepetrel>5.5){
	        direcaopetrel=1;
	    }
	 }

//	movimenta para esquerda
	if(direcaopetrel==1)
	{
	    // quando muda a direcao novas coordenadas sao geradas
		if(gerar==0){
		    gera();
			gerar=1;
		}
		movepetrel -= (float)passo/50;
		// movimento parabolico com interpolacao polinomial
	    if(p2x<movepetrel && movepetrel<p3x){

	    	// interpolacao polinomial dos pontos aleatorios
	    	GLfloat L0 = (((movepetrel-p4x)*(movepetrel-p3x))/((p2x-p4x)*(p2x-p3x)));
	    	GLfloat L1 = (((movepetrel-p2x)*(movepetrel-p3x))/((p4x-p2x)*(p4x-p3x)));
	    	GLfloat L2 = (((movepetrel-p2x)*(movepetrel-p4x))/((p3x-p2x)*(p3x-p4x)));
	    	alturapetrel = ((p1y*L0) + (p4y*L1) + (p3y*L2));
	    }
	    // limite esquerdo de movimento
	    if(movepetrel<-5.5){
	        direcaopetrel=0;
	    }
	}

glutPostRedisplay();
glutTimerFunc(10,movepetrelgigante,1);
}

// tempo = funcao de controle do tempo de jogo
void tempo(int passo){

	tempoConta -= 1;
	tempoFilhote -= 1;
    // condicao de termino do tempo de jogo
	if(tempoConta<0){
		// o pinguim e o petrel sao paralisados
		moveping = -3.0;
		movepetrel = 0.0;
		alturapetrel = 1.0;
		// exibe o texto de final de jogo
		texto = 5.0;
	}
	// condicao de termino do tempo de vida do filhote
	else if(tempoFilhote<0){
		// o pinguim e o petrel sao paralisados
		moveping = -3.0;
		movepetrel = 0.0;
		alturapetrel = 1.0;
		// exibe o texto "o filhote morreu" e "você perdeu"
		texto2 = 4.0;
		texto4 = 3.0;
	}

	glutPostRedisplay();
	glutTimerFunc(10,tempo,1);
}


int main(int argc, char** argv) {

  // funcoes necessarias para os numeros aleatorios
  std::random_device rd; 	// obtem um numero aleatorio do hardware
  std::mt19937 gen(rd()); 	// alimenta o gerador de numeros
  // gera = funcao de geracao de numeros aleatorios
  gera();

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

  // movimentacao do pinguim
  glutTimerFunc(10,move,1);
  // movimentacao do peixe 1
  glutTimerFunc(10,move2,1);
  // movimentacao do peixe 2
  glutTimerFunc(10,move3,1);
  // movimentacao do peixe 3
  glutTimerFunc(10,move4,1);
  // movimentacao do peixe 4
  glutTimerFunc(10,move5,1);
  // movimentacao do passaro petrel gigante
  glutTimerFunc(10,movepetrelgigante,1);
  // controle de tempo de jogo
  glutTimerFunc(10,tempo,1);

  // Indica que sempre que uma tecla for pressionada no teclado, GLUT deverá chama a função keyboard() para tratar eventos de teclado (keyboard callback).
  // A função de teclado deve possuir o seguinte protótipo:
  // glutKeyboardFunc(keyboard);

  // Funcao especial do GLUT para teclas de setas
  glutSpecialFunc(keyboard);
  // Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}
