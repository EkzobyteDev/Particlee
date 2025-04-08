#include "planeGrid.h"
#include <algorithm>


planeGrid::planeGrid(aabb borders, vector2 subdivisionsCount, int maxParticlesInCell)
{
	this->borders = borders;
	this->subdivisionsCount = subdivisionsCount;

	vector<particle*> temp(maxParticlesInCell);
	grid.insert(grid.begin(), subdivisionsCount.x * subdivisionsCount.y, temp);
}

vector<particle*>* planeGrid::getCellThatOccuppiesPoint(vector2 point)
{
	if (borders.contains(point) == false) return nullptr;
	vector2 cellCoords;
	cellCoords.x = floor((point.x - borders.pos.x) / borders.size.x * subdivisionsCount.x);
	cellCoords.y = floor((point.y - borders.pos.y) / borders.size.y * subdivisionsCount.y);
	return &grid[cellCoords.y * subdivisionsCount.y + cellCoords.x];
}

vector<vector<particle*>*> planeGrid::getCellsByRadius(vector2 point, float radius)
{
	vector<vector<particle*>*> result;
	for (int shiftX = -1; shiftX < 2; shiftX++)
	{
		for (int shiftY = -1; shiftY < 2; shiftY++)
		{
			vector2 targetPoint(point.x + radius*shiftX, point.y + radius*shiftY);
			vector<particle*>* searchResult = getCellThatOccuppiesPoint(targetPoint);
			if (searchResult != nullptr) result.push_back(searchResult);
		}
	}
	return result;
}

void planeGrid::addParticle(particle* _particle)
{
	vector<particle*>* targetCell = getCellThatOccuppiesPoint(_particle->coords);
	if (targetCell != nullptr) targetCell->push_back(_particle);
}

void planeGrid::updateParticleCell(particle* _particle, vector2 particleOldPos)
{
	if (particleOldPos == _particle->coords) return;
	if (borders.contains(_particle->coords) == false) return;

	vector<particle*>* oldCell = getCellThatOccuppiesPoint(particleOldPos);
	vector<particle*>* targetCell = getCellThatOccuppiesPoint(_particle->coords);

	if (oldCell == nullptr) return;
	if (oldCell == targetCell) return;

	for (int i = 0; i < oldCell->size(); i++)
	{
		if ((*oldCell)[i] == _particle)
		{
			(*oldCell)[i] = nullptr;
			break;
		}
	}

	for (int i = 0; i < targetCell->size(); i++)
	{
		if ((*targetCell)[i] == nullptr)
		{
			(*targetCell)[i] = _particle;
			break;
		}
	}
}