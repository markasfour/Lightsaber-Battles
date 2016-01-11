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
#include "FUNCThelper.h"

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

	//player center
	SDL_Point center;
	
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
				handleSaberSelectMouseDown(saberSelect, saberButtons, main_char,
										   Luke, Anakin, Vader, switched, 
										   soundOn, mouse_x, mouse_y);
				
				//background select panel clicks
				handleBackgroundSelectMouseDown(bgSelect, bgButtons, background,
												mouse_x, mouse_y);
				
				//mute button click
				handleMuteMouseDown(muteIC, mute, mouse_x, mouse_y);
			
				//saber on switch and sound
				handleSaberOnSwitchMouseDown(main_char, muteIC, mouse_x, mouse_y,
											 switched, mute, soundOn, soundOff, 
											 saberSelect, bgSelect);
				
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
		main_char.handleHumSound(mute);
		
		//get center points
		center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
		main_char.saber.setCenterPoints();

		//move background
		backgroundRect.x = (-1 * (((center.x - mouse_x) / double(center.x)) * ((SCREEN_WIDTH - backgroundRect.w))/2)) - ((backgroundRect.w - SCREEN_WIDTH)/2);
		backgroundRect.y = (((center.y - mouse_y) / double(center.y)) * (SCREEN_HEIGHT - backgroundRect.h)/2);

		//handle angle
		main_char.saber.handleAngle(center, mouse_x, mouse_y);

		//handle swing
		main_char.saber.handleSwing();
		main_char.handleSwingSound(mute);
	
		//handle saber position
		main_char.saber.handleSaberPosition(mouse_x, mouse_y, switched);
		
		//lightsaber select gui
		handleSaberSelectGUI(saberSelect, saberButtons, saberIcons, mouse_x, mouse_y);

		//background select gui
		handleBackgroundSelectGUI(bgSelect, bgButtons, mouse_x, mouse_y);
		
		//render everything
		//clear screen
		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
		SDL_RenderClear(RENDERER);
		
		//background
		SDL_RenderCopy(RENDERER, backgrounds.at(background).mTexture, NULL, &backgroundRect);
		
		//blade
		main_char.renderBlade(RENDERER);
		
		//hilt
		main_char.renderHilt(RENDERER);
		
		//saber select
		renderSaberSelectGUI(RENDERER, saberSelect, saberButtons, saberIcons, hilts, mouse_x, mouse_y);
				
		//background select
		renderBackgroundSelectGUI(RENDERER, bgSelect, bgButtons, backgrounds, mouse_x, mouse_y);
				
		//mute button
		renderMuteButton(RENDERER, muteIC, mouse_x, mouse_y, mute);

		//display
		SDL_RenderPresent(RENDERER);
		
		//cap the frame rate
		if (fps.get_ticks() < 1000/FRAMES_PER_SECOND)
			SDL_Delay((1000/FRAMES_PER_SECOND) - fps.get_ticks());
	}

	close();
	return 0;
}
