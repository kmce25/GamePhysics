#pragma once
#include <glm\glm.hpp>
#include <gl/glut.h>

class GameWindow
{
private:
	int SWidth;
	int SHeight;
	double ClipXLeft, ClipXRight, ClipYTop, ClipYBottom;

public:
	GameWindow(int WindowWidth, int WindowHeight, int ScreenPosX, int ScreenPosY) //NTS : Pointer because thats how it is in glut "glutCreateWindow(const char *title);"
		: SWidth(WindowWidth), SHeight(WindowHeight)												 // SWidth = WindowWidth, SHeight = WindowHeight
	{
		glutInitDisplayMode(GLUT_DOUBLE);															 // Enable double buffered mode
		glutInitWindowSize(WindowWidth, WindowHeight);
		glutInitWindowPosition(ScreenPosX, ScreenPosY);
		glutCreateWindow("Pool Game");
	}

	virtual ~GameWindow() {}
	int getSWidth();
	int getSHeight();
	void Reshape(GLsizei SWidth, GLsizei SHeight);

};