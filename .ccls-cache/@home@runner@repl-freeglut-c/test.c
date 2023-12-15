// shading.c by qcm

#include <GL/glut.h>
#include <math.h>

// Light position
GLfloat lightPos[] = { 2.0f, 2.0f, 2.0f, 1.0f };

// Sphere position
GLfloat spherePos[] = { 0.0f, 0.0f, 0.0f };

// Camera parameters
GLfloat cameraRadius = 4.0f;
GLfloat cameraAngle = 0.0f;
GLfloat cameraSpeed = 360.0f / 15.0f; // 1 full rotation every 15 seconds

// Grid parameters
int gridSize = 10;
int gridSpacing = 1;

// Rotation speed increment/decrement
GLfloat speedIncrement = 10.0f;

// Camera angle increment/decrement
GLfloat angleIncrement = 10.0f;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the light source
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Set up the material properties
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat shininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    // Set up the camera position
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat cameraX = cameraRadius * sin(cameraAngle * 3.14159f / 180.0f);
    GLfloat cameraZ = cameraRadius * cos(cameraAngle * 3.14159f / 180.0f);
    gluLookAt(cameraX, 3.0, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw the sphere
    glutSolidSphere(1.0, 50, 50);

    // Draw the grid
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = -gridSize; i <= gridSize; i += gridSpacing) {
        glVertex3f(i, -1.0f, -gridSize);
        glVertex3f(i, -1.0f, gridSize);
        glVertex3f(-gridSize, -1.0f, i);
        glVertex3f(gridSize, -1.0f, i);
    }
    glEnd();

    // Set up the text position
    glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white
    glRasterPos3f(1.0f, 1.5f, 0.0f); // Position the text

    // Display the text using GLUT bitmap fonts
    const char* text = "arrow keys camera , A/Z speed, S stop";
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        ++text;
    }

    glFlush();
}

void timerFunc(int value) {
    // Update the camera angle
    cameraAngle += cameraSpeed * 0.01f; // 0.01 seconds elapsed

    // Redraw the scene
    glutPostRedisplay();

    // Set the timer for the next update
    glutTimerFunc(10, timerFunc, 0); // 10 milliseconds interval
}

void reshapeWindow(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void specialKeyHandler(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            cameraRadius -= 0.1f;
            if (cameraRadius < 0.1f)
                cameraRadius = 0.1f;
            break;
        case GLUT_KEY_DOWN:
            cameraRadius += 0.1f;
            break;
        case GLUT_KEY_LEFT:
            cameraAngle += angleIncrement;
            break;
        case GLUT_KEY_RIGHT:
            cameraAngle -= angleIncrement;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void keyboardHandler(unsigned char key, int x, int y) {
    switch (key) {
        case 'A':
        case 'a':
            cameraSpeed += speedIncrement;
            break;
        case 'S':
        case 's':
            cameraSpeed = 0;
        case 'Z':
        case 'z':
            if (cameraSpeed <= 0)
            cameraSpeed = 0;
        else
            cameraSpeed -= speedIncrement;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Sphere Example");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshapeWindow);
    glutSpecialFunc(specialKeyHandler); // Register special key event handler
    glutKeyboardFunc(keyboardHandler); // Register regular key event handler
    glutTimerFunc(0, timerFunc, 0); // Start the timer
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();

    return 0;
}
