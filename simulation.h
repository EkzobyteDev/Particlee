#pragma once
#include <vector>
#include "particle.h"
#include "planeGrid.h"

class simulationInitParams
{
public:
	int particlesCount;
	float particleRadius;
	vector2 quadSize;
	aabb border;
};

using namespace std;
class simulation
{
public:

	simulationInitParams params;
	vector<particle> particles; // A vector of all particles
	vector<particle*> activeParticles; // A vector of pointers to all active particles (particles that have to be processed)
	planeGrid* grid;

	simulation(simulationInitParams& initParams);

	void simulateFrame(float deltaTime, float time);
};