#include <GL/glut.h>
#include <cmath>

float angle = 0;  // For animation

// Shear matrix for asteroid field
GLfloat shearMatrix[] = {
    1.0f, 0.5f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

void drawShip() {
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
}

void timer(int) {
    angle += 1.0f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // ~60 FPS
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set clipping window (Step 8)
    glMatrixMode(GL_PROJECTION);

    // Four viewports (Step 9)
    int viewports[4][4] = {
        {0, 300, 300, 300},    // Bottom-left
        {300, 300, 300, 300},  // Bottom-right
        {0, 0, 300, 300},      // Top-left
        {300, 0, 300, 300}     // Top-right
    };

    for (int i = 0; i < 4; i++) {
        glViewport(viewports[i][0], viewports[i][1],
            viewports[i][2], viewports[i][3]);

        glLoadIdentity();
        gluOrtho2D(-2.0, 2.0, -1.5, 1.5);  // Clipping window

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();
        switch (i) {
        case 0:  // Translation World (Step 3)
            glColor3f(1, 0, 0);
            glTranslatef(0.5f, 0.0f, 0.0f);
            break;

        case 1:  // Rotation Planet (Step 4 + animation)
            glColor3f(0, 1, 0);
            glTranslatef(0.5f, 0.5f, 0.0f);
            glRotatef(angle, 0, 0, 1);  // Animated
            glTranslatef(-0.5f, -0.5f, 0.0f);
            break;

        case 2:  // Scaling Moon (Step 5) + Reflection (Step 6)
            glColor3f(0, 0, 1);
            glTranslatef(-0.5f, 0.0f, 0.0f);
            glScalef(-0.5f, 0.5f, 1.0f);
            break;

        case 3:  // Shear Asteroid (Step 7)
            glColor3f(1, 1, 0);
            glMultMatrixf(shearMatrix);
            break;
        }
        drawShip();
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Shape Odyssey - Complete");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}