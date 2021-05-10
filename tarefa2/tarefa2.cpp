#include <GL/glut.h>
#include <math.h>

void init();
void display();

GLint larJan = 500;
GLint altJan = 500;

float xPos, yPos;

void init() {
  // define a cor de background da janela
  glClearColor(0.854, 0.678, 0.996, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);

}

//rotinas para conversao de coordenadas do mouse
float Xc(float x){
	xPos = x*(2.0/575) -1;
	return xPos;
}

float Yc(float y){
	yPos = 1 - y*(2.0/410);
	return yPos;
}

// desenhos
void grama()
{
  glBegin(GL_POLYGON);
  glVertex3f(Xc(0.0), Yc(410.0), 0.0);
  glVertex3f(Xc(0.0), Yc(358.0), 0.0);
  glVertex3f(Xc(575.0), Yc(358.0), 0.0);
  glVertex3f(Xc(575.0), Yc(410.0), 0.0);
  glEnd();
}

void estrada()
{
  glBegin(GL_POLYGON);
  glVertex3f(Xc(0.0), Yc(358.0), 0.0);
  glVertex3f(Xc(0.0), Yc(297.0), 0.0);
  glVertex3f(Xc(575.0), Yc(297.0), 0.0);
  glVertex3f(Xc(575.0), Yc(358.0), 0.0);
  glEnd();
}

void linha()
{
  glBegin(GL_POLYGON);
  glVertex3f(Xc(0.0), Yc(332.0), 0.0);
  glVertex3f(Xc(0.0), Yc(327.0), 0.0);
  glVertex3f(Xc(575.0), Yc(327.0), 0.0);
  glVertex3f(Xc(575.0), Yc(332.0), 0.0);
  glEnd();
}

void montanhas()
{
  glBegin(GL_POLYGON);
  glVertex3f(Xc(0.0), Yc(297.0), 0.0);
  glVertex3f(Xc(0.0), Yc(262.0), 0.0);
  glVertex3f(Xc(122.0), Yc(193.0), 0.0);
  glVertex3f(Xc(147.0), Yc(223.0), 0.0);
  glVertex3f(Xc(247.0), Yc(157.0), 0.0);
  glVertex3f(Xc(386.0), Yc(272.0), 0.0);
  glVertex3f(Xc(500.0), Yc(220.0), 0.0);
  glVertex3f(Xc(575.0), Yc(264.0), 0.0);
  glVertex3f(Xc(575.0), Yc(297.0), 0.0);
  glVertex3f(Xc(0.0), Yc(297.0), 0.0);
  glEnd();
}

void retangulo()
{
  //centro da figura: 287.5 e 205.0
  //altura do retangulo: 34
  //comprimento do retangulo: 148
  glBegin(GL_POLYGON);
  glVertex3f(Xc(213.5), Yc(188.0), 0.0);
  glVertex3f(Xc(213.5), Yc(222.0), 0.0);
  glVertex3f(Xc(361.5), Yc(222.0), 0.0);
  glVertex3f(Xc(361.5), Yc(188.0), 0.0);
  glEnd();
}

void base()
{
  //centro da figura: 287.5 e 205.0
  //altura do retangulo: 170
  //comprimento do retangulo: 6
  glBegin(GL_POLYGON);
  glVertex3f(Xc(284.5), Yc(120.0), 0.0);
  glVertex3f(Xc(284.5), Yc(290.0), 0.0);
  glVertex3f(Xc(290.5), Yc(290.0), 0.0);
  glVertex3f(Xc(290.5), Yc(120.0), 0.0);
  glEnd();
}

void catavento()
{
  glBegin(GL_POLYGON);
  glVertex3f(Xc(287.5), Yc(205.0), 0.0);
  glVertex3f(Xc(301.5), Yc(179.0), 0.0);
  glVertex3f(Xc(311.5), Yc(125.0), 0.0);
  glVertex3f(Xc(287.5), Yc(175.0), 0.0);
  glEnd();
}

void circulo()
{
  glBegin(GL_POINTS);
    for(int i=0;i<1000;++i)
    {
      glVertex3f(cos(2*3.14159*i/1000.0),sin(2*3.14159*i/1000.0),0);
    }
  glEnd();
}

void linhas()
{
  //linha tamanho 128
  glBegin(GL_LINES);
  glVertex3f(Xc(287.5), Yc(269.0), 0.0);
  glVertex3f(Xc(287.5), Yc(141.0), 0.0);
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3f(0.0, 0.725, 0.0);
  grama();

  glColor3f(0.0, 0.725, 0.0);
  montanhas();

  glColor3f(0.564, 0.231, 0.596);
  estrada();

  // linha da estrada
  glColor3f(1.0, 1.0, 1.0);
  linha();

  //rodas - circulos
  for (float x=0.070; x>0.055; x-= 0.001)	// loop for de criacao de diversos circulos com raios diferentes
  {
    glPushMatrix();
 	glTranslatef(Xc(208.0), Yc(331.0), 0.0);
 	glScalef(x,x,0);
 	glColor3f(0.0, 0.0, 0.0);
 	circulo();
 	glPopMatrix();
  }
  for (float x=0.070; x>0.055; x-= 0.001)
  {
    glPushMatrix();
 	glTranslatef(Xc(289.0), Yc(331.0), 0.0);
 	glScalef(x,x,0);
 	glColor3f(0.0, 0.0, 0.0);
 	circulo();
 	glPopMatrix();
  }
  for (float x=0.055; x>0.015; x-= 0.001)
  {
    glPushMatrix();
 	glTranslatef(Xc(208.0), Yc(331.0), 0.0);
 	glScalef(x, x,0);
 	glColor3f(0.792, 0.757, 0.761);
 	circulo();
 	glPopMatrix();
  }
  for (float x=0.055; x>0.015; x-= 0.001)
  {
    glPushMatrix();
 	glTranslatef(Xc(289.0), Yc(331.0), 0.0);
 	glScalef(x, x,0);
 	glColor3f(0.792, 0.757, 0.761);
 	circulo();
 	glPopMatrix();
  }
  for (float x=0.015; x>0.000; x-= 0.001)
  {
    glPushMatrix();
 	glTranslatef(Xc(208.0), Yc(331.0), 0.0);
 	glScalef(x, x,0);
 	glColor3f(0.0, 0.0, 0.0);
 	circulo();
 	glPopMatrix();
  }
  for (float x=0.015; x>0.000; x-= 0.001)
  {
    glPushMatrix();
 	glTranslatef(Xc(289.0), Yc(331.0), 0.0);
 	glScalef(x, x,0);
 	glColor3f(0.0, 0.0, 0.0);
 	circulo();
 	glPopMatrix();
  }

  //rodas - linhas
  for (float alpha = 15.0; alpha<181.0; alpha+= 30.0)	// loop for de criacao de diversas linhas com angulos diferentes
  {
    glPushMatrix();
    glTranslatef(Xc(208.0), Yc(331.0), 0.0);
    glRotatef(alpha, 0.0, 0.0, 1.0);
    glScalef(0.2,0.2,0);
    glColor3f(0.0, 0.0, 0.0);
    linhas();
    glPopMatrix();
  }
  for (float alpha = 15.0; alpha<181.0; alpha+= 30.0)
  {
    glPushMatrix();
    glTranslatef(Xc(289.0), Yc(331.0), 0.0);
    glRotatef(alpha, 0.0, 0.0, 1.0);
    glScalef(0.2,0.2,0);
    glColor3f(0.0, 0.0, 0.0);
    linhas();
    glPopMatrix();
  }

  //carro - base
  glPushMatrix();
  glTranslatef(Xc(248.0), Yc(307.0), 0.0);
  glScalef(1.0,1.0,0);
  glColor3f(1.0, 0.0, 0.0);
  retangulo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(Xc(228.0), Yc(283.0), 0.0);
  glScalef(0.5,0.5,0);
  glColor3f(1.0, 0.0, 0.0);
  retangulo();
  glPopMatrix();

  //sol - circulo
  for (float x=0.170; x>0.000; x-= 0.001)
  {
    glPushMatrix();
	glTranslatef(Xc(451.0), Yc(57.0), 0.0);
	glScalef(x, x,0);
	glColor3f(0.882, 1.0, 0.0);
	circulo();
	glPopMatrix();
  }

  //sol - linhas
  for (float alpha = 15.0; alpha<181.0; alpha+= 30.0)
  {
    glPushMatrix();
    glTranslatef(Xc(451.0), Yc(57.0), 0.0);
    glRotatef(alpha, 0.0, 0.0, 1.0);
    glScalef(0.8,0.8,0);
    glColor3f(0.882, 1.0, 0.0);
    linhas();
    glPopMatrix();
  }

  //cataventos - bases
  glPushMatrix();
  glTranslatef(Xc(304.0), Yc(173.0), 0.0);
  glScalef(1.0,1.0,0);
  glColor3f(0.663, 0.576, 0.639);
  base();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(Xc(180.0), Yc(169.0), 0.0);
  glScalef(0.5,0.5,0);
  glColor3f(0.663, 0.576, 0.639);
  base();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(Xc(61.0), Yc(171.0), 0.0);
  glScalef(0.8,0.8,0);
  glColor3f(0.663, 0.576, 0.639);
  base();
  glPopMatrix();

  //cataventos - cataventos
  //catavento 1
  glPushMatrix();
  glTranslatef(Xc(304.0), Yc(91.0), 0.0);
  //glRotatef(alpha, 0.0, 0.0, 1.0);
  glScalef(1.0,1.0,0);
  glColor3f(1.0, 0.0, 0.0);
  catavento();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(Xc(304.0), Yc(91.0), 0.0);
  glRotatef(120.0, 0.0, 0.0, 1.0);
  glScalef(1.0,1.0,0);
  glColor3f(1.0, 0.0, 0.0);
  catavento();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(Xc(304.0), Yc(91.0), 0.0);
  glRotatef(240.0, 0.0, 0.0, 1.0);
  glScalef(1.0,1.0,0);
  glColor3f(1.0, 0.0, 0.0);
  catavento();
  glPopMatrix();

  //catavento 2
  glPushMatrix();
  glTranslatef(Xc(179.0), Yc(127.0), 0.0);
  //glRotatef(alpha, 0.0, 0.0, 1.0);
  glScalef(0.45,0.45,0);
  glColor3f(1.0, 0.0, 0.0);
  catavento();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(Xc(179.0), Yc(127.0), 0.0);
  glRotatef(120.0, 0.0, 0.0, 1.0);
  glScalef(0.45,0.45,0);
  glColor3f(1.0, 0.0, 0.0);
  catavento();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(Xc(179.0), Yc(127.0), 0.0);
  glRotatef(240.0, 0.0, 0.0, 1.0);
  glScalef(0.45,0.45,0);
  glColor3f(1.0, 0.0, 0.0);
  catavento();
  glPopMatrix();

  //catavento 3
  glPushMatrix();
  glTranslatef(Xc(61.0), Yc(100.0), 0.0);
  //glRotatef(alpha, 0.0, 0.0, 1.0);
  glScalef(0.8,0.8,0);
  glColor3f(1.0, 0.0, 0.0);
  catavento();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(Xc(61.0), Yc(100.0), 0.0);
  glRotatef(120.0, 0.0, 0.0, 1.0);
  glScalef(0.8,0.8,0);
  glColor3f(1.0, 0.0, 0.0);
  catavento();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(Xc(61.0), Yc(100.0), 0.0);
  glRotatef(240.0, 0.0, 0.0, 1.0);
  glScalef(0.8,0.8,0);
  glColor3f(1.0, 0.0, 0.0);
  catavento();
  glPopMatrix();

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
  glutInitWindowSize(larJan, altJan);
  glutInitWindowPosition(200, 50);

  // Cria uma janela e define seu título
  glutCreateWindow("Tarefa 2");

  //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
  init();

  // Define display() como a função de desenho (display callback) para a janela corrente.
  // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
  glutDisplayFunc(display);

  //Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}
