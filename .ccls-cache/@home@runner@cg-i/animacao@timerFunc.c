#include <GL/glut.h>

// Posição inicial do quadrado
GLfloat x1 = 100.0f;
GLfloat y1 = 150.0f;
GLsizei rsize = 50;

// Passo nas direções x e y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// Medidas da janela
GLfloat windowWidth = 400;
GLfloat windowHeight = 400;

void init(){
     glClearColor(0.0,0.0,0.0,0.0);
     glEnable(GL_DEPTH_TEST);
     glColor3f(1.0,1.0,1.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluOrtho2D(0.0,windowWidth,0.0,windowHeight);
}

void displayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x1, y1, x1+rsize, y1+rsize);
	glutSwapBuffers();
}

void timerFunc(int value)
{
	if(x1 > windowWidth-rsize || x1 < 0)
		xstep = -xstep;

	if(y1 > windowHeight-rsize || y1 < 0)
		ystep = -ystep;

	x1 += xstep;
	y1 += ystep;

	glutPostRedisplay();
	
  glutTimerFunc(50,timerFunc, 1);
}

int main(int argc, char *argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50,50);
  glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Contra as Paredes");
	glutDisplayFunc(displayFunc);
	glutTimerFunc(50,timerFunc,1);
	init();
	glutMainLoop();
}