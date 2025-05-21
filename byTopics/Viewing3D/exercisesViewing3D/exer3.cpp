#include <GL/glut.h>
#include <iostream>


float nearPlane = -5.0f;
float farPlane  =  5.0f;

void init(void){
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void specialKeyPressed(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: // Use GLUT_KEY_UP for '+'
            nearPlane += 0.5f; // Increase near plane
            if (nearPlane > -1.0f) nearPlane = -1.0f;
            break;
        case GLUT_KEY_DOWN: // Use GLUT_KEY_DOWN for '-'
            nearPlane -= 0.5f; // Decrease near plane
            if (nearPlane < -10.0f) nearPlane = -10.0f;
            break;
        case GLUT_KEY_LEFT: // Use GLUT_KEY_LEFT for '<'
            farPlane -= 0.5f;  // Decrease far plane
            if (farPlane < 1.0f) farPlane = 1.0f;
            break;
        case GLUT_KEY_RIGHT: // Use GLUT_KEY_RIGHT for '>'
            farPlane += 0.5f;  // Increase far plane
            if (farPlane > 10.0f) farPlane = 10.0f;
            break;
    }
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y) {
    switch(key) {
        case 'r':
            nearPlane = -5.0f;
            farPlane = 5.0f;
            break;
    }
    glutPostRedisplay();
}

void display(void){


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    glOrtho(-5.0, 5.0, -5.0, 5.0, nearPlane, farPlane); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, //camera position
        0,0,0, //look at
        0,1,0 //up vector
          );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glColor3f(1.0, 0.0, 0.0);
    
    glutWireSphere(1.0, 20,20);

    glTranslatef(2.0, 0.0, 0.0);
    glutWireCube(1.0);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500 ,500);
    glutInitWindowPosition( 100, 100);  
    glutCreateWindow("Exercise 3");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutSpecialFunc(specialKeyPressed); 
    glutMainLoop();
    return 0;
    
}