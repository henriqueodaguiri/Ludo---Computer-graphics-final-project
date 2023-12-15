#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 320

int xc = 160;
int yc = 160;
int radius = 60;

float converteX(int x){
  return -1.0+2*(float)x/WINDOW_WIDTH;
}

float converteY(int y){
  return 1.0-2*(float)y/WINDOW_HEIGHT;
}

void drawCircle(int xc, int yc, int radius) {
  int x = 0;
  int y = radius;
  int d = 3 - 2 * radius;

  while (x <= y) {
    glBegin(GL_POINTS);
    glVertex2f(converteX(xc + x), converteY(yc + y));
    glVertex2f(converteX(xc - x), converteY(yc + y));
    glVertex2f(converteX(xc + x), converteY(yc - y));
    glVertex2f(converteX(xc - x), converteY(yc - y));
    glVertex2f(converteX(xc + y), converteY(yc + x));
    glVertex2f(converteX(xc - y), converteY(yc + x));
    glVertex2f(converteX(xc + y), converteY(yc - x));
    glVertex2f(converteX(xc - y), converteY(yc - x));
    glEnd();

    if (d <= 0) {
      d += 4 * x + 6;
    }
    else {
      d += 4 * (x - y) + 10;
      y--;
    }
    x++;
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0); 
  
  drawCircle(xc, yc, radius);

  glFlush();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Bresenham Circle");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}