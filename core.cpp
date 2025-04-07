#include <iostream>
#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_syswm.h>
#include <Windows.h>
#include "vector2.cpp"
#include <iomanip>
#include <unordered_set>
#include <omp.h>
#include "simulation.h"
#include <chrono>

const int SCREEN_WIDTH  = 1920;
const int SCREEN_HEIGHT = 1080;

using namespace std;
void draw(SDL_Renderer* renderer, simulation& sim, SDL_Point* points)
{
	auto t = chrono::high_resolution_clock::now();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	#pragma omp parallel for
	for (int i = 0; i < sim.activeParticles.size(); i++)
	{
		points[i].x = sim.activeParticles[i]->coords.x;
		points[i].y = sim.activeParticles[i]->coords.y;
	}

	cout << "    Set pixels: " << std::setw(4) << chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t).count();
	t = chrono::high_resolution_clock::now();
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoints(renderer, points, sim.activeParticles.size());
	cout << "    Upload pixels: " << std::setw(4) << chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t).count();
}

int main(int argc, char** args)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return 1;

	SDL_Window*  window  = SDL_CreateWindow("Particlee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) return 1;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) return 1;

	bool run = true;
	SDL_Event e;

	srand(time(0));
	int cellPixelSize = 1;

	aabb ab(0, 0, 1920, 1920);

	omp_set_num_threads(8);
	
	simulationInitParams simInitParams;
	simInitParams.particlesCount = 100;
	simInitParams.particleSize = 1;
	simInitParams.border.pos = vector2::zero();
	simInitParams.border.size = vector2(SCREEN_WIDTH, SCREEN_HEIGHT);
	simInitParams.quadSize = vector2(8, 8);

	simulation sim(simInitParams);
	SDL_Point* points = new SDL_Point[sim.activeParticles.size()];	
	float deltaTime = 0.01;
	while (run)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				run = false;
			}
		}

		auto t = chrono::high_resolution_clock::now();
		sim.simulateFrame(deltaTime, SDL_GetTicks64()/1000.0);
		cout << "Sim time: " << setw(4) << chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t).count();

		draw(renderer, sim, points);
		
		auto t1 = chrono::high_resolution_clock::now();
		SDL_RenderPresent(renderer);
		cout << "   Rendering: " << setw(4) << chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t1).count();
		
		deltaTime = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t).count();
		cout << "   Total time: " << setw(4) << deltaTime;
		cout << "   FPS: " << std::setprecision(5) << 1'000'000/deltaTime << '\n';
	}

	delete[] points;
	SDL_DestroyWindow(window);
	SDL_Quit();
}