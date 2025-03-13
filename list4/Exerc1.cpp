#include <GL/glut.h>




GLfloat shearMatrix[]{
	 1.0f , 0.5f, 0.5f , 0.f,
	 0.f , 1.f, 0.f , 0.f,
	 0.f , 0.f, 1.f , 0.f,
	 0.f , 0.f, 0.f , 1.f
};


void init(void) {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -5, 5);


}

void drawCube() {
	glutWireSphere(2.0, 30, 30);
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Top-left
	glViewport(0,300, 300, 300);

	glPushMatrix();
	glColor3f(1.f, 0.f, 0.f);
	glRotatef(30, 1, 0, 0);
	drawCube();
	glPopMatrix();

	
	//top-right
	glViewport(300, 300, 300, 300);

	glPushMatrix();
	glColor3f(0.f, 1.f, 0.f);
	glRotatef(30, 0, 1, 0);
	drawCube();
	glPopMatrix();

	//bottom-left
	glViewport(0,0,300,300);
	
	glPushMatrix();
	glColor3f(0.f, 0.f, 1.f);
	glMultMatrixf(shearMatrix);
	drawCube();
	glPopMatrix();
	

	//bottom-right
	glViewport(300, 0, 300, 300);

	glPushMatrix();
	glColor3f(1.f,1.f, 0.f);
	glScalef(2,2, 2);
	drawCube();
	glPopMatrix();
	

	glFlush();

	}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Exercise 1");

	init();
	glutDisplayFunc(display);
	glutMainLoop();

		return 0;
}


