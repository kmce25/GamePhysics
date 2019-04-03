#include <GL/glut.h>
#include <glm\glm.hpp>
#include "Game.h"
#include "Timer.h"
#include "Table.h"
int refreshMilliseconds = 16;
LowResTimer timer;
double oldTime = 0;

Game *game;																			//Pointer to reference functions in Game

void initGL() 
{
	glClearColor(0.2, 0.2, 0.2, 1.0); 
}

void display() {
	game->Render();
}

void reshape(GLsizei SWidth, GLsizei SHeight)
{
	game->ReshapeWindow(SWidth, SHeight);									
}


void update(int value)
{
	game->update(timer.getTime() - oldTime);
	glutPostRedisplay();																// Post a paint request to activate display()
	glutTimerFunc(refreshMilliseconds, update, 0);										// Subsequent timer call at milliseconds
	oldTime = timer.getTime();
}

void Render()
{
	glutDisplayFunc(display);														// Register callback handler for window re-paint
	glutReshapeFunc(reshape);														// Register callback handler for window re-shape
	glutTimerFunc(0, update, 0);													// First timer call immediately
	initGL();																		// Our own OpenGL initialization
	glutMainLoop();																	// Enter event-processing loop
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);															// Initalise glut
	game = new Game();
	game->Load();
	timer.startTimer();
	Render();
	
	delete game;
	return 0;
}