#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float x = 0.0;
float y = 0.0;


void quadrado(float tX, float tY){
  glBegin(GL_POLYGON);
    glVertex2f(-0.25+tX, 0.25+tY);
    glVertex2f(0.25+tX, 0.25+tY);
    glVertex2f(0.25+tX, -0.25+tY);
    glVertex2f(-0.25+tX, -0.25+tY);
  glEnd();
}

void desenha(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    quadrado(-0.5,+0.5);
    glColor3f(1.0,0.0,0.0);
    quadrado(0.5,0.5);
    glColor3f(0.0,1.0,0.0);
    quadrado(0.5,-0.5);
    glColor3f(0.0,0.0,1.0);
    quadrado(-0.5,-0.5);
    glFlush();
}

void init(){
  glClearColor(0, 0, 0, 0);
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    init();
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (400 ,400);
    glutCreateWindow ("Primeiro programa usando OpenGL");
    glutDisplayFunc (desenha);
    glutMainLoop ();
    return 0;
}