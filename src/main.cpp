#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif
#include "input.h"
#include "timer.h"
#include "texture.h"
#include "SDLhelper.h"
#include "lightsaber.h"
#include "character.h"
#include "button.h"
#include "panel.h"
#include "Menu.h"
#include "Simulator.h"
#include "Customize.h"
#include "Battle.h"

using namespace std;

int main(int argc, char **argv[])
{
	if (argc > 1)
	{
		DEBUG = true;
		cout << "Debug mode" << endl;
	}
	
	if (!init())
		return -1;

	char CurrentPath[FILENAME_MAX];
	if (!GetCurrentDir(CurrentPath, sizeof(CurrentPath)))
     	 return -1;
	CurrentPath[sizeof(CurrentPath) - 1] = '\0';

	if (!loadMedia(CurrentPath))
		return -1;
	
	//main loop flag
	bool quit = false;

	//event handler
	SDL_Event e;

	//mouse location
	int mouse_x = 0; 
	int mouse_y = 0;

	//keyboard input handler
	Input input;

	//frame rate regulator
	Timer fps;
	
	//mouse timer
	Timer mouse_timer;
	bool mouse_held = false;
	bool mouse_tap = false;
	bool mouse_down = false;
	double release_time = -1;
	double total_time = -1;

	//custom character
	Character custom;
	//custom background
	int bg = 0;

	Menu main_menu;
	Simulator simulator;
	Customize customize;
	Battle battle;

	//Main loop
	while (!quit)
	{
		//start input handler
		input.beginNewFrame();
		
		//start the frame timer
		fps.start();
		
		//get mouse location
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
		//Handle events in the queue
		while (SDL_PollEvent(&e) != 0)
		{
			//user quits
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				mouse_timer.start();
				mouse_down = true;
				release_time = 0;
			}
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				mouse_timer.stop();	
				mouse_down = false;
				
			}
		}
	
		//handle mouse tap / hold
		if (mouse_down)
			release_time = mouse_timer.get_ticks();
		else if (!mouse_down)
		{
			if (release_time > -1)
				total_time = release_time;
			release_time = -1;		
		}
				
		if (total_time <= 75 && total_time > -1)
		{
			mouse_held = false;
			mouse_tap = true;
		}
		else if (mouse_down && mouse_timer.get_ticks() > 75)
		{
			mouse_held = true;
			mouse_tap = false;
		}
		else
		{
			mouse_tap = false;
			mouse_held = false;
		}

		//handle mouse input
		if (mouse_tap)
		{
			if (GAMES.at(0))
				simulator.handleMouseDown(mouse_x, mouse_y, custom);
			else if (GAMES.at(1))
				customize.handleMouseDown(mouse_x, mouse_y, custom, bg);
			else if (GAMES.at(2))
				battle.handleMouseDown(mouse_x, mouse_y);
			else
				main_menu.handleMouseDown(mouse_x, mouse_y);
		}
		total_time = -1;
	
		//handle game mechanics
		if (GAMES.at(0))
			simulator.handleGame(mouse_x, mouse_y);	
		else if (GAMES.at(1))
			customize.handleGame(mouse_x, mouse_y);
		else if (GAMES.at(2))
			battle.handleGame(mouse_x, mouse_y, custom);
		else
			main_menu.handleBackgroundMovement(mouse_x, mouse_y);

		//handle rendering
		if (GAMES.at(0))
			simulator.renderEverything(RENDERER, mouse_x, mouse_y, custom);	
		else if (GAMES.at(1))
			customize.renderEverything(RENDERER, mouse_x, mouse_y, bg);
		else if (GAMES.at(2))
			battle.renderEverything(RENDERER, mouse_x, mouse_y, custom);
		else
			main_menu.renderEverything(RENDERER, mouse_x, mouse_y);

		//cap the frame rate
		if (fps.get_ticks() < 1000/FRAMES_PER_SECOND)
			SDL_Delay((1000/FRAMES_PER_SECOND) - fps.get_ticks());
	}
	main_menu.close();	
	simulator.close();
	customize.close();
	close();
	return 0;
}
