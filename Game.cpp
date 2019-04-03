#include "Game.h"
#include <glm\glm.hpp>
#include <iostream>
#include <vector>
#include "VerletSolver.h"
#include "Gravity.h"
#include "Balls.h"
#include "Shadow.h"
#include "list"

using namespace std;
using namespace glm;	

void Game::Load()
{
	Window = new GameWindow(ScreenWidth, ScreenHeight, 500, 10);
	grid = new Grid(5, ScreenWidth, ScreenHeight);

	solver = new VerletSolver();
	forceRegistry = new ForceRegistry();
	resolver = new ContactResolver();


	Table *BackTable = new Table(vec2(400, 500), vec2(500, 500));
	gameobjects.push_back(BackTable);														//Push to render
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

	PhysicsParameters* ParametersTopRightCus = new PhysicsParameters(INFINITY, vec2(850, 725), vec2(0, 0), .0f);						//Top cushion - collider
	Gravity* gravityTRC = new Gravity(vec2(0, 0));
	Cushions *TopRightCus = new Cushions(vec2(8, 190), vec2(146, 500), ParametersTopRightCus, vec3(0.0f, 0.3f, 0.0f));
	dynObjs.push_back(TopRightCus);

	PhysicsParameters* ParametersBotRightCus = new PhysicsParameters(INFINITY, vec2(850, 275), vec2(0, 0), .0f);						//Top cushion - collider
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
	Balls* BotLeftPockColl = new Balls(15, ParametersPocketsBotLeft, vec3(1));
	dynObjs.push_back(BotLeftPockColl);

	PhysicsParameters* ParametersPocketsMidLeft = new PhysicsParameters(INFINITY, vec2(150, 500), vec2(0, 0), .0f);			//Mid Left pocket collision
	Balls* MidLeftPockColl = new Balls(15, ParametersPocketsMidLeft, vec3(1));
	dynObjs.push_back(MidLeftPockColl);

	PhysicsParameters* ParametersPocketsTopLeft = new PhysicsParameters(INFINITY, vec2(150, 950), vec2(0, 0), .0f);			//Top Left pocket collision
	Balls* TopLeftPockColl = new Balls(15, ParametersPocketsTopLeft, vec3(1));
	dynObjs.push_back(TopLeftPockColl);

	PhysicsParameters* ParametersPocketsTopRight = new PhysicsParameters(INFINITY, vec2(850, 950), vec2(0, 0), .0f);		//Top Right pocket collision
	Balls* TopRightPockColl = new Balls(15, ParametersPocketsTopRight, vec3(1));
	dynObjs.push_back(TopRightPockColl);

	PhysicsParameters* ParametersPocketsMidRight = new PhysicsParameters(INFINITY, vec2(850, 500), vec2(0, 0), .0f);		//Mid Right pocket collision
	Balls* MidRightPockColl = new Balls(15, ParametersPocketsMidRight, vec3(1));
	dynObjs.push_back(MidRightPockColl);

	PhysicsParameters* ParametersPocketsBotRight = new PhysicsParameters(INFINITY, vec2(850, 50), vec2(0, 0), .0f);			//Bottom Right pocket collision
	Balls* BotRightPockColl = new Balls(15, ParametersPocketsBotRight, vec3(1));
	dynObjs.push_back(BotRightPockColl);

	Gravity* gravityBalls = new Gravity(vec2(0, 0));		//Testing purposes
	PhysicsParameters* ParametersBalls = new PhysicsParameters(10, vec2(250, 800), vec2(100, 100), 0.8f);						//Mass, Pos, vel, restit
	Balls* ball = new Balls(20, ParametersBalls);
	forceRegistry->Add(ball, gravityBalls);
	//EntityList.push_back(ball);
	dynObjs.push_back(ball);

	Gravity* gravityBalls1 = new Gravity(vec2(0, 0));		//Testing purposes
	PhysicsParameters* ParametersBalls1 = new PhysicsParameters(10, vec2(250, 500), vec2(100, 100), 0.8f);						//Mass, Pos, vel, restit
	Balls* bal1l = new Balls(20, ParametersBalls1);
	forceRegistry->Add(bal1l, gravityBalls1);
	//EntityList.push_back(ball);
	dynObjs.push_back(bal1l);

	Gravity* gravityBalls2 = new Gravity(vec2(0, -200));		//Testing purposes
	PhysicsParameters* ParametersBalls2 = new PhysicsParameters(10, vec2(500, 600), vec2(100, 100), 0.8f);						//Mass, Pos, vel, restit
	Balls* ball2 = new Balls(20, ParametersBalls2);
	forceRegistry->Add(ball2, gravityBalls2);
	//EntityList.push_back(ball);
	dynObjs.push_back(ball2);
}

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





