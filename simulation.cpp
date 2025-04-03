#include <iostream>
#include "simulation.h"
#include "vector2.cpp"
#include "math.h"
#include <omp.h>

// x0 y0 - upper left corner
// x1 y1 - bottom right corner
void simulation::init(int particlesCount, int particleSize, int quadSize, int x0, int y0, int x1, int y1)
{
	srand(time(0));

	particles = std::vector<particle>(particlesCount);
	activeParticles = std::vector<particle*>(particlesCount);

	for (int i = 0; i < particlesCount; i++)
	{
		particles[i] = particle();
		activeParticles[i] = &particles[i];
		particles[i].coords = vector2(x0 + (rand()%(x1-x0)), y0 + (rand()%(y1-y0)));
	}
}

void simulation::simulateFrame(float deltaTime, float time)
{
	static std::vector<vector2>* startCoords = nullptr;
	if (startCoords == nullptr)
	{
		startCoords = new std::vector<vector2>();
		for (particle* particle : activeParticles)
		{
			startCoords->push_back(particle->coords);
		}
	}
	float r = 500;
	#pragma	omp parallel for
	for (int i = 0; i < activeParticles.size(); i++)
	{
		activeParticles[i]->coords = (*startCoords)[i] + vector2::one() * (r * sin(i+time/4));
	}
}