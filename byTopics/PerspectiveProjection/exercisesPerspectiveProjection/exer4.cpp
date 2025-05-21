#include <GL/freeglut.h>

GLfloat lightPos[] = {2.0f, 2.0f, 2.0f, 1.0f}; // Initial position of the point light

// Material properties
GLfloat mat_metal_ambient[] = {0.25, 0.25, 0.25, 1.0};
GLfloat mat_metal_diffuse[] = {0.4, 0.4, 0.4, 1.0};
GLfloat mat_metal_specular[] = {0.774597, 0.774597, 0.774597, 1.0};
GLfloat mat_metal_shininess[] = {76.8};

GLfloat mat_plastic_ambient[] = {0.0, 0.1, 0.06, 1.0};
GLfloat mat_plastic_diffuse[] = {0.0, 0.50980392, 0.50980392, 1.0};
GLfloat mat_plastic_specular[] = {0.50196078, 0.50196078, 0.50196078, 1.0};
GLfloat mat_plastic_shininess[] = {32.0};

GLfloat mat_wood_ambient[] = {0.4, 0.2, 0.07, 1.0};
GLfloat mat_wood_diffuse[] = {0.4, 0.2, 0.07, 1.0};
GLfloat mat_wood_specular[] = {0.0, 0.0, 0.0, 1.0};
GLfloat mat_wood_shininess[] = {0.0};

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    // Setup directional light (GL_LIGHT0)
    GLfloat light0_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_position[] = {0.0, 0.0, 1.0, 0.0}; // Directional light along +Z
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glEnable(GL_LIGHT0);
    
    // Setup point light (GL_LIGHT1)
    GLfloat light1_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light1_specular[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
    glEnable(GL_LIGHT1);
    
    // Material properties for the sphere
    GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // Update point light position
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);

    // Draw the light source
      // Metal Cube (left)
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_metal_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_metal_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_metal_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, mat_metal_shininess);
      glPushMatrix();
      glTranslatef(-3.0, 0.0, 0.0);
      glutSolidCube(1.5);
      glPopMatrix();
      
      // Plastic Sphere (center)
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_plastic_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_plastic_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_plastic_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, mat_plastic_shininess);
      glPushMatrix();
      glutSolidSphere(1.0, 50, 50);
      glPopMatrix();
      
      // Wood Cylinder (right)
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_wood_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_wood_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_wood_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, mat_wood_shininess);
      glPushMatrix();
      glTranslatef(3.0, 0.0, 0.0);
      glRotatef(-90.0, 1.0, 0.0, 0.0);
      glutSolidCylinder(0.8, 2.0, 20, 20);
      glPopMatrix();
    
    
    // Draw the ground plane
    GLfloat ground_ambient[] = {0.2, 0.6, 0.2, 1.0};
    GLfloat ground_diffuse[] = {0.2, 0.6, 0.2, 1.0};
    GLfloat ground_specular[] = {0.0, 0.0, 0.0, 1.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ground_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ground_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ground_specular);
    
    glBegin(GL_QUADS);
    glVertex3f(-10.0, -1.0, -10.0);
    glVertex3f(-10.0, -1.0,  10.0);
    glVertex3f( 10.0, -1.0,  10.0);
    glVertex3f( 10.0, -1.0, -10.0);
    glEnd();
    
    // Draw the light source as a small yellow sphere
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 1.0, 100.0);
}

void specialKeys(int key, int x, int y) {
    float step = 0.5;
    switch (key) {
        case GLUT_KEY_LEFT:  lightPos[0] -= step; break;
        case GLUT_KEY_RIGHT: lightPos[0] += step; break;
        case GLUT_KEY_UP:    lightPos[2] -= step; break;
        case GLUT_KEY_DOWN:  lightPos[2] += step; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lighting Example");
    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    
    glutMainLoop();
    return 0;
}