#include <GL/glut.h>
//##include <windows..h>>  only for Windows system

int init(void){

    glClearColor(1.0, 1.0, 1.0, 0.0); // set background color to white
    glMatrixMode(GL_PROJECTION); // set projection parameters
    gluOrtho2D(0.0, 200.0, 0.0, 150.0); // set 2D orthographic projection
    return 0;
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT); // clear display window
    glColor3f(0.0, 0.0, 0.0); // set color to black
    glPointSize(10.0); // set point size
    glBegin(GL_QUADS); // draw primitive
    glVertex2i(90, 15); // draw point
    glVertex2i(10, 145); // draw point
    glVertex2i(10, 15); // draw point
    glVertex2i(90, 145); // draw point
    glEnd(); // end drawing points
    glFlush(); // force execution of OpenGL commands in finite time
}

int main(int argc, char** argv)
{
    glutInit( &argc, argv); // start glut
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); // set display mode - single buffer, RGB  color
    glutInitWindowSize(400, 300); // set window size
    glutInitWindowPosition(400,400); // set window position

    //Create the window        
    glutCreateWindow("Hello World - my first window"); // create window

    init(); // initialize
    glutDisplayFunc(display); // set display callback
    glutMainLoop(); // enter event loop

    
    return 0;
}
