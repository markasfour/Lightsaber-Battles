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
#include "button.h"

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
	hiltRect.w = 14;
	hiltRect.h = 60;

	//blade rendering rectangle
	SDL_Rect bladeRect;
	bladeRect.w = 21;
	bladeRect.h = 1;
	
	//blade tip rendering rectangle
	SDL_Rect bladetipRect;
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
	
	//lightsaber selection panel
	bool visible = false;
	bool switched = false;
	SDL_Rect saberSelect;
	saberSelect.x = 0;
	saberSelect.y = SCREEN_HEIGHT;
	saberSelect.h = 60;
	saberSelect.w = 3 * (10 + 45) + 10;
	button LukeBG(0xFF, 0xFF, 0xFF, 0xFF, 10, SCREEN_HEIGHT, 45, 45);
	button AnakinBG(0xFF, 0xFF, 0xFF, 0xFF, 10 + 45 + 10, SCREEN_HEIGHT, 45, 45);	
	button VaderBG(0xFF, 0xFF, 0xFF, 0xFF, 10 + 45 + 10 + 45 + 10, SCREEN_HEIGHT, 45, 45);
	button LukeIC(LukeBG.rect.x + (LukeBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
	button AnakinIC(AnakinBG.rect.x + (AnakinBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
	button VaderIC(VaderBG.rect.x + (VaderBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
	
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

		//character switch boolean
		switched = false;

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
				
				if (visible && LukeBG.wasClicked(mouse_x, mouse_y))
					main_char = Luke, switched = true, on = false;
				else if (visible && AnakinBG.wasClicked(mouse_x, mouse_y))
					main_char = Anakin, switched = true, on = false;
				else if (visible && VaderBG.wasClicked(mouse_x, mouse_y))
					main_char = Vader, switched = true, on = false;
				else
					on = !on;
				if (on && !switched)
					Mix_PlayChannel(-1, main_char.ON_SOUND, 0);
				else if (!on && !switched)
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
		
		//handle key presses here

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
		bladeCenter = {bladeRect.w / 2, (bladeRect.h) + (hiltRect.h / 2)};
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
			if (bladeRect.h < 300 && !switched)
			{
				bladeRect.h += 10;
			}
			else
				bladeRect.h = 300;
		}
		//blade off
		if (!on)
		{	
			if (bladeRect.h > 0 && !switched) 
			{
				bladeRect.h -= 4;
			}
			else
				bladeRect.h = 0;
		}
		
		//hilt position
		hiltRect.x = mouse_x - (hiltRect.w / 2);
		hiltRect.y = mouse_y - (hiltRect.h / 2);
		
		//lightsaber select gui
		if (mouse_x < saberSelect.w && mouse_y > SCREEN_HEIGHT - 20)
		{
			visible = true;
		}
		if (visible)
		{
			if (saberSelect.y > SCREEN_HEIGHT - 60)
				saberSelect.y -= 10;
			if (LukeBG.rect.y > SCREEN_HEIGHT - 50)	
			{	
				LukeBG.rect.y -= 10;
				LukeBG.hover.y -= 10;
				LukeIC.rect.y -= 10;
			}
			if (AnakinBG.rect.y > SCREEN_HEIGHT - 50)	
			{	
				AnakinBG.rect.y -= 10;
				AnakinBG.hover.y -= 10;
				AnakinIC.rect.y -= 10;
			}
			if (VaderBG.rect.y > SCREEN_HEIGHT - 50)	
			{	
				VaderBG.rect.y -= 10;
				VaderBG.hover.y -= 10;
				VaderIC.rect.y -= 10;
			}
			if (mouse_x > saberSelect.w || mouse_y < SCREEN_HEIGHT - 60)
				visible = false;
		}
		if (!visible)
		{
			if (saberSelect.y < SCREEN_HEIGHT)
				saberSelect.y += 10;
			if (LukeBG.rect.y < SCREEN_HEIGHT)
			{
				LukeBG.rect.y += 10;
				LukeBG.hover.y += 10;
				LukeIC.rect.y += 10;
			}
			if (AnakinBG.rect.y < SCREEN_HEIGHT)	
			{
				AnakinBG.rect.y += 10;
				AnakinBG.hover.y += 10;
				AnakinIC.rect.y += 10;
			}
			if (VaderBG.rect.y < SCREEN_HEIGHT)	
			{	
				VaderBG.rect.y += 10;
				VaderBG.hover.y += 10;
				VaderIC.rect.y += 10;
			}
		}
		
		//render everything
		//blade
		if (on)
		{
			SDL_RenderCopyEx(RENDERER, main_char.blade.mTexture, NULL, &bladeRect, 
						 	 angle, &bladeCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, main_char.bladetip.mTexture, NULL, &bladetipRect, 
						 	 angle, &bladetipCenter, SDL_FLIP_NONE);
		}
		if (!on && bladeRect.h > 0)
		{
			SDL_RenderCopyEx(RENDERER, main_char.blade.mTexture, NULL, &bladeRect, 
						 	 angle, &bladeCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, main_char.bladetip.mTexture, NULL, &bladetipRect, 
						 	 angle, &bladetipCenter, SDL_FLIP_NONE);
		}
		//hilt
		SDL_RenderCopyEx(RENDERER, main_char.hilt.mTexture, NULL, &hiltRect,
						 angle, &hiltCenter, SDL_FLIP_NONE);
		//saber select
		SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0x0F);
		SDL_RenderFillRect(RENDERER, &saberSelect);
		//Luke button
		SDL_SetRenderDrawColor(RENDERER, LukeBG.r, LukeBG.g, LukeBG.b, LukeBG.a);
		if (visible && LukeBG.mouseHover(mouse_x, mouse_y))
		{
			SDL_RenderFillRect(RENDERER, &LukeBG.hover);
			LukeIC.mouseHover(mouse_x, mouse_y);
			SDL_RenderCopyEx(RENDERER, hilt_Luke.mTexture, NULL, &LukeIC.hover,
							 45, NULL, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderFillRect(RENDERER, &LukeBG.rect);
			SDL_RenderCopyEx(RENDERER, hilt_Luke.mTexture, NULL, &LukeIC.rect,
							 45, NULL, SDL_FLIP_NONE);
		}
		//Anakin button
		SDL_SetRenderDrawColor(RENDERER, AnakinBG.r, AnakinBG.g, AnakinBG.b, AnakinBG.a);
		if (visible && AnakinBG.mouseHover(mouse_x, mouse_y))
		{
			SDL_RenderFillRect(RENDERER, &AnakinBG.hover);
			AnakinIC.mouseHover(mouse_x, mouse_y);
			SDL_RenderCopyEx(RENDERER, hilt_Anakin.mTexture, NULL, &AnakinIC.hover,
							 45, NULL, SDL_FLIP_NONE);	
		}
		else
		{	
			SDL_RenderFillRect(RENDERER, &AnakinBG.rect);
			SDL_RenderCopyEx(RENDERER, hilt_Anakin.mTexture, NULL, &AnakinIC.rect,
							 45, NULL, SDL_FLIP_NONE);	
		}
		//Vader button
		SDL_SetRenderDrawColor(RENDERER, VaderBG.r, VaderBG.g, VaderBG.b, VaderBG.a);
		if (visible && VaderBG.mouseHover(mouse_x, mouse_y))
		{	
			SDL_RenderFillRect(RENDERER, &VaderBG.hover);
			VaderIC.mouseHover(mouse_x, mouse_y);
			SDL_RenderCopyEx(RENDERER, hilt_Vader.mTexture, NULL, &VaderIC.hover,
							 45, NULL, SDL_FLIP_NONE);	
		}
		else
		{	
			SDL_RenderFillRect(RENDERER, &VaderBG.rect);
			SDL_RenderCopyEx(RENDERER, hilt_Vader.mTexture, NULL, &VaderIC.rect,
							 45, NULL, SDL_FLIP_NONE);	
		}

		//display
		SDL_RenderPresent(RENDERER);
		
		//cap the frame rate
		if (fps.get_ticks() < 1000/FRAMES_PER_SECOND)
			SDL_Delay((1000/FRAMES_PER_SECOND) - fps.get_ticks());
	}

	close();
	return 0;
}
