#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <cmath>
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
#include "helper.h"
#include "character.h"

#define PI 3.14

using namespace std;

int main()
{
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

	//mouse click boolean
	bool click = false;

	//keyboard input handler
	Input input;

	//frame rate regulator
	Timer fps;

	//hilt rendering rectangle 
	SDL_Rect hiltRect;
	hiltRect.x = SCREEN_WIDTH / 2;
	hiltRect.y = 3 * SCREEN_HEIGHT / 4;
	hiltRect.w = 14;
	hiltRect.h = 60;

	//blade rendering rectangle
	SDL_Rect bladeRect;
	bladeRect.x = SCREEN_WIDTH / 2 - 4;
	bladeRect.y = 3 * SCREEN_HEIGHT / 4 - 3;
	bladeRect.w = 21;
	bladeRect.h = 1;
	
	//blade tip rendering rectangle
	SDL_Rect bladetipRect;
	bladetipRect.x = bladeRect.x;
	bladetipRect.y = bladeRect.y - 7;
	bladetipRect.w = 21;
	bladetipRect.h = 7;
	
	//lightsaber on/off
	bool on = false;
	
	//rotate blade
	double angle = 0;
	SDL_Point center;
	SDL_Point hiltCenter;
	SDL_Point bladeCenter;
	SDL_Point bladetipCenter;
	
	//init position
	bool start = true;
	
	//characters
	Character main_char("Luke");
	Character Luke("Luke");
	Character Anakin("Anakin");
	Character Vader("Vader");

	//Main loop
	while (!quit)
	{
		//start input handler
		input.beginNewFrame();
		
		//start the frame timer
		fps.start();
		
		//get mouse location
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
		if (start && mouse_x == 0 && mouse_y == 0)
		{
			mouse_x = SCREEN_WIDTH / 2;
			mouse_y = 3 * SCREEN_HEIGHT / 4;
		}
		if (start && mouse_x != SCREEN_WIDTH / 2 && mouse_y != SCREEN_HEIGHT / 4)
			start = false;

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
				on = !on;
				if (on)
					Mix_PlayChannel(-1, main_char.ON_SOUND, 0);
				if (!on)
					Mix_PlayChannel(-1, main_char.OFF_SOUND, 0);
			}
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.repeat == 0) 
					input.keyDownEvent(e);
			}
			else if (e.type == SDL_KEYUP) 
				input.keyUpEvent(e);
		}
		
		//handle key presses
		if (input.wasKeyPressed(SDL_SCANCODE_1))
			main_char = Luke;	
		else if (input.wasKeyPressed(SDL_SCANCODE_2))
			main_char = Anakin;
		else if (input.wasKeyPressed(SDL_SCANCODE_3))
			main_char = Vader;

		//handle music
		if (on)
			if (Mix_Playing(1) == 0)
				Mix_PlayChannel(1, main_char.HUM, 0);
		if (!on)
			Mix_HaltChannel(1);

		//clear screen
		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
		SDL_RenderClear(RENDERER);
		
		//get center points
		center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
		hiltCenter = {hiltRect.w / 2, hiltRect.h / 2};
		bladeCenter = {bladeRect.w / 2, bladeRect.h + (hiltRect.h / 2)};
		bladetipCenter = {bladetipRect.w / 2, bladetipRect.h + bladeRect.h + (hiltRect.h / 2)};

		//handle angle
		if (mouse_x - center.x != 0)
			angle = atan2((double(center.y - mouse_y)) , (double(center.x - mouse_x))) * (180.0/PI) - 90;
		else if (mouse_y < center.y)
			angle = 0;
		else
			angle = 180;
		angle *= 2;
		
		//handle blade position
		bladeRect.x = mouse_x - (bladeRect.w / 2);
		bladetipRect.x = bladeRect.x;
		bladeRect.y = mouse_y - (hiltRect.h / 2) - bladeRect.h;
		bladetipRect.y = bladeRect.y - bladetipRect.h;
		
		//blade on
		if (on)
		{
			if (bladeRect.h < 300)
			{
				bladeRect.y -= 10;
				bladeRect.h += 10;
				bladetipRect.y = bladeRect.y - 3;
			}
			
		}
		//blade off
		if (!on)
		{	
			if (bladeRect.h > 0) 
			{
				bladeRect.y += 4;
				bladeRect.h -= 4;
				bladetipRect.y = bladeRect.y - 3;
				SDL_RenderCopyEx(RENDERER, main_char.blade.mTexture, NULL, &bladeRect, 
							 	 angle, &bladeCenter, SDL_FLIP_NONE);
				SDL_RenderCopyEx(RENDERER, main_char.bladetip.mTexture, NULL, &bladetipRect, 
							 	 angle, &bladetipCenter, SDL_FLIP_NONE);
			}
		}

		//draw hilt
		hiltRect.x = mouse_x - (hiltRect.w / 2);
		hiltRect.y = mouse_y - (hiltRect.h / 2);
		
		//render everything
		if (on)
		{
			SDL_RenderCopyEx(RENDERER, main_char.blade.mTexture, NULL, &bladeRect, 
						 	 angle, &bladeCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, main_char.bladetip.mTexture, NULL, &bladetipRect, 
						 	 angle, &bladetipCenter, SDL_FLIP_NONE);
		}
		SDL_RenderCopyEx(RENDERER, main_char.hilt.mTexture, NULL, &hiltRect,
						 angle, &hiltCenter, SDL_FLIP_NONE);
		SDL_RenderPresent(RENDERER);
		
		//cap the frame rate
		if (fps.get_ticks() < 1000/FRAMES_PER_SECOND)
			SDL_Delay((1000/FRAMES_PER_SECOND) - fps.get_ticks());
	}

	close();
	return 0;
}
