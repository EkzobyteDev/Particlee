#pragma once
#include <vector>
#include "particle.h"

class simulation
{
public:
	std::vector<particle> particles; // A vector of all particles
	std::vector<particle*> activeParticles; // A vector of pointers to all active particles (particles that have to be processed)
	std::vector<particle*>* grid; // An array of quads that contains pointers to particles that are in this quad now

	void init(int particlesCount, int particleSize, int quadSize, int x0, int y0, int x1, int y1);
	void simulateFrame(float deltaTime, float time);
};