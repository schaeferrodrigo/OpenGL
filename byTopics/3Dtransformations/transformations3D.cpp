#include <stdio.h>
#include <GL/glut.h>

float alpha = 0, beta = 0, delta = 1;

void init(void){

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5,5, -5, 5, -5, 5);
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 0);
    glRotatef(beta, 0, 1, 0);
    glRotatef(alpha, 1, 0, 0);  
    glScalef(delta, delta, delta);
    glutWireSphere(1.f, 20, 20); // radius, slices, stacks  - center at the origin

    glColor3f(0, 0, 1);
    glTranslatef(0, -1, 0);
    glScalef(4,0.1f, 4);
    glutSolidCube(1.0f); //cube at the origin with side 1
    glFlush();  

}

void kyePressed_special(int key, int x, int y){
    switch(key){
        case GLUT_KEY_PAGE_UP:
            delta= delta*1.1f;
            break;
        case GLUT_KEY_PAGE_DOWN:
            delta = delta*0.9f;
            break;
        case GLUT_KEY_LEFT:
            beta += 1;
            break;
        case GLUT_KEY_RIGHT:
            beta -= 1;
            break;
        case GLUT_KEY_UP:
            alpha -= 1;
            break;
        case GLUT_KEY_DOWN:
            alpha += 1;
            break;
    }
    glutPostRedisplay(); 
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformations 3D"); 

    init();
    glutSpecialFunc(kyePressed_special);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

