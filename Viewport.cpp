#include <GL/glut.h>

int init(void) {

	glClearColor(1.0, 1.0, 1.0, 0.0); // white window
	glMatrixMode(GL_PROJECTION); 
	gluOrtho2D(-100.0, 100.0 , -100.0 , 100.0); // Clipping window
	return 0;
}

void drawObject() {
	
	glBegin(GL_TRIANGLES);
		glVertex2f(50.0, -50.0);
		glVertex2f(0.0, 50.0);
		glVertex2f(-50.0, -50.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex2f(-99.0,-99.0);
		glVertex2f(99.0,-99.0);
		glVertex2f(99.0,99.0);
		glVertex2f(-99.0,99.0);
	glEnd();

	/* note that the two objects are completely  inside the clipping window */

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT); //
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* First viewport */
	glViewport(10, 10, 200,200); // square (as the clipping view)  resolution 200x200 pixels
	glColor3f(1.0f, 0.0f, 0.0f); //red color
	drawObject();
  
	/* Second viewport */
	glViewport(310, 50, 100, 100); // square (as the clipping view)  resolution 200x200 pixels
	glColor3f(0.0f, 1.0f, 0.0f); //red color
	glRotatef(90, 0, 0, 1); // rotate 90 degrees
	drawObject();

	glFlush();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // start glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode - single buffer, RGB  color
	glutInitWindowSize(500, 275); // set window size
	glutInitWindowPosition(400, 400); // set window position

	//Create the window        
	glutCreateWindow("Example: Creating viewports"); // create window

	init(); // initialize
	glutDisplayFunc(display); // set display callback
	glutMainLoop(); // enter event loop


	return 0;
}