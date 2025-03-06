#include <GL/glut.h>

float angle;

void timer(int) {

    angle += 1.0f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); 
}

GLfloat shearMatrix[]{
     1.0f , 0.5f, 0.f , 0.f,
     0.f , 1.f, 0.f , 0.f,
     0.f , 0.f, 1.f , 0.f,
     0.f , 0.f, 0.f , 1.f
};


void triangle() {
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f ,- 0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
}

int init(void) {
    
    glClearColor(0.f, 0.f, 0.f,1.f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-2.0, 2.0, -1.5, 1.5);
    return 0;
}



void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    int viewports[4][4]{
        {0,0, 300 ,300},
        {300, 0, 300,300},
        {0,300, 300 , 300},
        {300,300,300,300}
    };

    for (int i = 0; i < 4; i++) {
        glViewport(viewports[i][0], viewports[i][1],
            viewports[i][2], viewports[i][3]);

       glLoadIdentity();
       
       glPushMatrix();

       switch (i) {

       case 0:

           glColor3f(1.0f, 0.0f, 0.0f);
           glTranslatef(0.5f, 0.0, 0.0);
           break;

       case 1:
           glColor3f(0.f, 1.f, 0.f);
           glRotatef(angle, 0.f, 0.f, 1.f);
           break;

       case 2:

           glColor3f(0.f, 0.f, 1.f);
           glScalef(-0.5f, 0.5f, 1.0f);
           break;

       case 3: 
           glColor3f(1.f, 1.f, 1.f);
           glMultMatrixf(shearMatrix);
           break;
       
       }
       
        triangle();
           
        
        glPopMatrix();

    }

    glFlush();
    
    glutSwapBuffers();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(600,600);
    glutInitWindowPosition(400, 400);

    glutCreateWindow("Practical Activity");

    init();
    glutDisplayFunc(display);

    glutTimerFunc(0, timer, 0);
    glutMainLoop();

 
    return 0;
}