#pragma once
#include <glm\glm.hpp>
#include <GL/glut.h>
#include <vector>
#include "Object.h"
#include <map>

using namespace std;
using namespace glm;

typedef pair<int, int> Indices;
class Grid
{
private:
	int CellSize;
	int CellWidth;
	int CellHeight;
	int Cols;
	int Rows;

	map<Indices, vector<Object*>> ObjectBucks;
	Indices computerCellIndices(vec2 position);

public:
	Grid(int cellSize, int cellWidth, int cellHeight);
	virtual ~Grid();
	vector<Object*>ReturnNeighbours(Object *obj);
	void AddObject(Object *obj);
	void ClearGrid();


};