#include <iostream>
#include <algorithm>
#include "simulation.h"
#include "vector2.cpp"
#include "math.h"
#include <omp.h>


simulation::simulation(simulationInitParams& initParams)
{
	srand(time(0));

	params = initParams;
	particles = vector<particle>(initParams.particlesCount);
	activeParticles = std::vector<particle*>(initParams.particlesCount);
	grid = new planeGrid(initParams.border, initParams.border.size / initParams.quadSize, initParams.quadSize.x * initParams.quadSize.y);

	float maxVelocity = 100;
	for (int i = 0; i < initParams.particlesCount; i++)
	{
		particles[i] = particle();
		particles[i].radius = initParams.particleRadius;
		particles[i].mass = 1;

		particles[i].coords.x = lerp(initParams.border.pos.x, initParams.border.pos.x + initParams.border.size.x, rand() / (float)RAND_MAX);
		particles[i].coords.y = lerp(initParams.border.pos.y, initParams.border.pos.y + initParams.border.size.y, rand() / (float)RAND_MAX);
		particles[i].velocity.x = lerp(-maxVelocity, maxVelocity, rand() / (float)RAND_MAX);
		particles[i].velocity.y = lerp(-maxVelocity, maxVelocity, rand() / (float)RAND_MAX);
		
		activeParticles[i] = &particles[i];
		grid->addParticle(&particles[i]);
	}
}

void simulation::simulateFrame(float deltaTime, float time)
{
	#pragma omp parallel for
	for (int i = 0; i < activeParticles.size(); i++)
	{
		particle* _particle = activeParticles[i];
		_particle->coordsOld = _particle->coords;
		_particle->velocityOld = _particle->velocity;

		vector<vector<particle*>*> cells = grid->getCellsByRadius(_particle->coordsOld, _particle->radius);
		for (auto cell : cells)
		{
			for (particle* other : *cell)
			{
				if (other == nullptr) continue;
				if ((other->coords - _particle->coords).sqrlen() > (_particle->radius + other->radius) * (_particle->radius + other->radius)) continue;

				if (_particle->mass == other->mass) 
					_particle->velocity = other->velocityOld;
				else 
					_particle->velocity = (2 * other->mass * other->velocityOld + _particle->velocity * (_particle->mass - other->mass)) / (_particle->mass + other->mass);
			}
		}

		_particle->coords += _particle->velocity * deltaTime;
		_particle->coords.x = clamp(_particle->coords.x, params.border.pos.x, params.border.pos.x + params.border.size.x);
		_particle->coords.y = clamp(_particle->coords.y, params.border.pos.y, params.border.pos.y + params.border.size.y);
	}

	#pragma omp parallel for
	for (int i = 0; i < activeParticles.size(); i++)
	{
		grid->updateParticleCell(activeParticles[i], activeParticles[i]->coordsOld);
	}
}