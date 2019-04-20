#include "Game.h"
#include <glm\glm.hpp>
#include <iostream>
#include <vector>
#include "VerletSolver.h"
#include "Gravity.h"
#include "Balls.h"
#include "Shadow.h"
#include "list"
#include "BallInner.h"
#include "Drag.h"

using namespace std;
using namespace glm;	

//PhysicsParameters* ParametersCueBall;

void Game::Load()
{
	Window = new GameWindow(ScreenWidth, ScreenHeight, 500, 10);
	grid = new Grid(5, ScreenWidth, ScreenHeight);

	solver = new VerletSolver();
	forceRegistry = new ForceRegistry();
	resolver = new ContactResolver();


	Table *BackTable = new Table(vec2(400, 500), vec2(500, 500));
	gameobjects.push_back(BackTable);														
	BackTable->setColor(0.30f, 0.16f, 0.14f);

	Table *table = new Table(vec2(350, 450), vec2(500, 500));
	gameobjects.push_back(table);
	table->setColor(0.0f, 0.3f, 0.0f);
	////////////////////////////////////////////////////////////////////////////////Cushion shadow
	Shadow *BotCusShaw = new Shadow(vec2(350, 11), vec2(500, 52));
	gameobjects.push_back(BotCusShaw);
	BotCusShaw->setColor(0.0f, 0.2f, 0.0f);

	Shadow *TopCusShaw = new Shadow(vec2(350, 11), vec2(500, 950));
	gameobjects.push_back(TopCusShaw);
	TopCusShaw->setColor(0.0f, 0.2f, 0.0f);

	Shadow *LeftCusShaw = new Shadow(vec2(8, 450), vec2(155, 500));
	gameobjects.push_back(LeftCusShaw);
	LeftCusShaw->setColor(0.0f, 0.2f, 0.0f);

	Shadow *RightCusShaw = new Shadow(vec2(8, 450), vec2(845, 500));
	gameobjects.push_back(RightCusShaw);
	RightCusShaw->setColor(0.0f, 0.2f, 0.0f);

	//////////////////////////////////////////////////////////////////////////////////Cushions
	PhysicsParameters* ParametersBotCus = new PhysicsParameters(INFINITY, vec2(500, 48), vec2(0, 0), .0f);								//Bottom cushion - collider
	Gravity* gravity = new Gravity(vec2(0, 0));
	Cushions *BotCus = new Cushions(vec2(316, 8), vec2(500, 48), ParametersBotCus, vec3(0.0f, 0.3f, 0.0f));
	dynObjs.push_back(BotCus);

	PhysicsParameters* ParametersLeftBotCus = new PhysicsParameters(INFINITY, vec2(150, 275), vec2(0, 0), .0f);							//Bottom Left cushion - collider
	Gravity* gravityLBC = new Gravity(vec2(0, 0));
	Cushions *LeftBotCus = new Cushions(vec2(8, 190), vec2(146, 500), ParametersLeftBotCus, vec3(0.0f, 0.3f, 0.0f));
	dynObjs.push_back(LeftBotCus);

	PhysicsParameters* ParametersLeftTopCus = new PhysicsParameters(INFINITY, vec2(150, 725), vec2(0, 0), .0f);							//Top Left cushion - collider
	Gravity* gravityLTC = new Gravity(vec2(0, 0));
	Cushions *LeftTopCus = new Cushions(vec2(8, 190), vec2(146, 500), ParametersLeftTopCus, vec3(0.0f, 0.3f, 0.0f));
	dynObjs.push_back(LeftTopCus);

	PhysicsParameters* ParametersTopCus = new PhysicsParameters(INFINITY, vec2(500, 954), vec2(0, 0), .0f);								//Top cushion - collider
	Gravity* gravityTC = new Gravity(vec2(0, 0));
	Cushions *TopCus = new Cushions(vec2(316, 8), vec2(146, 500), ParametersTopCus, vec3(0.0f, 0.3f, 0.0f));
	dynObjs.push_back(TopCus);

	PhysicsParameters* ParametersTopRightCus = new PhysicsParameters(INFINITY, vec2(850, 725), vec2(0, 0), .0f);						//Top right cushion - collider
	Gravity* gravityTRC = new Gravity(vec2(0, 0));
	Cushions *TopRightCus = new Cushions(vec2(8, 190), vec2(146, 500), ParametersTopRightCus, vec3(0.0f, 0.3f, 0.0f));
	dynObjs.push_back(TopRightCus);

	PhysicsParameters* ParametersBotRightCus = new PhysicsParameters(INFINITY, vec2(850, 275), vec2(0, 0), .0f);						//Bot right cushion - collider
	Gravity* gravityBRC = new Gravity(vec2(0, 0));
	Cushions *BotRightCus = new Cushions(vec2(8, 190), vec2(146, 500), ParametersBotRightCus, vec3(0.0f, 0.3f, 0.0f));
	dynObjs.push_back(BotRightCus);

	/////////////////////////////////////////////////////////////////////////////////Pockets
	Pockets *BotLeft = new Pockets(35.0f, vec2(150, 50));
	gameobjects.push_back(BotLeft);
	BotLeft->setColor(0.0f, 0.0f, 0.0f);

	Pockets *MidLeft = new Pockets(35.0f, vec2(150, 500));
	gameobjects.push_back(MidLeft);
	MidLeft->setColor(0.0f, 0.0f, 0.0f);

	Pockets *TopLeft = new Pockets(35.0f, vec2(150, 950));
	gameobjects.push_back(TopLeft);
	TopLeft->setColor(0.0f, 0.0f, 0.0f);

	Pockets *BotRight = new Pockets(35.0f, vec2(850, 50));
	gameobjects.push_back(BotRight);
	BotRight->setColor(0.0f, 0.0f, 0.0f);

	Pockets *MidRight = new Pockets(35.0f, vec2(850, 500));
	gameobjects.push_back(MidRight);
	MidRight->setColor(0.0f, 0.0f, 0.0f);

	Pockets *TopRight = new Pockets(35.0f, vec2(850, 950));
	gameobjects.push_back(TopRight);
	TopRight->setColor(0.0f, 0.0f, 0.0f);

	///////////////////////////////////////////////////////////////////////////////////////////////Inner pocket

	PhysicsParameters* ParametersPocketsBotLeft = new PhysicsParameters(INFINITY, vec2(150, 50), vec2(0, 0), .0f);			//Bottom Left pocket collision
	BallInner* BotLeftPockColl = new BallInner(15, ParametersPocketsBotLeft, vec3(1));
	dynObjs.push_back(BotLeftPockColl);

	PhysicsParameters* ParametersPocketsMidLeft = new PhysicsParameters(INFINITY, vec2(150, 500), vec2(0, 0), .0f);			//Mid Left pocket collision
	BallInner* MidLeftPockColl = new BallInner(15, ParametersPocketsMidLeft, vec3(1));
	dynObjs.push_back(MidLeftPockColl);

	PhysicsParameters* ParametersPocketsTopLeft = new PhysicsParameters(INFINITY, vec2(150, 950), vec2(0, 0), .0f);			//Top Left pocket collision
	BallInner* TopLeftPockColl = new BallInner(15, ParametersPocketsTopLeft, vec3(1));
	dynObjs.push_back(TopLeftPockColl);

	PhysicsParameters* ParametersPocketsTopRight = new PhysicsParameters(INFINITY, vec2(850, 950), vec2(0, 0), .0f);		//Top Right pocket collision
	BallInner* TopRightPockColl = new BallInner(15, ParametersPocketsTopRight, vec3(1));
	dynObjs.push_back(TopRightPockColl);

	PhysicsParameters* ParametersPocketsMidRight = new PhysicsParameters(INFINITY, vec2(850, 500), vec2(0, 0), .0f);		//Mid Right pocket collision
	BallInner* MidRightPockColl = new BallInner(15, ParametersPocketsMidRight, vec3(1));
	dynObjs.push_back(MidRightPockColl);

	PhysicsParameters* ParametersPocketsBotRight = new PhysicsParameters(INFINITY, vec2(850, 50), vec2(0, 0), .0f);			//Bottom Right pocket collision
	BallInner* BotRightPockColl = new BallInner(15, ParametersPocketsBotRight, vec3(1));
	dynObjs.push_back(BotRightPockColl);

	Drag* DragBlackBall1 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersBalls = new PhysicsParameters(10, vec2(500, 750), vec2(0, 0), 0.8f);						//Mass, Pos, vel, restit
	Balls* BlackBall = new Balls(20, ParametersBalls, vec3(0, 0, 0));		//Black
	forceRegistry->Add(BlackBall, DragBlackBall1);
	//EntityList.push_back(ball);
	dynObjs.push_back(BlackBall);

	Drag* DragRedBall1 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersRedball = new PhysicsParameters(10, vec2(520, 713), vec2(0, 0), 0.8f);						
	Balls* Redball = new Balls(20, ParametersRedball, vec3(1, 0, 0));	//Red
	forceRegistry->Add(Redball, DragRedBall1);
	//EntityList.push_back(ball);
	dynObjs.push_back(Redball);

	Drag* DragYellowBall1 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersYellowBall1 = new PhysicsParameters(10, vec2(480, 713), vec2(0, 0), 0.8f);						
	Balls* Yellowball = new Balls(20, ParametersYellowBall1, vec3(1, 1, 0));	  //Yellow
	forceRegistry->Add(Yellowball, DragYellowBall1);
	//EntityList.push_back(ball);
	dynObjs.push_back(Yellowball);

	Drag* DragRedBall2 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersRedBall2 = new PhysicsParameters(10, vec2(500, 676), vec2(0, 0), 0.8f);						
	Balls* Redball2 = new Balls(20, ParametersRedBall2, vec3(1, 0, 0));	//Red
	forceRegistry->Add(Redball2, DragRedBall2);
	//EntityList.push_back(ball);
	dynObjs.push_back(Redball2);

	Drag* DragRedBall3 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersRedBall3 = new PhysicsParameters(10, vec2(460, 750), vec2(0, 0), 0.8f);						
	Balls* Redball3 = new Balls(20, ParametersRedBall3, vec3(1, 0, 0));	//Red
	forceRegistry->Add(Redball3, DragRedBall3);
	//EntityList.push_back(ball);
	dynObjs.push_back(Redball3);

	Drag* DragYellowBall2 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersYellowBall2 = new PhysicsParameters(10, vec2(540, 750), vec2(0, 0), 0.8f);						
	Balls* Yellowball2 = new Balls(20, ParametersYellowBall2, vec3(1, 1, 0));	  //Yellow
	forceRegistry->Add(Yellowball2, DragYellowBall2);
	//EntityList.push_back(ball);
	dynObjs.push_back(Yellowball2);

	Drag* DragYellowBall3 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersYellowBall3 = new PhysicsParameters(10, vec2(440, 787), vec2(0, 0), 0.8f);						
	Balls* Yellowball3 = new Balls(20, ParametersYellowBall3, vec3(1, 1, 0));	  //Yellow
	forceRegistry->Add(Yellowball3, DragYellowBall3);
	//EntityList.push_back(ball);
	dynObjs.push_back(Yellowball3);

	Drag* DragRedBall4 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersRedBall4 = new PhysicsParameters(10, vec2(481, 787), vec2(0, 0), 0.8f);						
	Balls* Redball4 = new Balls(20, ParametersRedBall4, vec3(1, 0, 0));	//Red
	forceRegistry->Add(Redball4, DragRedBall4);
	//EntityList.push_back(ball);
	dynObjs.push_back(Redball4);

	Drag* DragYellowBall4 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersYellowBall4 = new PhysicsParameters(10, vec2(522, 787), vec2(0, 0), 0.8f);						
	Balls* Yellowball4 = new Balls(20, ParametersYellowBall4, vec3(1, 1, 0));	  //Yellow
	forceRegistry->Add(Yellowball4, DragYellowBall4);
	//EntityList.push_back(ball);
	dynObjs.push_back(Yellowball4);

	Drag* DragRedBall5 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersRedBall5 = new PhysicsParameters(10, vec2(563, 787), vec2(0, 0), 0.8f);						
	Balls* Redball5 = new Balls(20, ParametersRedBall5, vec3(1, 0, 0));	//Red
	forceRegistry->Add(Redball5, DragRedBall5);
	//EntityList.push_back(ball);
	dynObjs.push_back(Redball5);

	Drag* DragYellowBall5 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersYellowBall5 = new PhysicsParameters(10, vec2(587, 823), vec2(0, 0), 0.8f);						
	Balls* Yellowball5 = new Balls(20, ParametersYellowBall5, vec3(1, 1, 0));	  //Yellow
	forceRegistry->Add(Yellowball5, DragYellowBall5);
	//EntityList.push_back(ball);
	dynObjs.push_back(Yellowball5);

	Drag* DragRedBall6 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersRedBall6 = new PhysicsParameters(10, vec2(547, 823), vec2(0, 0), 0.8f);						
	Balls* Redball6 = new Balls(20, ParametersRedBall6, vec3(1, 0, 0));	//Red
	forceRegistry->Add(Redball6, DragRedBall6);
	//EntityList.push_back(ball);
	dynObjs.push_back(Redball6);

	Drag* DragYellowBall6 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersYellowBall6 = new PhysicsParameters(10, vec2(507, 823), vec2(0, 0), 0.8f);						
	Balls* Yellowball6 = new Balls(20, ParametersYellowBall6, vec3(1, 1, 0));	  //Yellow
	forceRegistry->Add(Yellowball6, DragYellowBall6);
	//EntityList.push_back(ball);
	dynObjs.push_back(Yellowball6);


	Drag* DragRedBall7 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersRedBall7 = new PhysicsParameters(10, vec2(467, 823), vec2(0, 0), 0.8f);						
	Balls* Redball7 = new Balls(20, ParametersRedBall7, vec3(1, 0, 0));	//Red
	forceRegistry->Add(Redball7, DragRedBall7);
	//EntityList.push_back(ball);
	dynObjs.push_back(Redball7);

	Drag* DragYellowBall7 = new Drag(5.0f, 0.0f);
	PhysicsParameters* ParametersYellowBall7 = new PhysicsParameters(10, vec2(427, 823), vec2(0, 0), 0.8f);						
	Balls* Yellowball7 = new Balls(20, ParametersYellowBall7, vec3(1, 1, 0));	  //Yellow
	forceRegistry->Add(Yellowball7, DragYellowBall7);
	//EntityList.push_back(ball);
	dynObjs.push_back(Yellowball7);


	////////////////////////////////////////////////////////////////////////////////////////////////////Cue ball
	Drag* DragCueBall = new Drag(10.0f, 0.0f);
	PhysicsParameters* ParametersCueBall = new PhysicsParameters(10, vec2(500, 250), vec2(0, 1000), 0.8f);						
	Balls* CueBall = new Balls(25, ParametersCueBall, vec3(1, 1, 1));	  //White
	forceRegistry->Add(CueBall, DragCueBall);
	dynObjs.push_back(CueBall);

	////////////////////////////////////////////////////////////////////////////////////////////////////Decor balls
	Gravity* gravityDecor = new Gravity(vec2(0, -50));
	PhysicsParameters* ParametersDecor = new PhysicsParameters(20, vec2(45, 1000), vec2(0, 0), 0.8f);						//Mass, Pos, vel, restit
	Balls* Decor = new Balls(20, ParametersDecor, vec3(1, 0, 0));
	forceRegistry->Add(Decor, gravityDecor);
	dynObjs.push_back(Decor);

	Gravity* gravityDecor1 = new Gravity(vec2(0, -100));
	PhysicsParameters* ParametersDecor1 = new PhysicsParameters(20, vec2(45, 1000), vec2(0, 0), 0.8f);						
	Balls* Decor1 = new Balls(20, ParametersDecor1, vec3(1, 1, 0));
	forceRegistry->Add(Decor1, gravityDecor1);
	dynObjs.push_back(Decor1);

	Gravity* gravityDecor2 = new Gravity(vec2(0, -150));		
	PhysicsParameters* ParametersDecor2 = new PhysicsParameters(20, vec2(45, 1000), vec2(0, 0), 0.8f);						
	Balls* Decor2 = new Balls(20, ParametersDecor2, vec3(1, 0, 0));
	forceRegistry->Add(Decor2, gravityDecor2);
	dynObjs.push_back(Decor2);

	Gravity* gravityDecor3 = new Gravity(vec2(0, -50));		
	PhysicsParameters* ParametersDecor3 = new PhysicsParameters(20, vec2(955, 1000), vec2(0, 0), 0.8f);						
	Balls* Decor3 = new Balls(20, ParametersDecor3, vec3(1, 0, 0));
	forceRegistry->Add(Decor3, gravityDecor3);
	dynObjs.push_back(Decor3);

	Gravity* gravityDecor4 = new Gravity(vec2(0, -100));		
	PhysicsParameters* ParametersDecor4 = new PhysicsParameters(20, vec2(955, 1000), vec2(0, 0), 0.8f);						
	Balls* Decor4 = new Balls(20, ParametersDecor4, vec3(1, 1, 0));
	forceRegistry->Add(Decor4, gravityDecor4);
	dynObjs.push_back(Decor4);

	Gravity* gravityDecor5 = new Gravity(vec2(0, -150));		
	PhysicsParameters* ParametersDecor5 = new PhysicsParameters(20, vec2(955, 1000), vec2(0, 0), 0.8f);						
	Balls* Decor5 = new Balls(20, ParametersDecor5, vec3(1, 0, 0));
	forceRegistry->Add(Decor5, gravityDecor5);
	dynObjs.push_back(Decor5);


	///TEST BALL FOR POCKETS
	Drag* DragYellowBall8 = new Drag(0.0f, 0.0f);
	PhysicsParameters* ParametersYellowBall8 = new PhysicsParameters(10, vec2(150, 20), vec2(0, 1), 0.8f);						
	Balls* Yellowball8 = new Balls(20, ParametersYellowBall8, vec3(1, 1, 0));	  //Yellow
	forceRegistry->Add(Yellowball8, DragYellowBall8);
	//EntityList.push_back(ball);
	dynObjs.push_back(Yellowball8);
}
/*
For if the cue can not be implemented:

Wanted to be able to reference ~CueBall, ParametersCueBall ~ from a function outside the Load function, but not sure how to reference them so I can give it a velocity everytime it stops.
Tried to reference like a variable, but did not work. 


*/

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW);

	/*list<Entity*>::iterator it;
	for (it = EntityList.begin(); it != EntityList.end(); ++it)
	{
		(*it)->Draw(Window->getSWidth(), Window->getSHeight());
	}*/

	for (vector<Entity*>::iterator it = gameobjects.begin(); it < gameobjects.end(); it++)
	{
		(*it)->Draw(Window->getSWidth(), Window->getSHeight());
		
	}

	for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
	{
		(*it)->Draw(Window->getSWidth(), Window->getSHeight());
	}

	glutSwapBuffers();
}

void Game::Inputs()
{
}

void Game::update(float dt)
{
	forceRegistry->updateForces(dt);
	solver->Integrate(dynObjs, dt);
	forceRegistry->Clear();

	for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
	{
		(*it)->update(dt);			//updates other quantities in each object
	}
	GetCollisionsData();

	while (!collisionData.empty())
	{
		unique_ptr<CollisionData>& data = collisionData.back();
		resolver->setNumIterations(data->maxNumContacts - data->numContactsLeft);
		if (data->contact != nullptr)
			resolver->resolveContacts(data->contact, data->maxNumContacts, dt);

		collisionData.pop_back();
	}
}

void Game::ReshapeWindow(int SWidth, int SHeight)
{
	Window->Reshape(SWidth, SHeight);
}

void Game::GetCollisionsData()
{
	for (vector<PhysicsEntity*>::iterator it_obj1 = dynObjs.begin(); it_obj1 < dynObjs.end() - 1; ++it_obj1)
	{
		for (vector<PhysicsEntity*>::iterator it_obj2 = it_obj1 + 1; it_obj2 < dynObjs.end(); ++it_obj2)
		{
			CollisionData * data = CollisionDetector::CheckCollision(*it_obj1, *it_obj2);
			if (data != nullptr)
				collisionData.push_back(unique_ptr<CollisionData>(data));
		}
	}
}





