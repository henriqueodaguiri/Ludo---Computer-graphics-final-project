#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaX = 0.0;
float thetaY = 0.0;
float alfa = 0.0;
float beta = 0.0;

void cubo() {
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.25,0.25,0.25);
    glVertex3f(0.25,0.25,0.25);
    glVertex3f(0.25,-0.25,0.25);
    glVertex3f(-0.25,-0.25,0.25);
  glEnd();
  glColor3f(0.0,1.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.25,0.25,-0.25);
    glVertex3f(0.25,0.25,-0.25);
    glVertex3f(0.25,-0.25,-0.25);
    glVertex3f(-0.25,-0.25,-0.25);
  glEnd();
  glColor3f(0.0,0.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(0.25,-0.25,0.25);
    glVertex3f(0.25,0.25,0.25);
    glVertex3f(0.25,0.25,-0.25);
    glVertex3f(0.25,-0.25,-0.25);
  glEnd();
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.25,-0.25,0.25);
    glVertex3f(-0.25,0.25,0.25);
    glVertex3f(-0.25,0.25,-0.25);
    glVertex3f(-0.25,-0.25,-0.25);
  glEnd();
  glColor3f(1.0,0.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.25,0.25,0.25);
    glVertex3f(0.25,0.25,0.25);
    glVertex3f(0.25,0.25,-0.25);
    glVertex3f(-0.25,0.25,-0.25);
  glEnd();
  glColor3f(0.0,1.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.25,-0.25,0.25);
    glVertex3f(0.25,-0.25,0.25);
    glVertex3f(0.25,-0.25,-0.25);
    glVertex3f(-0.25,-0.25,-0.25);
  glEnd();
}

void desenha() {
  glClearColor(0, 0, 0, 0); // Preto
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPushMatrix();
  glTranslatef(0.5,0.5,0.0);
  glRotatef(thetaX,1.0,0.0,0.0);
  glRotatef(thetaY,0.0,1.0,0.0);
  cubo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.5,0.5,0.0);
  glRotatef(thetaX,1.0,0.0,0.0);
  glRotatef(thetaY,0.0,1.0,0.0);
  cubo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5,-0.5,0.0);
  glRotatef(thetaX,1.0,0.0,0.0);
  glRotatef(thetaY,0.0,1.0,0.0);
  cubo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.5,-0.5,0.0);
  glRotatef(thetaX,1.0,0.0,0.0);
  glRotatef(thetaY,0.0,1.0,0.0);
  cubo();
  glPopMatrix();
  
  glFlush();
}

void tecladoEspecial(int tecla, int x, int y) {
  switch (tecla) {
  case GLUT_KEY_RIGHT:
    thetaY += 2;
    break;
  case GLUT_KEY_LEFT:
    thetaY -= 2;
    break;
  case GLUT_KEY_UP:
    thetaX += 2;
    break;
  case GLUT_KEY_DOWN:
    thetaX -= 2;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y){
    switch (tecla) {
        case 'a':
            beta+=2;
            break;
        case 'd':
            beta-=2;
            break;
        case 'w':
            alfa+=0.05;
            break;
        case 's':
            alfa-=0.05;
        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,400);
  glutCreateWindow("Cubo");
  glutDisplayFunc(desenha);
  glutKeyboardFunc(teclado);
  glutSpecialFunc(tecladoEspecial);
  glutMainLoop();
  return 0;
}