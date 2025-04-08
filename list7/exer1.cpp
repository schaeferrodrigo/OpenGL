 #include <GL/glut.h>


 void lighting(){

     float direction[4] = {0.0f, 0.0f , 1.0f , 0.0f}; //coming from z-axis at infinity
     float color[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // white light
     float ambient[4] = {0.f, 0.f, 0.f, 1.f};


     //exerc 2
     float position[4] = {2.0f, 1.0f, 0.0f, 1.0f};


     glLightfv(GL_LIGHT0, GL_POSITION, direction);
     glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
     glLightfv(GL_LIGHT0, GL_SPECULAR, color);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, color);

     
     //exerc 2
     glLightfv(GL_LIGHT1, GL_POSITION, position);
     glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
     glLightfv(GL_LIGHT1, GL_SPECULAR, color);
     glLightfv(GL_LIGHT1, GL_DIFFUSE, color);
     
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_LIGHT1); //exerc 2
   

 }


 int init (){
   
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 2.0, 2.0, 
                0.0, 0.0, 0.0,
                 0.0, 1.0, 0.0);

   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(80.0f, 1.0f, 0.1f, 50.0f);

    lighting();

    return 0;

 }

 void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glMatrixMode(GL_MODELVIEW);
   //glLoadIdentity();
    //glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
    glutSolidCube(1.0);

    glPushMatrix();
    float material[4] = {0.65f, 0.65f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material);
    glTranslatef(2.0f, 1.0f, 0.0f);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();

    glFlush();


 }

 int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise 1");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
 }