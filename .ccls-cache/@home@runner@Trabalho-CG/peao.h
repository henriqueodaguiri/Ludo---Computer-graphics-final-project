#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

void cone(float raio, float altura, int segmentos) {
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < segmentos; ++i) {
    float theta1 = 2.0f * M_PI * (float)i / segmentos;
    float theta2 = 2.0f * M_PI * (float)(i + 1) / segmentos;

    glNormal3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glNormal3f(raio * cos(theta1), 0.0f, raio * sin(theta1));
    glVertex3f(raio * cos(theta1), 0.0f, raio * sin(theta1));
    glNormal3f(raio * cos(theta2), 0.0f, raio * sin(theta2));
    glVertex3f(raio * cos(theta2), 0.0f, raio * sin(theta2));

    glVertex3f(raio * cos(theta2), 0.0f, raio * sin(theta2));
    glVertex3f(raio * cos(theta1), 0.0f, raio * sin(theta1));
  
  glVertex3f(0.0f, altura, 0.0f);
  }
  

  glEnd();
}

void esfera(float radius, int slices, int stacks) {
  glutSolidSphere(radius, slices, stacks);
}

void peao(float r, float g, float b) {
  glColor3f(r, g, b);
  glTranslatef(0.0, 0.1, 0.0);
  glScalef(0.25, 0.25, 0.25);
  cone(0.5f, 1.0f, 50);
  glTranslatef(0.0f, 1.0f, 0.0f);
  esfera(0.3f, 30, 30);
}