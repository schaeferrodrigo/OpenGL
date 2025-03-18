#include <GL/glut.h>

void init(void){
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,3,0, //camera position
        0,0,0, //look at
        0,0,-1 //up vector
          );

    }

void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glColor3f(1.0, 0.0, 0.0);
    
    glutWireSphere(1.0, 20,20);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500 ,500);
    glutInitWindowPosition( 100, 100);  
    glutCreateWindow("Exercise 1");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}