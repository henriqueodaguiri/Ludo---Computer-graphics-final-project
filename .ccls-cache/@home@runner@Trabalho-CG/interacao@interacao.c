#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592654

float up = 0.0;
float right = 0.0;
float theta = 0.0;

void imprimeMatriz() {
  float matrix[16];
  int i, j;

  printf("\n\nM = \n");
  glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      printf("%f ", matrix[i + j * 4]);
    }
    printf("\n");
  }
  printf("\n");
}

void circulo() {
  int i;
  float angulo = 0.0;
  glBegin(GL_POLYGON);
  for (i = 0; i <= 10; i++) {
    angulo = 2 * PI * i / 10.0;
    glVertex2f(0.25 * cos(angulo) + 0.25, 0.25 * sin(angulo) + 0.25);
  }
  glEnd();
}

void quadrado() {
  glBegin(GL_POLYGON);
  glVertex2f(-0.25, 0.25);
  glVertex2f(0.25, 0.25);
  glVertex2f(0.25, -0.25);
  glVertex2f(-0.25, -0.25);
  glEnd();
}

void desenha() {
  glClearColor(0, 0, 0, 0); // Preto
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  imprimeMatriz();
  
  glColor3f(1.0, 1.0, 1.0);
  circulo();

  glFlush();
}

void tecladoEspecial(int tecla, int x, int y) {
  switch (tecla) {
  case GLUT_KEY_UP:
    up += 0.05;
    break;
  case GLUT_KEY_DOWN:
    up -= 0.05;
    break;
  case GLUT_KEY_RIGHT:
    right += 0.05;
    break;
  case GLUT_KEY_LEFT:
    right -= 0.05;
    break;

  default:
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Primeiro programa usando OpenGL");
  glutDisplayFunc(desenha);
  glutSpecialFunc(tecladoEspecial);
  glutMainLoop();
  return 0;
}