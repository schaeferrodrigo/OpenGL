#include <GL/glut.h>


float camX = 5.f;
float camZ = 5.f;

void keyPressed_special(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            camX -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            camX += 0.1;
            break;
        case GLUT_KEY_UP:
            camZ += 0.1;
            break;
        case GLUT_KEY_DOWN:
            camZ -= 0.1;
            break;
    }
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y){
    switch(key){
        case 'r':
            camX = 5.f;
            camZ = 5.f;
            break;
    }
    glutPostRedisplay();
}

void init(void){
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);

   

    }

void display(void){

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX,2,camZ, //camera position
        0,0,0, //look at
        0,1,0 //up vector
          );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glColor3f(1.0, 0.0, 0.0);
    
    glutWireSphere(4.0, 20,20);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500 ,500);
    glutInitWindowPosition( 100, 100);  
    glutCreateWindow("Exercise 2");

    init();
    glutSpecialFunc(keyPressed_special);
    glutKeyboardFunc(keyPressed);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}