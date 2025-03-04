
/*
Step 1: Base Camp - Setup
Objective : Create a blank OpenGL window with black background

Clipping window = [-2 ,2]x [-1.5,1.5]

Window size = 600 x 600

Engagement : "Prepare your spaceship console for launch!"
*/


/*
Step 2: First Contact - Draw Triangle
Objective: Render a white triangle in center
Engagement: "Meet your triangular spaceship!"
 vertices: (-0.5 , 0.5) , (0.5, -0.5) , (0 , 0.5)
*/

/*
Step 3: Translation World
Objective : Move triangle to right side using glTranslatef
Engagement : "Engage thrusters to move right!"

Translate 0.5 on the x direction
*/

#include <GL/glut.h>

void drawSpaceship() {

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glEnd();

}


void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0); //black window
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-2, 2, -1.5, 1.5);
}


void display(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glTranslatef(0.5, 0.0,0.0);
	drawSpaceship();

	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv );
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(400, 400);

	glutCreateWindow("Exercises");

	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}