/*

COMO JOGAR:

REGRAS GERAIS
- O primeiro jogador é sorteado, a partir disso segue o sentido anti-horário;
- No turno de cada jogador é possivel jogar o dado apertado MOUSE_LEFT;
- Após isso o jogador pressiona um número de 1 - 4 para escolher a peao;
- apertando novamente o botao MOUSE_LEFT move o peao selecionado com o valor;
sorteado pelo dado. Caso nenhum peao seja selecionado pro padrao o jogo escolhe
o de valor mais baixo em jogo;
- O jogador que completar 4 voltas completas, uma com cada peao, primeiro sera o
vencedor da partida;

CASOS ESPECIAS
- Tirando o valor 6 no seu turno é possivel após mover um peao jogar novamente
ou iniciar o jogo com algum peao na reserva apertando a tecla 'a' antes de jogar
o dado novamente;
- Casas são compartilhadas para peoes da mesma cor, em caso de cores diferentes
o ultimo a chegar se mantem na casa enquanto o outro volta para reserva;

*/

#include "dice.h"
#include "peao.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

/* GLOBAL */

#define RED 0
#define GREEN 1
#define YELLOW 2
#define BLUE 3

float thetaX = 0.0;
float thetaY = 0.0;
int turn; // variavel que define a vez do jogador
int diceResult = 1;
int ani_seq = 0; // variavel para indicar a próxima animação

float difX[3] = {0, 0, 0};
float difY[3] = {0, 0, 0};
float difZ[3] = {0, 0, 0};

float targetX[3] = {0, 0, 0};
float targetY[3] = {0, 0, 0};
float targetZ[3] = {0, 0, 0};
int animation[3] = {0, 0, 0}; // buffer de animação

float xCam = 0.01;
float yCam = 8.0;
float zCam = 0.0;

#define MAX_PLAYERS 4
#define MAX_PAWNS 4
#define CELL_SIZE 0.5
#define MAX_DICE_ROLLS 3

typedef struct Pawn {
  float x, z;
  int tileNum;
  int mapSide;
  int state;
} Pawn;

typedef struct Player {
  int r, g, b;
  Pawn pawns[MAX_PAWNS];
} Player;

Player playerTeam[MAX_PLAYERS] = {
    // red, green, yellow, blue;
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 0},
    {0, 0, 1},
};

float initialCords[4][2] = {
    {1.75, 2.75},
    {1.75, 1.75},
    {2.75, 2.75},
    {2.75, 1.75},
};
float inGameInitialCord[2] = {3.0, 0.5};
float sideInitialCord[2] = {1.0, -0.5};

int mapSideRotation = 90;
void turnView();
/* MOVIMENTACAO */

Player getPlayerByID(int id) { return playerTeam[id]; }

Pawn getPawnByID(Player player, int id) { return player.pawns[id]; }

void lightning() {
  GLfloat light0_pos[] = {0.0f, 2.0f, 0.0f, 1.0f};
  GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat black[] = {0.5f, 0.5f, 0.5f, 1.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, black);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);

  GLfloat light1_pos[] = {0, 2, 0, 1.0f};
  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white);
  GLfloat direction[] = {0.0f, -3.0f, 0.0f};
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction); // vetor direção
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 360.0f);        // espalhamento angular
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5f);        // atenuação angular

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
}

void initPawns() {
  for (int i = 0; i < MAX_PLAYERS; i++) {
    Player p = getPlayerByID(i);
    for (int j = 0; j < MAX_PAWNS; j++) {
      playerTeam[i].pawns[j].x = initialCords[j][0];
      playerTeam[i].pawns[j].z = initialCords[j][1];
      playerTeam[i].pawns[j].tileNum = 0;
      playerTeam[i].pawns[j].mapSide = 0;
      playerTeam[i].pawns[j].state = 0;
    }
  }
}

void startPawnInGame(int team, int id) {
  Pawn *pawn = &playerTeam[team].pawns[id];
  pawn->x = inGameInitialCord[0];
  pawn->z = inGameInitialCord[1];
  pawn->tileNum = 9;
  pawn->state = 1;
}

void drawPawns(Player p) {
  for (int j = 0; j < MAX_PAWNS; j++) {
    Pawn pawn = getPawnByID(p, j);
    glPushMatrix();
    glRotatef(pawn.mapSide * -mapSideRotation, 0, 1, 0);
    glTranslatef(pawn.x, 0, pawn.z);
    peao(p.r - 0.3, p.g - 0.3, p.b - 0.3);
    glPopMatrix();
  }
}

void defaultMove(Pawn *pawn) {
  if (pawn->tileNum == 13) {
    pawn->mapSide += 1;
    pawn->mapSide = pawn->mapSide % 4;
    pawn->tileNum = 0;
    pawn->x = sideInitialCord[0];
    pawn->z = sideInitialCord[1];
  } else if (pawn->tileNum < 6) {
    pawn->x += CELL_SIZE;
  } else if (pawn->tileNum == 6 || pawn->tileNum == 7) {
    pawn->z += CELL_SIZE;
  } else if (pawn->tileNum > 7) {
    pawn->x -= CELL_SIZE;
  }
  pawn->tileNum++;
}

void finalMove(Pawn *p) {
  if (p->tileNum == 0)
    p->z -= CELL_SIZE;
  else {
    p->x -= CELL_SIZE;
  }
  p->tileNum++;
  if (p->tileNum == 6)
    p->state = 4;
}

void handlePawnState(Pawn *p) {
  if (p->state == 1) {
    p->state = 2;
  } else if (p->state == 2 && p->mapSide == 0 && p->tileNum == 9) {
    p->state = 3;
    p->tileNum = 0;
  }
}

void movePawn(int team, int id) {

  Pawn *pawn = &playerTeam[team].pawns[id];
  handlePawnState(pawn);

  if (pawn->state == 2) {
    defaultMove(pawn);
  } else if (pawn->state == 3) {
    finalMove(pawn);
  }

  // printf("\n pawn state %d", pawn->state);
  // printf("\n new pos x:%f z:%f", pawn->x, pawn->z);
  // printf("\n new tileNum %d", pawn->tileNum);
  // printf("\n new side %d \n", pawn->mapSide);
}

int gameState = 0;
int turnState = 0;
int selectedPawn = 0;
int action = 0;
int sixResults = 0;

/* ANIMATION */

void dice_animation() {
  turnView();
  difY[0] = (14.5 - 4.5) / 50.0;
  difY[1] = (4.5 - 14.5) / 75.0;
  difX[0] = (targetX[2] - xCam) / 100.0;
  difX[1] = (targetX[2] - xCam) / 100.0;
  difZ[0] = (targetZ[2] - zCam) / 100.0;
  difZ[1] = (targetZ[2] - zCam) / 100.0;
  targetX[0] = targetX[2];
  targetX[1] = targetX[2];
  targetZ[0] = targetZ[2];
  targetZ[1] = targetZ[2];
  targetY[0] = 14.5;
  targetY[1] = 4.5;
  animation[0] = 1;
  animation[1] = 1;
}

/* TURNOS */

void printTurno() {
  char *team = "X";
  switch (turn) {
  case 0:
    team = "RED";
    break;
  case 1:
    team = "GREEN";
    break;
  case 2:
    team = "YELLOW";
    break;
  case 3:
    team = "BLUE";
    break;
  }
  printf("\nnovo turno - vez do %s\n--Botão esquerdo para jogar o dado--\n",
         team);
}

// checagem de vitoria
int checkWin(Player p) {
  int count = 0;
  for (int i = 0; i < MAX_PAWNS; i++) {
    if (p.pawns[i].state == 3) {
      count++;
    }
  }
  if (count == MAX_PAWNS) {
    gameState = 1;
    switch (turn) {
    case RED:
      printf("RED WIN\n");
      break;
    case GREEN:
      printf("GREEN WIN\n");
      break;
    case YELLOW:
      printf("YELLOW WIN\n");
      break;
    case BLUE:
      printf("BLUE WIN\n");
      break;
    default:
      break;
    }
    return 1;
  }
  return 0;
}
void startNextTurn() {
  if (checkWin(getPlayerByID(turn)) != 1) {
    turnState = 0;
    selectedPawn = 0;
    if (diceResult == 6 && sixResults < 3) {
      printf("Jogador tirou 6 - joga novamente!!!\n");
    } else {
      action = 0;
      sixResults = 0;
      turn = (turn + 1) % MAX_PAWNS;
      turnView();
      printTurno();
    }
    diceResult = 0;
  }
}

void trySelectPawn(int team, int id) {
  Player p = playerTeam[team];
  Pawn *pawn = &p.pawns[id];
  if (p.pawns[id].state != 0 && p.pawns[id].state != 4) {
    selectedPawn = id;
  } else {
    for (int i = 0; i < MAX_PAWNS; i++) {
      if (p.pawns[i].state != 0 && p.pawns[i].state != 4) {
        selectedPawn = i;
        printf("selected pawn %d by default\n", selectedPawn);
        return;
      }
    }
    printf("no pawns in the board\n");
  }
}

void rollDice() {
  diceResult = draw_number();
  dice_animation();
  int pawnToMove = 0;
  turnState = 1;
  printf("Resultado do dado: %d\n", diceResult);
  if (diceResult == 6) {
    sixResults++;
    printf("Jogador tirou 6 %d vezes\n", sixResults);
    action = 1;
    printf("--Botão esquerdo para jogar novamente ou 'a' para começar com um "
           "novo peao--\n");
  } else {
    printf("--Selecione um peao valido no tabuleiro--\n");
    sixResults = 0;
    action = 0;
  }
}

void returnPawn(int team, int id) {
  printf("returning %d from %d\n", id, team);
  Pawn *pawn = &playerTeam[team].pawns[id];
  pawn->x = initialCords[id][0];
  pawn->z = initialCords[id][1];
  pawn->tileNum = 0;
  pawn->state = 0;
  pawn->mapSide = 0;
}

int getRealSide(int x, int z) {
  int val = z - x;
  val = (val + 4) % 4;
  return val;
}

void checkSharedTiles(int team, int id) {

  Pawn pawn = playerTeam[team].pawns[id];
  int tileNum = pawn.tileNum;
  int side = getRealSide(team, pawn.mapSide);
  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (i != team) {
      for (int j = 0; j < MAX_PAWNS; j++) {
        if (playerTeam[i].pawns[j].state != 0) {
          int side2 = getRealSide(i, playerTeam[i].pawns[j].mapSide);
          if (playerTeam[i].pawns[j].tileNum == tileNum && side == side2) {
            switch (i) {
            case RED:
              printf("peao %d do time RED voltou para o inicio\n", j);
              break;
            case GREEN:
              printf("peao %d do time GREEN voltou para o inicio\n", j);
              break;
            case YELLOW:
              printf("peao %d do time YELLOW voltou para o inicio\n", j);
              break;
            case BLUE:
              printf("peao %d do timE BLUE voltou para o inicio\n", j);
              break;
            default:
              break;
            }

            returnPawn(i, j);
          }
        }
      }
    }
  }
}

void moveSelectedPawn() {
  // printf("moving pawn %d - from team %d - value: %d\n", selectedPawn,
  // turn, diceResult);
  for (int i = 0; i < diceResult; i++) {
    movePawn(turn, selectedPawn);
  }
  checkSharedTiles(turn, selectedPawn);
}

void handleTurn() {
  // check player turn
  // roll dice
  // select pawn
  switch (turnState) {
  case 0:
    rollDice();
    break;
  case 1:
    turnState = 2;
    break;
  case 2:
    turnState = 3;
    break;
  case 3:
    moveSelectedPawn();
    startNextTurn();
  }
}

void tryDrawNewPawn() {
  if (action == 1 && sixResults < 3) {
    printf("PLAYER DRAWS A NEW PAWN\n");
    Player p = playerTeam[turn];
    for (int i = 0; i < MAX_PAWNS; i++) {
      if (p.pawns[i].state == 0) {
        startPawnInGame(turn, i);
        action = 0;
        printf("started pawn %d \n", i);
        startNextTurn();
        return;
      }
    }
    action = 0;
  }
}

void gameInit() {
  initPawns();
  for (int i = 0; i < MAX_PLAYERS; i++) {
    startPawnInGame(i, 0);
  }

  srand(time(NULL));
  turn = rand() % 4;
  printTurno();
}

void init() {
  glClearColor(0.709f, 0.921f, 0.96f, 1.0f); // define a cor de fundo
  glEnable(GL_DEPTH_TEST);                   // habilita o teste de profundidade

  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);

  glEnable(GL_COLOR_MATERIAL);

  glMatrixMode(GL_MODELVIEW); // define que a matrix é a model view
  glLoadIdentity();           // carrega a matrix de identidade
  // camera comeca apontada para o centro do tabuleiro em uma visao de cima
  gluLookAt(xCam, yCam, zCam, // posição da câmera
            0.0, -3.0, 0.0,   // para onde a câmera aponta
            0.0, 1.0, 0.0);   // vetor view-up

  glMatrixMode(GL_PROJECTION); // define que a matrix é a de projeção
  glLoadIdentity();            // carrega a matrix de identidade
  gluPerspective(60.0, 1.0, 2.0, 20.0);
  lightning();
}

void pawnInitialPosition() {
  glPushMatrix();
  glScalef(0.60, 0.60, 0.60);
  glRotatef(90, 1, 0, 0);
  circle(0.5, 30);
  glPopMatrix();
}

void camPosition(int value) {
  while (animation[ani_seq - 1] != 0 && ani_seq > 0) {
    ani_seq--;
  }
  xCam += difX[ani_seq];
  yCam += difY[ani_seq];
  zCam += difZ[ani_seq];
  if (difX[ani_seq] > 0) {
    if (xCam >= targetX[ani_seq])
      xCam = targetX[ani_seq];
  } else {
    if (xCam <= targetX[ani_seq])
      xCam = targetX[ani_seq];
  }
  if (difY[ani_seq] > 0) {
    if (yCam >= targetY[ani_seq])
      yCam = targetY[ani_seq];
  } else {
    if (yCam <= targetY[ani_seq])
      yCam = targetY[ani_seq];
  }
  if (difZ[ani_seq] > 0) {
    if (zCam >= targetZ[ani_seq])
      zCam = targetZ[ani_seq];
  } else {
    if (zCam <= targetZ[ani_seq])
      zCam = targetZ[ani_seq];
  }
  if (xCam == targetX[ani_seq] && yCam == targetY[ani_seq] &&
      zCam == targetZ[ani_seq] && ani_seq < 2) {
    animation[ani_seq] = 0;
    ani_seq++;
  }
  glLoadIdentity();
  gluLookAt(xCam, yCam, zCam, // posição da câmera
            0.0, -3.0, 0.0,   // para onde a câmera aponta
            0.0, 1.0, 0.0);   // vetor view-up
  lightning();
  glutPostRedisplay();
  glutTimerFunc(10, camPosition, 1);
}

/* CAMERA */

/*void camPosition(int value) {
  glutPostRedisplay();
  glutTimerFunc(10, camPosition, 1);
}*/

void turnView() {
  switch (turn) {
  case YELLOW:
    difX[2] = (-6.0 - xCam) / 100.0;
    difY[2] = (4.5 - yCam) / 100.0;
    difZ[2] = (-6.0 - zCam) / 100.0;
    targetX[2] = -6.0;
    targetY[2] = 4.5;
    targetZ[2] = -6.0;

    break;
  case RED:
    difX[2] = (6.0 - xCam) / 100.0;
    difY[2] = (4.5 - yCam) / 100.0;
    difZ[2] = (6.0 - zCam) / 100.0;
    targetX[2] = 6.0;
    targetY[2] = 4.5;
    targetZ[2] = 6.0;
    break;

  case GREEN:
    difX[2] = (6.0 - xCam) / 100.0;
    difY[2] = (4.5 - yCam) / 100.0;
    difZ[2] = (-6.0 - zCam) / 100.0;
    targetX[2] = 6.0;
    targetY[2] = 4.5;
    targetZ[2] = -6.0;
    break;

  case BLUE:
    difX[2] = (-6.0 - xCam) / 100.0;
    difY[2] = (4.5 - yCam) / 100.0;
    difZ[2] = (6.0 - zCam) / 100.0;
    targetX[2] = -6.0;
    targetY[2] = 4.5;
    targetZ[2] = 6.0;
    break;

  default:
    break;
  }
  animation[2] = 1;
}

/* DISPLAY */

void playerSideArea(Player p) {
  int i = 0;
  float r = p.r, g = p.g, b = p.b;

  // board center
  glPushMatrix();
  glScalef(3.0, 1.0, 3.0);
  triangle(r, g, b);
  glPopMatrix();

  // Base
  glPushMatrix();
  glTranslatef(2.25, 0.0, 2.25);
  glScalef(6.0, 1.0, 6.0);
  tile(r, g, b);
  glPopMatrix();

  // Circulos
  for (i = 0; i < MAX_PAWNS; i++) {
    glPushMatrix();
    glTranslatef(initialCords[i][0], 0.1, initialCords[i][1]);
    pawnInitialPosition();
    glPopMatrix();
  }

  glPushMatrix();
  glTranslatef(2.25, 0.0, 2.25);
  glScalef(4.0, 1.1, 4.0);
  tile(1, 1, 1);
  glPopMatrix();
  // Base

  glPushMatrix(); // caminho lateral cima
  glTranslatef(0.5, 0.0, -0.5);
  for (i = 0; i < 6; i++) {
    glTranslatef(0.5, 0.0, 0.0);
    tile(1.0, 1.0, 1.0);
  }
  glPopMatrix();

  glPushMatrix(); // caminho central
  glTranslatef(0.5, 0.0, 0.0);
  for (i = 0; i < 5; i++) {
    glTranslatef(0.5, 0.0, 0.0);
    tile(r, g, b);
  }
  glTranslatef(0.5, 0.0, 0.0);
  tile(1.0, 1.0, 1.0);
  glPopMatrix();

  glPushMatrix(); // caminho lateral baixo
  glTranslatef(0.5, 0.0, 0.5);
  for (i = 0; i < 6; i++) {
    glTranslatef(0.5, 0.0, 0.0);
    if (i == 4)
      tile(r, g, b);
    else
      tile(1.0, 1.0, 1.0);
  }
  glPopMatrix();
}

void board() {
  GLfloat shininess;
  GLfloat diffuse[4];
  GLfloat specular[4];

  shininess = 65.0;
  diffuse[0] = 0.65;
  diffuse[1] = 0.65;
  diffuse[2] = 0.65;
  diffuse[3] = 1.0;
  specular[0] = 1.0;
  specular[1] = 1.0;
  specular[2] = 1.0;
  specular[3] = 1.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  glPushMatrix();
  glScalef(15.0, 0.25, 15.0);
  cube();
  glPopMatrix();

  for (int i = 0; i < MAX_PLAYERS; i++) {
    glPushMatrix();
    glRotatef(i * mapSideRotation, 0, 1, 0);
    Player p = getPlayerByID(i);
    playerSideArea(p);
    drawPawns(p);
    glPopMatrix();
  }
}

void displayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa o buffer
  glMatrixMode(GL_MODELVIEW); // define que a matrix é a de modelo
  dice(diceResult);
  board();
  glFlush();
}

/* INPUT */

void keyboardSpecialKeys(int tecla, int x, int y) {
  switch (tecla) {
  case GLUT_KEY_RIGHT:
    glRotatef(1, 0.0, 1.0, 0.0);
    break;
  case GLUT_KEY_LEFT:
    glRotatef(-1, 0.0, 1.0, 0.0);
    break;
  case GLUT_KEY_UP:
    glRotatef(1, 1.0, 0.0, 0.0);
    break;
  case GLUT_KEY_DOWN:
    glRotatef(-1, 1.0, 0.0, 0.0);
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case '1':
    printf("selected pawn - 1");
    trySelectPawn(turn, 0);
    break;
  case '2':
    printf("selected pawn - 2");
    trySelectPawn(turn, 1);
    break;
  case '3':
    printf("selected pawn - 3");
    trySelectPawn(turn, 2);
    break;
  case '4':
    printf("selected pawn - 4");
    trySelectPawn(turn, 3);
    break;
  case 'a':
    if (gameState == 0 && turnState == 2)
      tryDrawNewPawn();
    break;
  case 'b':
    returnPawn(turn, 1);
    break;
  case 'c':
    diceResult = 3;
    break;
  case 13:
    printf("DEBUG - INPUT 13");
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  int diceCount = 0;
  switch (button) {
  case GLUT_LEFT_BUTTON:
    if (gameState == 0)
      handleTurn();
    break;
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Ludo");
  glutDisplayFunc(displayFunc);
  init();
  gameInit();
  glutTimerFunc(10, camPosition, 1);
  glutSpecialFunc(keyboardSpecialKeys);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}
