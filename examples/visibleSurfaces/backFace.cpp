#include <GL/glut.h> 


void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);

    //activate the depth test
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES); //counterclockwise direction - V .  N < 0 visible
        glVertex3f(-2, -2, 0);
        glVertex3f(2, -2, 0);
        glVertex3f(0, 2, 0);
    glEnd();


    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES); //clockwise direction - V .  N > 0 not visible
    glVertex3f(-4,-2,-4);
    glVertex3f(-3.5,0,-4);
    glVertex3f(-3,-2,-4);
    glEnd();
    
    glFlush();
}

int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH| GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Back face culling");

    glutDisplayFunc(display);

    init();
    glutMainLoop();
    return 0;


}