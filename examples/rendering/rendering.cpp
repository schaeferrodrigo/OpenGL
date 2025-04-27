#include <math.h>
#include <GL/glut.h>
#include <iostream>

#define X 0.525731112119133696
#define Z 0.856050808352039932

static GLfloat vdata[12][3] = {
{-X, 0.0, Z}, {X, 0.0 , Z}, {-X,0.0,-Z}, {X,0.0, -Z},
{0.0, Z, X}, {0.0 , Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
{Z,X,0.0}, {-Z, X, 0.0} , {Z,-X, 0.0}, {-Z,-X,0.0}
};

static int tindices[20][3] ={
{1,4,0}, {4,9,0},{4,5,9},{8,5,4}, {1,8,4},
{1,10,8}, {10,3,8},{8,3,5},{3,2,5}, {3,7,2},
{3,10,7}, {10,6,7},{6,11,7},{6,0,11}, {6,1,0},
{10,1,6}, {11,0,9},{2,11,9},{5,2,9}, {11,2,7}
};

//reflectio properties
GLfloat ks[] = {0.0,0.0,0.0,1.0};
GLfloat kd[] = {0.8,0.6,0.4,1.0};
GLfloat ns = 100;

//light position
GLfloat light_ambient[] = {0.2,0.2,0.2,1.0};
GLfloat light_diffuse[] = {1.0,1.0,1.0,1.0};
GLfloat light_specular[] = {1.0,1.0,1.0,1.0};
GLfloat light_position[] = {-1.0,1.1,2.5,1.0}; //local light source

int flat = 1 ; // 0 Gouraud method, 1 flat
int subdiv = 0; //number of subdivisions

void init(){
    glClearColor(0.0, 0.0, 0.0 , 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.5,0.5,-1.5,
        0.0,0.0,0.0,
        0.0,1.0,0.0
        );
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.25,1.25,-1.25,1.25,-2.0,2.0);
}

void keyboard(unsigned char key, int x, int y){
    switch(key){

        case 'Q':
        case 'q':
            exit(0);
            break;
        case '+':
            subdiv++;
            break;
        case '-':
            if(subdiv>0){subdiv--;}
            break;
        case 'f':
        case 'F':
            flat = 1;
            break;
        case 's':
        case 'S':
            flat = 0;
            break;
    }
    glutPostRedisplay();
}

void normalize(GLfloat v[3]){
    GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if(d==0.0){
        std::cout <<"zero length vector\n" << std::endl;
        return;
    }
    v[0] /= d; v[1] /= d; v[2] /= d;
}

void normCrossProduct(GLfloat u[3], GLfloat v[3], GLfloat n[3]){
    n[0] = u[1]*v[2] - u[2]*v[1];
    n[1] = u[2]*v[0] - u[0]*v[2];
    n[2] = u[0]*v[1] - u[1]*v[0];
}

void normFace(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]){
    GLfloat d1[3], d2[3], normal[3];
    for(int k = 0; k<3; k++){
        d1[k] = v1[k] - v2[k];
        d2[k] = v2[k] - v3[k];
    }
    normCrossProduct(d1,d2,normal);
    glNormal3fv(normal);
}

void draw_triangleFLAT(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]){
    glBegin(GL_TRIANGLES);
    normFace(v1,v2,v3);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glEnd();
}

void draw_triangleGOURAUD(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]){
    glBegin(GL_TRIANGLES);
    glNormal3fv(v1);
    glVertex3fv(v1);
    glNormal3fv(v2);
    glVertex3fv(v2);
    glNormal3fv(v3);
    glVertex3fv(v3);
    glEnd();
}

void subdivide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth){
    GLfloat v12[3], v23[3], v31[3];
    if(depth == 0){
        if(flat==1)
            draw_triangleFLAT(v1,v2,v3);
        else
            draw_triangleGOURAUD(v1,v2,v3);
        return;
    }
    for(int i = 0; i<3; i++){
        v12[i] = (v1[i] + v2[i])/2;
        v23[i] = (v2[i] + v3[i])/2;
        v31[i] = (v3[i] + v1[i])/2;
        }
    normalize(v12);
    normalize(v23);
    normalize(v31);
    subdivide(v1,v12,v31,depth-1);
    subdivide(v2,v23,v12,depth-1);
    subdivide(v3,v31,v23,depth-1);
    subdivide(v12,v23,v31,depth-1);
}
    
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

   
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    for(int  i = 0; i<20; i++){
        subdivide(&vdata[tindices[i][0]][0], &vdata[tindices[i][1]][0], &vdata[tindices[i][2]][0], subdiv);
   
    }
    glutSwapBuffers();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Icosahedron");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

