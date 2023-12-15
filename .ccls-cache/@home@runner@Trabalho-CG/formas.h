#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

void cube() {
  glBegin(GL_POLYGON);
  glNormal3f(-0.25, 0.25, 0.25);
  glVertex3f(-0.25, 0.25, 0.25);
  glNormal3f(0.25, 0.25, 0.25);
  glVertex3f(0.25, 0.25, 0.25);
  glNormal3f(0.25, -0.25, 0.25);
  glVertex3f(0.25, -0.25, 0.25);
  glNormal3f(-0.25, -0.25, 0.25);
  glVertex3f(-0.25, -0.25, 0.25);

  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-0.25, 0.25, -0.25);
  glVertex3f(-0.25, 0.25, -0.25);
  glNormal3f(0.25, 0.25, -0.25);
  glVertex3f(0.25, 0.25, -0.25);
  glNormal3f(0.25, -0.25, -0.25);
  glVertex3f(0.25, -0.25, -0.25);
  glNormal3f(-0.25, -0.25, -0.25);
  glVertex3f(-0.25, -0.25, -0.25);
  
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0.25, -0.25, 0.25);
  glVertex3f(0.25, -0.25, 0.25);
  glNormal3f(0.25, 0.25, 0.25);
  glVertex3f(0.25, 0.25, 0.25);
  glNormal3f(0.25, 0.25, -0.25);
  glVertex3f(0.25, 0.25, -0.25);
  glNormal3f(0.25, -0.25, -0.25);
  glVertex3f(0.25, -0.25, -0.25);

  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-0.25, -0.25, 0.25);
  glVertex3f(-0.25, -0.25, 0.25);
  glNormal3f(-0.25, 0.25, 0.25);
  glVertex3f(-0.25, 0.25, 0.25);
  glNormal3f(-0.25, 0.25, -0.25);
  glVertex3f(-0.25, 0.25, -0.25);
  glNormal3f(-0.25, -0.25, -0.25);
  glVertex3f(-0.25, -0.25, -0.25);
  
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-0.25, 0.25, 0.25);
  glVertex3f(-0.25, 0.25, 0.25);
  glNormal3f(0.25, 0.25, 0.25);
  glVertex3f(0.25, 0.25, 0.25);
  glNormal3f(0.25, 0.25, -0.25);
  glVertex3f(0.25, 0.25, -0.25);
  glNormal3f(-0.25, 0.25, -0.25);
  glVertex3f(-0.25, 0.25, -0.25);

  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-0.25, -0.25, 0.25);
  glVertex3f(-0.25, -0.25, 0.25);
  glNormal3f(0.25, -0.25, 0.25);
  glVertex3f(0.25, -0.25, 0.25);
  glNormal3f(0.25, -0.25, -0.25);
  glVertex3f(0.25, -0.25, -0.25);
  glNormal3f(-0.25, -0.25, -0.25);
  glVertex3f(-0.25, -0.25, -0.25);

  glEnd();
}

void tile(float r, float g, float b) {
  glColor3f(r, g, b);
  glBegin(GL_POLYGON);
  glNormal3f(-0.244, 0.0626, 0.244);
  glVertex3f(-0.244, 0.0626, 0.244);
  glNormal3f(0.244, 0.0626, 0.244);
  glVertex3f(0.244, 0.0626, 0.244);
  glNormal3f(0.244, 0.0626, -0.244);
  glVertex3f(0.244, 0.0626, -0.244);
  glNormal3f(-0.244, 0.0626, -0.244);
  glVertex3f(-0.244, 0.0626, -0.244);
   
  glEnd();
}

void triangle(float r, float g, float b) {
  glColor3f(r, g, b);
  glBegin(GL_POLYGON);
  glNormal3f(0.245, 0.0626, 0.245);
  glVertex3f(0.245, 0.0626, 0.245);
  glNormal3f(0.245, 0.0626, -0.245);
  glVertex3f(0.245, 0.0626, -0.245);
  glNormal3f(0.0, 0.0626, 0.0);
  glVertex3f(0.0, 0.0626, 0.0);
 
  glEnd();
}

void circle(float radius, int segments) {
  glBegin(GL_TRIANGLE_FAN);
  
  glNormal3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  
  for (int i = 0; i <= segments; ++i) {
    float theta = (2.0 * M_PI * i) / segments;
    float x = radius * cos(theta);
    float y = radius * sin(theta);
    glNormal3f(x, y, 0.0);
    glVertex3f(x, y, 0.0);
  }

  glEnd();
}