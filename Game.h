#pragma once
#include <GL\glut.h>
#include "GameWindow.h"
#include <glm\glm.hpp>
#include "Table.h"
#include <vector>
#include "Pocket.h"
#include "Cushions.h"
#include "Grid.h"
#include "ForceRegistry.h"
#include "Solver.h"
#include <memory>
#include "ContactResolver.h"
#include "CollisionData.h"
#include "CollisionDetector.h"


using namespace std;

class Game
{
private:
	GameWindow *Window;
	int ScreenHeight = 1000;
	int ScreenWidth = 1000;
	vector<Entity*> gameobjects;
	
	Grid* grid;

	ForceRegistry* forceRegistry = nullptr;
	Solver* solver = nullptr;
	vector<PhysicsEntity*> dynObjs;
	vector<Entity*> pocketsObjs;
	vector<unique_ptr<CollisionData>> collisionData;
	ContactResolver* resolver = nullptr;
	void GetCollisionsData();

public:
	Game() {};
	virtual ~Game()
	{
		for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
			delete *it;

		if (solver != nullptr) delete solver;
		if (Window != nullptr) delete Window;
		if (forceRegistry != nullptr) delete forceRegistry;
	}

	void Load();
	void Render();
	void Inputs();
	void update(float dt);
	void ReshapeWindow(int SWidth, int SHeight);
	
};