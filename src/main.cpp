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
#include "helper.h"
#include "character.h"
#include "button.h"
#include "panel.h"

#define PI 3.14159265 

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
	
	//background rendering rectangle
	SDL_Rect backgroundRect;
	backgroundRect.w = SCREEN_WIDTH * 1.05;
	backgroundRect.h = SCREEN_HEIGHT * 1.05;
	backgroundRect.x = (SCREEN_WIDTH - backgroundRect.w) / 2;
	backgroundRect.y = SCREEN_HEIGHT - backgroundRect.h;

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
	double prev_angle = 0;
	bool swing;
	int swing_choice = 0;
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
	panel saberSelect (0, SCREEN_HEIGHT, 3, 45, 10);
	bool switched = false;
	vector <button> saberButtons;
	vector <button> saberIcons;
	
	button LukeBG(0x00, 0x00, 0x00, 0xFF, 10, SCREEN_HEIGHT, 45, 45);
	saberButtons.push_back(LukeBG);
	button AnakinBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);	
	saberButtons.push_back(AnakinBG);
	button VaderBG(0x00, 0x00, 0x00, 0xFF, AnakinBG.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);
	saberButtons.push_back(VaderBG);
	
	button LukeIC(LukeBG.rect.x + (LukeBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
	saberIcons.push_back(LukeIC);
	button AnakinIC(AnakinBG.rect.x + (AnakinBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
	saberIcons.push_back(AnakinIC);
	button VaderIC(VaderBG.rect.x + (VaderBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
	saberIcons.push_back(VaderIC);

	//background selection panel
	int background = 0;
	panel bgSelect (465, SCREEN_HEIGHT, 3, 45, 10);
	vector <button> bgButtons;
	button CarbonFreezing(bgSelect.rect.x + 10, SCREEN_HEIGHT, 45, 45);
	bgButtons.push_back(CarbonFreezing);
	button EmperorsThrone(CarbonFreezing.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);
	bgButtons.push_back(EmperorsThrone);
	button HothEchoBase(EmperorsThrone.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);
	bgButtons.push_back(HothEchoBase);

	//mute
	bool mute = false;
	bool soundOn = false;
	bool soundOff = false;
	button muteIC(SCREEN_WIDTH - 25, 5, 20, 20);

	//Main loop
	while (!quit)
	{
		//hide cursor
		if (saberSelect.visible || bgSelect.visible)
			SDL_ShowCursor(1);
		else
			SDL_ShowCursor(0);
		
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
				//saber select panel clicks
				if (saberSelect.visible)
				{
					for (int i = 0; i < saberButtons.size(); i++)
					{
						if (saberButtons.at(i).wasClicked(mouse_x, mouse_y))
						{
							if (i == 0)
								main_char = Luke;
							else if (i == 1)
								main_char = Anakin;
							else
								main_char = Vader;
							switched = true, on = false, soundOn = false;
						}
					}
				}
				//background select panel clicks
				else if (bgSelect.visible)
				{
					for (int i = 0; i < bgButtons.size(); i++)
					{
						if (bgButtons.at(i).wasClicked(mouse_x, mouse_y))
							background = i;
					}
				}
				//mute button click
				else if (muteIC.wasClicked(mouse_x, mouse_y))
				{	
					mute = !mute;
					Mix_HaltChannel(2);	
				}
				else
					on = !on;
				
				if (on && !switched && !soundOn)
				{
					if (!mute)
						Mix_PlayChannel(2, main_char.ON_SOUND, 0);
					soundOn = true;
					soundOff = false;
				}
				else if (!on && !switched && !soundOff && !saberSelect.visible && !bgSelect.visible)
				{	
					if (!mute)
						Mix_PlayChannel(2, main_char.OFF_SOUND, 0);
					soundOff = true;
					soundOn = false;
				}
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

		//handle hum sound 
		if (on && !mute)
		{
			Mix_Volume(1, MIX_MAX_VOLUME/2);	//play at half volume
			if (Mix_Playing(1) == 0)
				Mix_PlayChannel(1, main_char.HUM, 0);
		}
		if (!on || mute)
			Mix_HaltChannel(1);
		
		//get center points
		center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
		hiltCenter = {hiltRect.w / 2, hiltRect.h / 2};
		bladeCenter = {bladeRect.w / 2, (bladeRect.h) + (hiltRect.h / 2)};
		bladetipCenter = {bladetipRect.w / 2, bladetipRect.h + bladeRect.h + (hiltRect.h / 2)};

		//move background
		backgroundRect.x = (-1 * (((center.x - mouse_x) / double(center.x)) * ((SCREEN_WIDTH - backgroundRect.w))/2)) - ((backgroundRect.w - SCREEN_WIDTH)/2);
		backgroundRect.y = (((center.y - mouse_y) / double(center.y)) * (SCREEN_HEIGHT - backgroundRect.h)/2);

		//handle angle
		prev_angle = angle;
		if (mouse_x - center.x != 0)
			angle = atan2((double(center.y - mouse_y)) , (double(center.x - mouse_x))) * (180.0/PI) - 90;
		else if (mouse_y < center.y)
			angle = 0;
		else
			angle = 180;
		angle *= 2;
		
		//handle swing
		swing = false;
		if (abs(prev_angle - angle) > 15)
			swing = true;
		else
			swing = false;
		if (swing && on && !mute)
		{
			if (Mix_Playing(3) == 0)
			{	
				Mix_Volume(3, MIX_MAX_VOLUME/3);	//play at third of volume
				if (abs(prev_angle - angle) <= 25)
					Mix_PlayChannel(3, SWING_SOUND_2, 0);
			}
			if (Mix_Playing(4) == 0)
			{
				Mix_Volume(4, MIX_MAX_VOLUME/3);	//play at third of volume
				if (abs(prev_angle - angle) > 25)
					Mix_PlayChannel(4, SWING_SOUND_1, 0);
			}
		}
		else if (mute)
		{
			Mix_HaltChannel(3);
			Mix_HaltChannel(4);
		}

		//handle blade position
		bladeRect.x = mouse_x - (bladeRect.w / 2);
		bladeRect.y = mouse_y - (hiltRect.h / 2) - bladeRect.h; 

		//blade on
		if (on)
		{
			if (bladeRect.h < 300 && !switched)
			{
				bladeRect.h += 10;
				bladeRect.y -= (10 * sin((angle + 90) * (PI/180)));
				bladeRect.x -= (10 * cos((angle + 90) * (PI/180)));
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
				bladeRect.y += (4 * sin((angle + 90) * (PI/180)));
				bladeRect.x += (4 * cos((angle + 90) * (PI/180)));
			}
			else
				bladeRect.h = 0;
		}

		//handle blade tip position
		bladetipRect.x = bladeRect.x;
		bladetipRect.y = bladeRect.y - bladetipRect.h;
		
		//hilt position
		hiltRect.x = mouse_x - (hiltRect.w / 2);
		hiltRect.y = mouse_y - (hiltRect.h / 2);
		
		//lightsaber select gui
		if (mouse_x < saberSelect.rect.w && mouse_y > SCREEN_HEIGHT - 20)
			saberSelect.visible = true;
		if (saberSelect.visible)
		{
			if (saberSelect.rect.y > SCREEN_HEIGHT - 60)
				saberSelect.rect.y -= 10;
			for (int i = 0; i < saberButtons.size(); i++)
			{
				if (saberButtons.at(i).rect.y > SCREEN_HEIGHT - 50)
				{
					saberButtons.at(i).rect.y -= 10;
					saberIcons.at(i).rect.y -= 10;
				}
			}
			if (mouse_x > saberSelect.rect.w || mouse_y < SCREEN_HEIGHT - 60)
				saberSelect.visible = false;
		}
		if (!saberSelect.visible)
		{
			if (saberSelect.rect.y < SCREEN_HEIGHT)
				saberSelect.rect.y += 10;
			for (int i = 0; i < saberButtons.size(); i++)
			{
				if (saberButtons.at(i).rect.y < SCREEN_HEIGHT)
				{
					saberButtons.at(i).rect.y += 10;
					saberIcons.at(i).rect.y += 10;
				}
			}
		}

		//background select gui
		if (mouse_x > bgSelect.rect.x && mouse_y > SCREEN_HEIGHT - 20)
			bgSelect.visible = true;
		if (bgSelect.visible)
		{
			if (bgSelect.rect.y > SCREEN_HEIGHT - 60)
				bgSelect.rect.y -= 10;
			for (int i = 0; i < bgButtons.size(); i++)
			{
				if (bgButtons.at(i).rect.y > SCREEN_HEIGHT - 50)
					bgButtons.at(i).rect.y -= 10;
			}
			if (mouse_x < bgSelect.rect.x || mouse_y < SCREEN_HEIGHT - 60)
				bgSelect.visible = false;
		}
		if (!bgSelect.visible)
		{
			if (bgSelect.rect.y < SCREEN_HEIGHT)
				bgSelect.rect.y += 10;
			for (int i = 0; i < bgButtons.size(); i++)
			{
				if (bgButtons.at(i).rect.y < SCREEN_HEIGHT)
					bgButtons.at(i).rect.y += 10;
			}
		}
		
		//render everything
		//clear screen
		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
		SDL_RenderClear(RENDERER);
		
		//background
		SDL_RenderCopy(RENDERER, backgrounds.at(background).mTexture, NULL, &backgroundRect);
		
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
		SDL_RenderFillRect(RENDERER, &saberSelect.rect);
		//buttons
		for (int i = 0; i < saberButtons.size(); i++)
		{
			SDL_SetRenderDrawColor(RENDERER, saberButtons.at(i).r, saberButtons.at(i).g, saberButtons.at(i).b, saberButtons.at(i).a);
			if (saberSelect.visible && saberButtons.at(i).mouseHover(mouse_x, mouse_y, true))
			{
				SDL_RenderFillRect(RENDERER, &saberButtons.at(i).hover);
				saberIcons.at(i).mouseHover(mouse_x, mouse_y, false);
				SDL_RenderCopyEx(RENDERER, hilts.at(i).mTexture, NULL, &saberIcons.at(i).hover,
							 	 45, NULL, SDL_FLIP_NONE);	
			}
			else if (saberSelect.visible && !saberButtons.at(i).mouseHover(mouse_x, mouse_y, true))
			{
				SDL_RenderFillRect(RENDERER, &saberButtons.at(i).rect);
				saberIcons.at(i).mouseHover(mouse_x, mouse_y, false);
				SDL_RenderCopyEx(RENDERER, hilts.at(i).mTexture, NULL, &saberIcons.at(i).rect,
							 	 45, NULL, SDL_FLIP_NONE);
			}
		}
		
		//background select
		SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0x0F);
		SDL_RenderFillRect(RENDERER, &bgSelect.rect);
		//buttons
		for (int i = 0; i < bgButtons.size(); i++)
		{
			if (bgSelect.visible && bgButtons.at(i).mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, backgrounds.at(i).mTexture, NULL, &bgButtons.at(i).hover);
			else if (bgSelect.visible && !bgButtons.at(i).mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, backgrounds.at(i).mTexture, NULL, &bgButtons.at(i).rect);
		}
		
		//mute button
		if (mute)
		{
			if (muteIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopyEx(RENDERER, muteOn.mTexture, NULL, &muteIC.hover,
								 0, NULL, SDL_FLIP_NONE);	
			else if (!muteIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopyEx(RENDERER, muteOn.mTexture, NULL, &muteIC.rect,
								 0, NULL, SDL_FLIP_NONE);
		}
		else if (!mute)
		{
			if (muteIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopyEx(RENDERER, muteOff.mTexture, NULL, &muteIC.hover,
								 0, NULL, SDL_FLIP_NONE);
			else if (!muteIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopyEx(RENDERER, muteOff.mTexture, NULL, &muteIC.rect,
								 0, NULL, SDL_FLIP_NONE);
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
