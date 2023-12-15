#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

  glPushMatrix();
  
  glColor3f(1.0, 0.0, 0.0);
  glTranslatef(0.5,0.5,0.0);
  glRotatef(theta,0.0,0.0,1.0);
  quadrado();
  
  glPopMatrix();
  glPushMatrix();
  
  glColor3f(0.0,0.0,1.0);
  glRotatef(theta,0.0,0.0,1.0);
  glTranslatef(0.5,-0.5,0.0);
  quadrado();

  glPopMatrix();
  glPushMatrix();

  glColor3f(0.0,1.0,0.0);
  glTranslatef(right,0.0,0.0);
  glTranslatef(-0.5,0.5,0.0);
  glPushMatrix();
  glRotatef(theta,0.0,0.0,1.0);
  quadrado();
  glPopMatrix();
  glColor3f(1.0,1.0,1.0);
  glScalef(0.5,0.5,1.0);
  quadrado();

  glPopMatrix();

  
  
  glFlush();
}

void tecladoEspecial(int tecla, int x, int y) {
  switch (tecla) {
  case GLUT_KEY_RIGHT:
    theta += 2;
    right += 0.01;
    break;
  case GLUT_KEY_LEFT:
    theta -= 2;
    right -= 0.01;
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