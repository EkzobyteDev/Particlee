#include <iostream>
#include <algorithm>
#include "simulation.h"
#include "vector2.cpp"
#include "math.h"
#include <omp.h>


simulation::simulation(simulationInitParams& initParams)
{
	srand(time(0));

	particles = vector<particle>(initParams.particlesCount);
	activeParticles = std::vector<particle*>(initParams.particlesCount);
	grid = new planeGrid(initParams.border, initParams.border.size / initParams.quadSize, initParams.quadSize.x * initParams.quadSize.y);

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
	float l = 1000;
	#pragma	omp parallel for
	for (int i = 0; i < activeParticles.size(); i++)
	{
		activeParticles[i]->coordsOld = activeParticles[i]->coords;
		activeParticles[i]->velocityOld = activeParticles[i]->velocity;

		// Velocity computing
		activeParticles[i]->velocity += vector2(lerp(-1.0f, 1.0f, rand() / (float)RAND_MAX), lerp(-1.0f, 1.0f, rand() / (float)RAND_MAX)) * l * deltaTime;

		activeParticles[i]->coords += activeParticles[i]->velocity * deltaTime;
	}

	#pragma omp parallel for
	for (int i = 0; i < activeParticles.size(); i++)
	{
		grid->updateParticleCell(activeParticles[i], activeParticles[i]->coordsOld);
	}
}