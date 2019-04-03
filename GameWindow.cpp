#include "GameWindow.h"

int GameWindow::getSWidth()
{
	return SWidth;
}

int GameWindow::getSHeight()
{
	return SHeight;
}

void GameWindow::Reshape(GLsizei SWidth, GLsizei SHeight)
{
	if (SHeight == 0)	
		SHeight = 1;
	
	GLfloat aspect = (GLfloat) SWidth / GLfloat (SHeight);
	glViewport(0, 0, SWidth, SHeight);										//specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
	glMatrixMode(GL_PROJECTION);											//used to create the viewing volume
	glLoadIdentity();														//replace the current matrix with the identity matrix
	if (SWidth >= SHeight)
	{
		ClipXLeft = -1.0 * aspect;
		ClipXRight = 1.0 * aspect;
		ClipYTop = 1.0;
		ClipYBottom = -1.0;
	}
	else
	{
		ClipXLeft = -1.0;
		ClipXRight = 1.0;
		ClipYTop = 1.0 /aspect;
		ClipYBottom = -1.0 / aspect;
	}
	gluOrtho2D(ClipXLeft, ClipXRight, ClipYBottom, ClipYTop);
}
