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
	button LukeBG(0x00, 0x00, 0x00, 0xFF, 10, SCREEN_HEIGHT, 45, 45);
	button AnakinBG(0x00, 0x00, 0x00, 0xfF, 10 + 45 + 10, SCREEN_HEIGHT, 45, 45);	
	button VaderBG(0x00, 0x00, 0x00, 0xFF, 10 + 45 + 10 + 45 + 10, SCREEN_HEIGHT, 45, 45);
	button LukeIC(LukeBG.rect.x + (LukeBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
	button AnakinIC(AnakinBG.rect.x + (AnakinBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
	button VaderIC(VaderBG.rect.x + (VaderBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
	
	//background selection panel
	int background = 1;
	panel bgSelect (465, SCREEN_HEIGHT, 3, 45, 10);
	button CarbonFreezing(bgSelect.rect.x + 10, SCREEN_HEIGHT, 45, 45);
	button EmperorsThrone(CarbonFreezing.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);
	button HothEchoBase(EmperorsThrone.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);

	//mute
	bool mute = false;
	bool soundOn = false;
	bool soundOff = false;
	button muteIC(SCREEN_WIDTH - 25, 5, 20, 20);

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
				//saber select panel clicks
				if (saberSelect.visible && LukeBG.wasClicked(mouse_x, mouse_y))
					main_char = Luke, switched = true, on = false, soundOn = false;
				else if (saberSelect.visible && AnakinBG.wasClicked(mouse_x, mouse_y))
					main_char = Anakin, switched = true, on = false, soundOn = false;
				else if (saberSelect.visible && VaderBG.wasClicked(mouse_x, mouse_y))
					main_char = Vader, switched = true, on = false, soundOn = false;
				//background select panel clicks
				else if (bgSelect.visible && CarbonFreezing.wasClicked(mouse_x, mouse_y))
					background = 1;
				else if (bgSelect.visible && EmperorsThrone.wasClicked(mouse_x, mouse_y))
					background = 2;
				else if (bgSelect.visible && HothEchoBase.wasClicked(mouse_x, mouse_y))
					background = 3;
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
				else if (!on && !switched && !soundOff)
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

		//handle music
		if (on && !mute)
			if (Mix_Playing(1) == 0)
				Mix_PlayChannel(1, main_char.HUM, 0);
		if (!on || mute)
			Mix_HaltChannel(1);

		//clear screen
		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
		SDL_RenderClear(RENDERER);
		
		//get center points
		center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
		hiltCenter = {hiltRect.w / 2, hiltRect.h / 2};
		bladeCenter = {bladeRect.w / 2, (bladeRect.h) + (hiltRect.h / 2)};
		bladetipCenter = {bladetipRect.w / 2, bladetipRect.h + bladeRect.h + (hiltRect.h / 2)};

		//move background
		backgroundRect.x = (-1 * (((center.x - mouse_x) / double(center.x)) * ((SCREEN_WIDTH - backgroundRect.w))/2)) - ((backgroundRect.w - SCREEN_WIDTH)/2);
		backgroundRect.y = (((center.y - mouse_y) / double(center.y)) * (SCREEN_HEIGHT - backgroundRect.h)/2);

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
			if (LukeBG.rect.y > SCREEN_HEIGHT - 50)	
			{	
				LukeBG.rect.y -= 10;
				LukeIC.rect.y -= 10;
			}
			if (AnakinBG.rect.y > SCREEN_HEIGHT - 50)	
			{	
				AnakinBG.rect.y -= 10;
				AnakinIC.rect.y -= 10;
			}
			if (VaderBG.rect.y > SCREEN_HEIGHT - 50)	
			{	
				VaderBG.rect.y -= 10;
				VaderIC.rect.y -= 10;
			}
			if (mouse_x > saberSelect.rect.w || mouse_y < SCREEN_HEIGHT - 60)
				saberSelect.visible = false;
		}
		if (!saberSelect.visible)
		{
			if (saberSelect.rect.y < SCREEN_HEIGHT)
				saberSelect.rect.y += 10;
			if (LukeBG.rect.y < SCREEN_HEIGHT)
			{
				LukeBG.rect.y += 10;
				LukeIC.rect.y += 10;
			}
			if (AnakinBG.rect.y < SCREEN_HEIGHT)	
			{
				AnakinBG.rect.y += 10;
				AnakinIC.rect.y += 10;
			}
			if (VaderBG.rect.y < SCREEN_HEIGHT)	
			{	
				VaderBG.rect.y += 10;
				VaderIC.rect.y += 10;
			}
		}

		//background select gui
		if (mouse_x > bgSelect.rect.x && mouse_y > SCREEN_HEIGHT - 20)
			bgSelect.visible = true;
		if (bgSelect.visible)
		{
			if (bgSelect.rect.y > SCREEN_HEIGHT - 60)
				bgSelect.rect.y -= 10;
			if (CarbonFreezing.rect.y > SCREEN_HEIGHT - 50)
			{
				CarbonFreezing.rect.y -= 10;
			}
			if (EmperorsThrone.rect.y > SCREEN_HEIGHT - 50)
			{
				EmperorsThrone.rect.y -= 10;
			}
			if (HothEchoBase.rect.y > SCREEN_HEIGHT - 50)
			{
				HothEchoBase.rect.y -= 10;
			}
			if (mouse_x < bgSelect.rect.x || mouse_y < SCREEN_HEIGHT - 60)
				bgSelect.visible = false;
		}
		if (!bgSelect.visible)
		{
			if (bgSelect.rect.y < SCREEN_HEIGHT)
				bgSelect.rect.y += 10;
			if (CarbonFreezing.rect.y < SCREEN_HEIGHT)
			{
				CarbonFreezing.rect.y += 10;
			}
			if (EmperorsThrone.rect.y < SCREEN_HEIGHT)
			{
				EmperorsThrone.rect.y += 10;
			}
			if (HothEchoBase.rect.y < SCREEN_HEIGHT)
			{
				HothEchoBase.rect.y += 10;
			}
		}

		//render everything
		//background
		if (background == 1)
			SDL_RenderCopy(RENDERER, background1.mTexture, NULL, &backgroundRect);
		else if (background == 2)	
			SDL_RenderCopy(RENDERER, background2.mTexture, NULL, &backgroundRect);
		else if (background == 3)
			SDL_RenderCopy(RENDERER, background3.mTexture, NULL, &backgroundRect);

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
		
		//glow
		//if (on)
		//	SDL_RenderCopy(RENDERER, glow_R.mTexture, NULL, &backgroundRect);
		
		//saber select
		SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0x0F);
		SDL_RenderFillRect(RENDERER, &saberSelect.rect);
		//Luke button
		SDL_SetRenderDrawColor(RENDERER, LukeBG.r, LukeBG.g, LukeBG.b, LukeBG.a);
		if (saberSelect.visible && LukeBG.mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &LukeBG.hover);
			LukeIC.mouseHover(mouse_x, mouse_y, false);
			SDL_RenderCopyEx(RENDERER, hilt_Luke.mTexture, NULL, &LukeIC.hover,
							 45, NULL, SDL_FLIP_NONE);
		}
		else if (saberSelect.visible && !LukeBG.mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &LukeBG.rect);
			SDL_RenderCopyEx(RENDERER, hilt_Luke.mTexture, NULL, &LukeIC.rect,
							 45, NULL, SDL_FLIP_NONE);
		}
		//Anakin button
		SDL_SetRenderDrawColor(RENDERER, AnakinBG.r, AnakinBG.g, AnakinBG.b, AnakinBG.a);
		if (saberSelect.visible && AnakinBG.mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &AnakinBG.hover);
			AnakinIC.mouseHover(mouse_x, mouse_y, false);
			SDL_RenderCopyEx(RENDERER, hilt_Anakin.mTexture, NULL, &AnakinIC.hover,
							 45, NULL, SDL_FLIP_NONE);	
		}
		else if (saberSelect.visible && !AnakinBG.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderFillRect(RENDERER, &AnakinBG.rect);
			SDL_RenderCopyEx(RENDERER, hilt_Anakin.mTexture, NULL, &AnakinIC.rect,
							 45, NULL, SDL_FLIP_NONE);	
		}
		//Vader button
		SDL_SetRenderDrawColor(RENDERER, VaderBG.r, VaderBG.g, VaderBG.b, VaderBG.a);
		if (saberSelect.visible && VaderBG.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderFillRect(RENDERER, &VaderBG.hover);
			VaderIC.mouseHover(mouse_x, mouse_y, false);
			SDL_RenderCopyEx(RENDERER, hilt_Vader.mTexture, NULL, &VaderIC.hover,
							 45, NULL, SDL_FLIP_NONE);	
		}
		else if (saberSelect.visible && !VaderBG.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderFillRect(RENDERER, &VaderBG.rect);
			SDL_RenderCopyEx(RENDERER, hilt_Vader.mTexture, NULL, &VaderIC.rect,
							 45, NULL, SDL_FLIP_NONE);	
		}

		//background select
		SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0x0F);
		SDL_RenderFillRect(RENDERER, &bgSelect.rect);
		//carbon freezing chamber button
		if (bgSelect.visible && CarbonFreezing.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderCopy(RENDERER, background1.mTexture, NULL, &CarbonFreezing.hover);
		}
		else if (bgSelect.visible && !CarbonFreezing.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderCopy(RENDERER, background1.mTexture, NULL, &CarbonFreezing.rect);
		}
		//emperors throne room button
		if (bgSelect.visible && EmperorsThrone.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderCopy(RENDERER, background2.mTexture, NULL, &EmperorsThrone.hover);
		}
		else if (bgSelect.visible && !EmperorsThrone.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderCopy(RENDERER, background2.mTexture, NULL, &EmperorsThrone.rect);
		}
		//Hoth echo base button
		if (bgSelect.visible && HothEchoBase.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderCopy(RENDERER, background3.mTexture, NULL, &HothEchoBase.hover);
		}
		else if (bgSelect.visible && !HothEchoBase.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderCopy(RENDERER, background3.mTexture, NULL, &HothEchoBase.rect);
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
