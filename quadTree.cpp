#pragma once
#include <unordered_set>
#include <vector>
#include "vector2.cpp"
#include "particle.h"
#include "aabb.cpp"

using namespace std;
class quadTree
{
	int maxParticlesCount;

public:
	quadTree** children; // 0 - left up; 1 - right up; 2 - left down; 3 - right down
	aabb boundingArea;

	vector<particle*> particles;


	quadTree(aabb& boundingArea, int maxParticlesCount, int maxDepth, int depthOfThis = 0)
	{
		this->boundingArea = boundingArea;
		this->maxParticlesCount = maxParticlesCount;

		if (depthOfThis == maxDepth) return;

		children = new quadTree*[4];
		for (int i = 0; i < 4; i++)
		{
			aabb childAabb = aabb(
				boundingArea.pos.x + ((i == 1 || i == 3) ? boundingArea.size.x/2 : 0),
				boundingArea.pos.y + ((i == 2 || i == 3) ? boundingArea.size.y/2 : 0),
				boundingArea.size.x / 2,
				boundingArea.size.y / 2);

			children[i] = new quadTree(childAabb, maxParticlesCount, maxDepth, depthOfThis + 1);
		}
	}

	quadTree* find(vector2 point)
	{
		if (boundingArea.contains(point) == false) return nullptr;
		if (/*particles.size() == 0 || */children == nullptr) return this;

		for (int i = 0; i < 4; i++)
		{
			quadTree* searchResult = children[i]->find(point);
			if (searchResult != nullptr) return searchResult;
		}
		return nullptr;
	}

	unordered_set<quadTree*> findByRadius(vector2 point, float radius)
	{
		//if (particle)
	}
};