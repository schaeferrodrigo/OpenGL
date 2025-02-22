#include <GL/glut.h>
//##include <windows..h>>  only for Windows system

int init(void){

    glClearColor(1.0, 1.0, 1.0, 0.0); // set background color to white
    glMatrixMode(GL_PROJECTION); // set projection parameters
    gluOrtho2D(0.0, 200.0, 0.0, 150.0); // set 2D orthographic projection
    return 0;
}

void drawObject(){
    glBegin(GL_POLYGON); // draw primitive
    glVertex2f(110, 50); // draw point
    glVertex2f(110, 70); // draw point
    glVertex2f(100, 80); // draw point
    glVertex2f(90, 70); // draw point
    glVertex2f(90,50); // draw point
    glEnd();
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT); // clear display window
    glColor3f(1.0, 0.0, 0.0); // set color to red
    glMatrixMode(GL_MODELVIEW); // set modelview parameters
    glLoadIdentity(); // reset modelview matrix 

    //scaling with a fixed point (110, 50)
    glTranslatef(110.0, 50.0, 0.0); // move to the origin
    glScalef(2.0, 2.0, 1.0); // scale object
    glTranslatef(-110.0, -50.0, 0.0); // return to the original position

    drawObject();  

    glFlush(); // force execution of OpenGL commands in finite time
}

int main(int argc, char** argv)
{
    glutInit( &argc, argv); // start glut
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); // set display mode - single buffer, RGB  color
    glutInitWindowSize(400, 300); // set window size
    glutInitWindowPosition(400,400); // set window position

    //Create the window        
    glutCreateWindow("Example: Applying Transformations"); // create window

    init(); // initialize
    glutDisplayFunc(display); // set display callback
    glutMainLoop(); // enter event loop

    
    return 0;
}
