#include <SDL.h>
#include <iostream>
#include "FG_Input.h"

#define REFRESH_RATE 1.0/60.0

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Unable to initialise SDL \n";
		return -1;
	}
	//SDLInput::start();
	std::vector<FG_Action> actions
	({ 
		FG_Action("IK", STATE_STAND, std::vector<FG_Command>({CMD_FORWARD, CMD_DOWN, CMD_BACK, CMD_FORWARD, CMD_ABILITY})),
		FG_Action("X1", STATE_JUMP, std::vector<FG_Command>({CMD_FORWARD, CMD_DOWN, CMD_BACK, CMD_ABILITY})),
		FG_Action("X2", STATE_STAND, std::vector<FG_Command>({CMD_FORWARD, CMD_DOWN, CMD_BACK, CMD_ABILITY}))
	});
	FG_Inputs test;
	test.DefaultInit();
	test.AddAction("6A", STATE_STAND, std::vector<FG_Command>({ CMD_FORWARD, CMD_ABILITY }));
	test.AddActions(actions);
	std::cout << test.GetActionString();
	bool go = true;
	float lastTime = SDL_GetTicks();
	while (go)
	{
		float currentTime = SDL_GetTicks();
		float deltaTime = currentTime - lastTime;
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_KEYDOWN:
				switch (ev.key.keysym.sym)
				{
				case LEFT: case RIGHT: case UP: case DOWN: case LIGHT: case MEDIUM: case HEAVY: case ABILITY:
					SDLInput::SetKey(ev.key.keysym.sym, true);
					break;
				}
				break;
			case SDL_KEYUP:
				switch (ev.key.keysym.sym)
				{
				case LEFT: case RIGHT: case UP: case DOWN: case LIGHT: case MEDIUM: case HEAVY: case ABILITY:
					SDLInput::SetKey(ev.key.keysym.sym, false);
					break;
				}
				break;
			}
			test.ProcessInput(deltaTime);
			lastTime = currentTime;
		}
	}
	
	system("PAUSE");
	SDL_Quit();
	return 0;
}