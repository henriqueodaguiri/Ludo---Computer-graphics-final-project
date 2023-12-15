#include <GL/glut.h>
#include "formas.h"

/* Returns the sign of x */
double sgnf ( double x ) {
   if ( x < 0 )
       return -1.0;
   if ( x > 0 )
       return 1.0;
   return 0;
}

void face(){
  int n = 20;
  double rx = 0.25;
  double ry = 0.25;
  double rz = 0.25;
  double s1 = 0.5;
  double s2 = 0.5;
  double phi = 0.0;
  double theta = 0.0;
  for(int i=0;i<n;i++){
    glBegin(GL_POLYGON);
        for(int j=0;j<n;j++){
          glNormal3f(rx*sgnf(cos(phi))*pow(fabs(cos(phi)),s1)*(sgnf(cos(theta))*pow(fabs(cos(theta)),s2)),ry*sgnf(cos(phi))*pow(fabs(cos(phi)),s1)*(sgnf(sin(theta))*pow(fabs(sin(theta)),s2)),rz*sgnf(sin(phi))*pow(fabs(sin(phi)),s1));
          glVertex3f(rx*sgnf(cos(phi))*pow(fabs(cos(phi)),s1)*(sgnf(cos(theta))*pow(fabs(cos(theta)),s2)),ry*sgnf(cos(phi))*pow(fabs(cos(phi)),s1)*(sgnf(sin(theta))*pow(fabs(sin(theta)),s2)),rz*sgnf(sin(phi))*pow(fabs(sin(phi)),s1));
            
            phi = phi + (2*M_PI)/n;
        }
    glEnd();
    phi = 0.0;

  }

  glEnd();
}

void sideface6(){
  glColor3f(1,1,1);
  glPushMatrix();  //Lower face
    glTranslatef(0.0,-0.251,0.0);
    face();
  glPopMatrix();

  //circles
  glColor3f(0.0,0.0,0.0);
  glPushMatrix();  //Lower face circle
    glTranslatef(0.15,-0.252,0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Lower face circle
    glTranslatef(0.0,-0.252,0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Lower face circle
    glTranslatef(-0.15,-0.252,0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Lower face circle
    glTranslatef(0.15,-0.252,-0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Lower face circle
    glTranslatef(0.0,-0.252,-0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Lower face circle
    glTranslatef(-0.15,-0.252,-0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();
}

void sideface5(){
  glColor3f(1,1,1);
  glPushMatrix();  //Upper face
    glTranslatef(0.0,0.251,0.0);
    face();
  glPopMatrix();

  // circles
  glColor3f(0.0,0.0,0.0);
  glPushMatrix();  //Upper face circle
    glTranslatef(0.,0.252,0.0);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();
  
  glPushMatrix();  //Upper face circle
    glTranslatef(0.1,0.252,0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();
  
  glPushMatrix();  //Upper face circle
    glTranslatef(-0.1,0.252,0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();
  
  glPushMatrix();  //Upper face circle
    glTranslatef(-0.1,0.252,-0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Upper face circle
    glTranslatef(0.1,0.252,-0.1);
    glRotatef(90,1,0,0);
    circle(0.05, 20);
  glPopMatrix();
}

void sideface4(){
  glColor3f(1,1,1);
  glPushMatrix();  // side faces
    glTranslatef(0.0,0.0,0.251);
    glRotatef(90,1,0,0);
    face();
  glPopMatrix();

  //circles
  glColor3f(0.0,0.0,0.0);
  glPushMatrix();  //Upper face circle
    glTranslatef(-0.1,-0.1,0.252);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Upper face circle
    glTranslatef(0.1,-0.1,0.252);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Upper face circle
    glTranslatef(-0.1,0.1,0.252);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Upper face circle
    glTranslatef(0.1,0.1,0.252);
    circle(0.05, 20);
  glPopMatrix();
}

void sideface3(){
  glColor3f(1,1,1);
  glPushMatrix();  
    glTranslatef(0.0,0.0,-0.251);
    glRotatef(90,1,0,0);
    face();
  glPopMatrix();

  // circles
  glColor3f(0.0,0.0,0.0);

  glPushMatrix();  //Upper face circle
    glTranslatef(0.15,0.15,-0.252);
    glRotatef(90,0,0,1);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Upper face circle
    glTranslatef(0.0,-0.0,-0.252);
    glRotatef(90,0,0,1);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Upper face circle
    glTranslatef(-0.15,-0.15,-0.252);
    glRotatef(90,0,0,1);
    circle(0.05, 20);
  glPopMatrix();
}

void sideface2(){
  glColor3f(1,1,1);
  glPushMatrix();  
    glTranslatef(0.251,0.0,0.0);
    glRotatef(90,0,0,1);
    face();
  glPopMatrix();

  // circles
  glColor3f(0.0,0.0,0.0);

  glPushMatrix();  //Upper face circle
    glTranslatef(0.252,-0.1,-0.1);
    glRotatef(90,0,1,0);
    circle(0.05, 20);
  glPopMatrix();

  glPushMatrix();  //Upper face circle
    glTranslatef(0.252,0.1,0.1);
    glRotatef(90,0,1,0);
    circle(0.05, 20);
  glPopMatrix();
  
}

void sideface1(){
  glColor3f(1,1,1);
  glPushMatrix();  
    glTranslatef(-0.251,0.0,0.0);
    glRotatef(90,0,0,1);
    face();
  glPopMatrix();

  //circles
  glColor3f(0.0,0.0,0.0);

  glPushMatrix();  //Upper face circle
    glTranslatef(-0.252,0.0,0.0);
    glRotatef(90,0,1,0);
    circle(0.05, 20);
  glPopMatrix();
}


void dice(int drawn_number){
  glColor3f(184.0/255,134.0/255,11.0/255);
  glPushMatrix();
  glPushMatrix();
    glTranslatef(0.0,7.0,0.0);
    switch(drawn_number){
      case 1:
        glRotatef(-90,0,0,1);
      break;
      case 2:
        glRotatef(90,0,0,1);
      break;
      case 3:
        glRotatef(90,1,0,0);
      break;
      case 4:
        glRotatef(-90,1,0,0);
      break;
      case 5:
        //nao eh preciso rotacionar
      break;
      case 6:
        glRotatef(180,1,0,0);
      break;
      default:
        break;
    }
    cube();
    sideface1();
    sideface2();
    sideface3();
    sideface4();
    sideface5();
    sideface6();
  glPopMatrix();
}

int draw_number(){
  int drawn_number = (rand() % 6) + 1;
  return drawn_number;
}