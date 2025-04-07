#include <iostream>
#include "simulation.h"
#include "vector2.cpp"
#include "math.h"
#include <omp.h>


simulation::simulation(simulationInitParams& initParams)
{
	srand(time(0));

	particles = vector<particle>(initParams.particlesCount);
	activeParticles = std::vector<particle*>(initParams.particlesCount);
	grid = new planeGrid(initParams.border, initParams.border.size / initParams.quadSize);

	for (int i = 0; i < initParams.particlesCount; i++)
	{
		particles[i] = particle();
		particles[i].coords.x = lerp(initParams.border.pos.x, initParams.border.pos.x + initParams.border.size.x, rand() / (float)RAND_MAX);
		particles[i].coords.y = lerp(initParams.border.pos.y, initParams.border.pos.y + initParams.border.size.y, rand() / (float)RAND_MAX);
		
		activeParticles[i] = &particles[i];
		grid->addParticle(&particles[i]);
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
	//#pragma	omp parallel for
	for (int i = 0; i < activeParticles.size(); i++)
	{
		vector2 oldCoords = activeParticles[i]->coords;
		activeParticles[i]->coords = (*startCoords)[i] + vector2::one() * (r * sin(i+time/4));

		grid->updateParticleCell(activeParticles[i], oldCoords);
	}
}