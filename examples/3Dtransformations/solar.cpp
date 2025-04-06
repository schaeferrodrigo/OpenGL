#include <GL/glut.h>

float  day = 0, hour = 0;


void timer(int value){
    hour += 1;
    if (hour == 24){
        day += 1;
        hour = 0;
        if (day == 365){
            day = 0;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(40, timer, 1); // 40 miliseconds = 1 hour
}

int init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluLookAt(0.0,1.0,0.0,    // camera position
                0.0,0.0,0.0,   // center of the scene
               1.0,0.0,0.0);   // up vector
    glOrtho(-5.2, 5.2,-5.2,5.,2-5.2, 5.2);
    return 0;
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix(); //sun
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glRotatef(360.0f/28.0f*day, 0.0, 0.1, 0.0);
    glutWireSphere(1, 20, 20);
    glPopMatrix();

    glPushMatrix(); //earth
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glRotatef(day, 0,1 ,0);
    glTranslatef(4, 0, 0);
    glRotatef(360.0f/24.0f*hour, 0,1,0);
    glutWireSphere(0.5, 10,10);


    glColor4f(0.81,0.78,0.79, 1.0);
    glRotatef(360.0f/28.0f*day, 0,1,0);
    glTranslatef(1.0, 0.0, 0.0);
    glutWireSphere(0.2, 10,10);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Solar System");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(40, timer, 1);
    glutMainLoop();
    return 0;
}

