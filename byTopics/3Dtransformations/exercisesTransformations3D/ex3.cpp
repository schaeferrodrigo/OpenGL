#include <GL/glut.h>
#include <cmath>


float angle = 0.0;

void timer(int value) {

    angle += 0.1f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(40, timer, 0);
}



int init(void) {
    glClearColor(0.0, 0.0, 0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluLookAt(0.0, 1.0, 0.0,
        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0);

    glOrtho(-5.2, 5.2, -5.2, 5.2, -5.2, 5.2);

    return 0;
}



void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    glPushMatrix();
    glColor4f(1.f, 1.f, 0.0f, 1.0f);
    glRotatef(angle, 1, 0, 0);
    glScalef(5*cos(angle)*cos(angle), 5 * cos(angle)*cos(angle), 5 * cos(angle) * cos(angle));
    glutWireSphere(1, 30, 30);
    glPopMatrix();

    
    glutSwapBuffers();
}





int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ex3");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(40, timer, 1);
    glutMainLoop();
  
    return 0;
}