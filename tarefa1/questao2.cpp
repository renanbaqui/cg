/*
 * Questao2.cpp
 *
 *  Created on: 14 de mar. de 2021
 *      Author: Renan Baqui
 */
#include <GL/glut.h>


void init(void);
void display(void);


int polygon = 4;
int larJan = 600, altJan = 600; // largura e altura da janela
float xPos, yPos;

void init(void)
{
  // define a cor de background da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho (-1, 1, -1, 1, -1, 1);
}

void display() {

  // Limpa a janela, colocando na tela a cor definida pela função glClearColor
  // glClear(GL_COLOR_BUFFER_BIT);

  glPointSize(50); // tamanho do ponto 50

  if(polygon == 3)
  {
    glBegin(GL_POINTS);
      glColor3f(0, 0, 0);	// cor do ponto preta
      glVertex3f(xPos, yPos, 0.5);	// posicao do mouse
    glEnd();

  }

  if(polygon == 4)
  {
    glClear(GL_COLOR_BUFFER_BIT);	// Limpa a janela, colocando na tela a cor definida pela função glClearColor
  }

  // Libera o buffer de comando de desenho para fazer o desenho acontecer o mais rápido possível.
  glFlush();
}


void mouse(int button, int action, int x, int y)
{
	switch(action)
	case GLUT_DOWN:	// callback due to a mouse press
	{
		xPos = x*(2.0/larJan) -1;
		yPos = 1 - y*(2.0/altJan);
	}

	switch(button)
    {
    case GLUT_LEFT_BUTTON:
    {
    	polygon = 3;
    	break;
    }
    case GLUT_MIDDLE_BUTTON:
    {

      break;
    }
    case GLUT_RIGHT_BUTTON:
    {
    	polygon = 4;
    	break;
    }
    default: break;
  }

  display();
}

int main(int argc, char** argv)
{

 //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
 //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
  glutInit(&argc, argv);

  //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
  // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
  // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

  //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
  glutInitWindowSize (larJan, altJan);
  glutInitWindowPosition (200, 50);

  // Cria uma janela e define seu título
  glutCreateWindow ("Primeiro OpenGL");

  //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
  init();

  // Define display() como a função de desenho (display callback) para a janela corrente.
  // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
  glutDisplayFunc(display);

  // Indica que sempre que uma tecla for pressionada no teclado, GLUT deverá chama a função keyboard() para tratar eventos de teclado (keyboard callback).
  // A função de teclado deve possuir o seguinte protótipo:
  // glutKeyboardFunc(keyboard);

  glutMouseFunc(mouse);

  // Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}
