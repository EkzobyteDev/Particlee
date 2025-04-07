#pragma once
#include <vector>
#include "vector2.cpp"
#include "particle.h"
#include "aabb.cpp"

using namespace std;
class planeGrid
{
private:
	aabb borders;
	vector2 subdivisionsCount;
	vector<vector<particle*>> grid; // Each cell contains a list of particles

public:
	planeGrid(aabb borders, vector2 subdivisionsCount);

	vector<particle*>* getCellThatOccuppiesPoint(vector2 point);
	vector<vector<particle*>*> getCellsByRadius(vector2 point, float radius);

	void addParticle(particle* _particle);
	void updateParticleCell(particle* _particle, vector2 particleOldPos);
};
