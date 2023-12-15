#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float tx1 = 0.0;
float ty1 = 0.0;
float tx2 = 0.0;
float ty2 = 0.0;
float tx3 = 0.0;
float ty3 = 0.0; 

float r = 0.0;
float g = 0.0;
float b = 0.0;

void leituraCoordenadas(){
  printf("x1: ");
  scanf("%f",&tx1);
  printf("y1: ");
  scanf("%f",&ty1);
  printf("x2: ");
  scanf("%f",&tx2);
  printf("y2: ");
  scanf("%f",&ty2);
  printf("x3: ");
  scanf("%f",&tx3);
  printf("y3: ");
  scanf("%f",&ty3);
}

void leituraCor(){
  printf("r: ");
  scanf("%f",&r);
  printf("g: ");
  scanf("%f",&g);
  printf("b: ");
  scanf("%f",&b);
}

void desenha(){
    glClearColor(0, 0, 0, 0); //Preto
    while(1){
      glClear(GL_COLOR_BUFFER_BIT);
      leituraCoordenadas();
      leituraCor();
      glColor3f(r,g,b);
      glBegin(GL_POLYGON);
          glVertex2f(tx1, ty1);
          glVertex2f(tx2, ty2);
          glVertex2f(tx3, ty3);
      glEnd();
      glFlush();
    }
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (400 ,400);
    glutCreateWindow ("Primeiro programa usando OpenGL");
    glutDisplayFunc (desenha);
    glutMainLoop ();
    return 0;
}