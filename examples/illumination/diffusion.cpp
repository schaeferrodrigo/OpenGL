#include <GL/glut.h>
#include <iostream>

enum LightSetup { AMBIENT_DIFFUSE, LOCAL_DIFFUSE, COMBINED_LIGHTING };
LightSetup currentLighting = AMBIENT_DIFFUSE;

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  // Default to no ambient
    GLfloat diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };  // Default to no diffuse
    GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Default to no position

    switch (currentLighting) {
        case AMBIENT_DIFFUSE:
            // Ambient + Diffuse global light
            ambient[0] = 0.2f; ambient[1] = 0.2f; ambient[2] = 0.2f;
            diffuse[0] = 0.6f; diffuse[1] = 0.6f; diffuse[2] = 0.6f;
            lightPos[0] = 0.0f; lightPos[1] = 0.0f; lightPos[2] = 1.0f; // Directional light
            break;

        case LOCAL_DIFFUSE:
            // Local Point Light with Diffuse Only
            ambient[0] = 0.0f; ambient[1] = 0.0f; ambient[2] = 0.0f;  // No ambient
            diffuse[0] = 1.0f; diffuse[1] = 1.0f; diffuse[2] = 1.0f;  // Full diffuse
            lightPos[0] = 2.0f; lightPos[1] = 2.0f; lightPos[2] = 2.0f; // Point light
            break;

            case COMBINED_LIGHTING:
            ambient[0] = 0.3f; ambient[1] = 0.3f; ambient[2] = 0.3f; // Slightly higher ambient light
            diffuse[0] = 1.0f; diffuse[1] = 1.0f; diffuse[2] = 1.0f; // Full diffuse light intensity
            lightPos[0] = 2.0f; lightPos[1] = 2.0f; lightPos[2] = 3.0f; // Move point light further for stronger effect
            break;
    }

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    setupLighting();

    // Set material color
    GLfloat materialColor[] = { 0.8f, 0.2f, 0.2f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

    glPushMatrix();
    glRotatef(30, 1, 1, 0);
    glutSolidCube(1.0);
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            currentLighting = AMBIENT_DIFFUSE;
            std::cout << "Switched to Ambient + Diffuse Global Light" << std::endl;
            break;
        case '2':
            currentLighting = LOCAL_DIFFUSE;
            std::cout << "Switched to Local Point Light with Diffuse" << std::endl;
            break;
        case '3':
            currentLighting = COMBINED_LIGHTING;
            std::cout << "Switched to Combined Ambient + Local Diffuse Light" << std::endl;
            break;
        case 27: // ESC key
            exit(0);
            break;
    }
    glutPostRedisplay();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Switch Between Lighting Setups");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

