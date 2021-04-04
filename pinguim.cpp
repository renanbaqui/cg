/*
 * penguim.cpp
 *
 *  Created on: 29 de mar de 2021
 *      Author: Flavia, Renan e Silvio
 */
#include <GL/glut.h>
#include <math.h>
const double PI = 3.1415926535898;

int frameNumber = 0;
GLfloat moveping = 0.0, alturaping = -2.4, rotaping = 0.0, escalaping = 0.4;
GLfloat movepeixe1 = 2.5, alturapeixe1 = -3.8, rotapeixe1 = 0.0, escalapeixe1 = 0.15;
GLfloat movepeixe2 = 5.0, alturapeixe2 = -4.5, rotapeixe2 = 0.0, escalapeixe2 = 0.18;
GLfloat movepeixe3 = 1.0, alturapeixe3 = -5.5, rotapeixe3 = 0.0, escalapeixe3 = 0.18;
GLfloat movepeixe4 = 3.5, alturapeixe4 = -5.1, rotapeixe4 = 0.0, escalapeixe4 = 0.15;
GLint direcao = 2, direcaopeixe1 = 0, direcaopeixe2 = 0, direcaopeixe3 = 0, direcaopeixe4 = 0;

void init();
void display();
void move(int passo);
// alteracao na função keyboard para adequar a glutSpecialFunc
void keyboard(int key, int x, int y);


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
	glTranslatef(moveping, alturaping, 0.0);
	glRotatef(rotaping, 0.0, 0.0, 1.0);
	glScalef(escalaping, 0.4, 0.0);
	pinguim();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0, -2.8, 0.0);
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
	// passaro
	glPushMatrix();
	glTranslatef(0.0, 4.0, 0.0);
	glScalef(1.0, 1.0, 0.0);
	passaro();
	glPopMatrix();

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
		if(moveping>5.0){
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
