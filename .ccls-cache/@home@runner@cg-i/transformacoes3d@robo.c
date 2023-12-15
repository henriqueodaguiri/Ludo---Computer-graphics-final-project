#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaXBraco = 0.0;
float thetaYBraco = 0.0;

float thetaYBracoStep = 2.0;
float thetaXBracoStep = 2.0;

float thetaXPerna = 0.0;
float thetaYPerna = 0.0;

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

void cabeca(){
  glPushMatrix();
  glTranslatef(0.0,0.65,0.0);
  glScalef(0.25,0.25,0.25);
  glTranslatef(0.0,0.25,0.0);
  cubo();
  glPopMatrix();
}

void tronco(){
  glPushMatrix();
  glTranslatef(0.0,0.25,0.0);
  glScalef(0.25,0.75,0.25);
  glTranslatef(0.0,0.25,0.0);
  cubo();
  glPopMatrix();
}

void anteBracoDireito(){
  glPushMatrix();

  glTranslatef(0.25,0.55,0.0);
  glRotatef(thetaXBraco+2,0.0,0.0,1.0);
  glTranslatef(-0.25,-0.55,0.0);
  
  glTranslatef(0.25,0.55,0.0);
  glScalef(0.25,0.125,0.125);
  glTranslatef(0.25,0.25,0.0);
  cubo();
  
  glPopMatrix();
}

void bracoDireito(){
  
  glPushMatrix();

  glTranslatef(0.1,0.55,0.0);
  glRotatef(thetaYBraco,0.0,1.0,0.0);
  glRotatef(thetaXBraco,0.0,0.0,1.0);
  glTranslatef(-0.1,-0.55,0.0);
  
  glPushMatrix();
  glTranslatef(0.1,0.55,0.0);
  glScalef(0.25,0.125,0.125);
  glTranslatef(0.25,0.25,0.0);
  cubo();
  glPopMatrix();

  anteBracoDireito();

  glPopMatrix();
}

void bracoEsquerdo(){
  glPushMatrix();
  glScalef(-1.0,1.0,1.0);
  bracoDireito();
  glPopMatrix();
}

void pernaDireita(){

  glPushMatrix();

  glTranslatef(0.01,0.2,0.0);
  glRotatef(thetaXPerna,1.0,0.0,0.0);
  glTranslatef(-0.01,-0.2,0.0);
  
  glPushMatrix();
  glTranslatef(0.01,0.2,0.0);
  glScalef(0.125,0.25,0.125);
  glTranslatef(0.25,-0.25,0.0);
  cubo();
  glPopMatrix();

  glPushMatrix();

  glTranslatef(0.01,0.01,0.0);
  glRotatef(-thetaXPerna,1.0,0.0,0.0);
  glTranslatef(-0.01,0.01,0.0);
  
  glTranslatef(0.01,0.01,0.0);
  glScalef(0.125,0.25,0.125);
  glTranslatef(0.25,-0.25,0.0);
  cubo();
  glPopMatrix();

  glPopMatrix();
}

void pernaEsquerda(){
  glPushMatrix();
  glScalef(-1.0,1.0,1.0);
  pernaDireita();
  glPopMatrix();
}

void desenha() {
  glClearColor(0, 0, 0, 0); // Preto
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPushMatrix();

  glRotatef(alfa,1.0,0.0,0.0);
  glRotatef(beta,0.0,1.0,0.0);
  glTranslatef(0.0,-0.3,0.0);

  cabeca();
  tronco();
  bracoDireito();
  bracoEsquerdo();
  pernaDireita();
  pernaEsquerda();
  
  glPopMatrix();
  
  glFlush();
}

void tecladoEspecial(int tecla, int x, int y) {
  switch (tecla) {
  case GLUT_KEY_RIGHT:
    if(thetaYBraco<90)
      thetaYBraco += 2;
    break;
  case GLUT_KEY_LEFT:
    if(thetaYBraco>0)
      thetaYBraco -= 2;
    break;
  case GLUT_KEY_UP:
    if(thetaXBraco<45)
      thetaXBraco += 2;
    if(thetaXPerna<90)
      thetaXPerna += 2;
    break;
  case GLUT_KEY_DOWN:
    if(thetaXBraco>-45)
      thetaXBraco -= 2;
    if(thetaXPerna>0)
      thetaXPerna -= 2;
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
            alfa+=2;
            break;
        case 's':
            alfa-=2;
        default:
            break;
    }
    glutPostRedisplay();
}

void timerFunc(int value)
{

  if(thetaYBraco <= 0 || thetaYBraco >= 90)
		thetaYBracoStep = -thetaYBracoStep;

  thetaYBraco += thetaYBracoStep;

  if(thetaXBraco <= -45 || thetaXBraco >= 45)
		thetaXBracoStep = -thetaXBracoStep;

  thetaXBraco += thetaXBracoStep;
  
/*    if(thetaXPerna<90)
      thetaXPerna += 2;
    if(thetaXBraco>-45)
      thetaXBraco -= 2;
    if(thetaXPerna>0)
      thetaXPerna -= 2;
 */
	glutPostRedisplay();
	
  glutTimerFunc(50,timerFunc, 1);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,400);
  glutCreateWindow("Cubo");
  glutDisplayFunc(desenha);
  glutKeyboardFunc(teclado);
  //glutSpecialFunc(tecladoEspecial);
  glutTimerFunc(50,timerFunc,1);
  glutMainLoop();
  return 0;
}