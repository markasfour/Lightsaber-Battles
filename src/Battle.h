#ifndef BATTLE_H
#define BATTLE_H

struct Battle
{
	//background rendering rectangle
	SDL_Rect backgroundRect;
	int background;

	//player center
	SDL_Point center;
	SDL_Point op_center;
	
	//init position
	bool start;

	//characters
	Character main_char;
	Character opponent;

	//mute
	bool mute;
	bool soundOn;
	bool soundOff;
	button muteIC;
	
	//back
	button back;
	LTexture back_text;

	Battle()
	{
		srand(time(NULL));

		backgroundRect.w = SCREEN_WIDTH * 1.05;
		backgroundRect.h = SCREEN_HEIGHT * 1.05;
		backgroundRect.x = (SCREEN_WIDTH - backgroundRect.w) / 2;
		backgroundRect.y = SCREEN_HEIGHT - backgroundRect.h;

		background = rand() % backgrounds.size();

		start = true;
		
		mute = false;
		soundOn = false;
		soundOff = false;
		button mIC (SCREEN_WIDTH - 25, 5, 20, 20);
		muteIC = mIC;

		button B(0x0F, 0x0F, 0x0F, 0xFF, 0, 0, 50, 30);
		back = B;
		SDL_Color color = {0xFF, 0xFF, 0xFF};
		back_text.loadFromRenderedText(RENDERER, FONT, "back", color);
	}
	
	void handleMuteMouseDown(int mouse_x, int mouse_y);
	void handleBackMouseDown(int mouse_x, int mouse_y);
	void handleMouseDown(int mouse_x, int mouse_y);
	void handleGame(int mouse_x, int mouse_y, Character custom);
	void renderMuteButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderBackButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, Character custom);
};

void Battle::handleMuteMouseDown(int mouse_x, int mouse_y)
{
	if (muteIC.wasClicked(mouse_x, mouse_y))
	{	
		mute = !mute;
		Mix_HaltChannel(1);
		Mix_HaltChannel(2);
		Mix_HaltChannel(3);
		Mix_HaltChannel(4);
	}
}

void Battle::handleBackMouseDown(int mouse_x, int mouse_y)
{
	if (back.wasClicked(mouse_x, mouse_y))
	{	
		GAMES.at(2) = false;	
		SDL_ShowCursor(1);
	}
}

void Battle::handleMouseDown(int mouse_x, int mouse_y)
{
	//mute button click
	handleMuteMouseDown(mouse_x, mouse_y);
	
	//back button click
	handleBackMouseDown(mouse_x, mouse_y);
}

void Battle::handleGame(int mouse_x, int mouse_y, Character custom)
{
	main_char = custom;
	
	SDL_ShowCursor(0);
	
	if (start && mouse_x == 0 && mouse_y == 0)
	{
		mouse_x = SCREEN_WIDTH / 2;
		mouse_y = 3 * SCREEN_HEIGHT / 4;
	}
	if (start && mouse_x != SCREEN_WIDTH / 2 && mouse_y != SCREEN_HEIGHT / 4)
		start = false;
	
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
	main_char.saber.handleSaberPosition(mouse_x, mouse_y, false);
}

void Battle::renderMuteButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	if (mute)
		{
			if (muteIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, muteOn.mTexture, NULL, &muteIC.hover);
			else if (!muteIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, muteOn.mTexture, NULL, &muteIC.rect);
		}
		else if (!mute)
		{
			if (muteIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, muteOff.mTexture, NULL, &muteIC.hover);
			else if (!muteIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, muteOff.mTexture, NULL, &muteIC.rect);
		}
}

void Battle::renderBackButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0xFF);
	if (back.mouseHover(mouse_x, mouse_y, true))
	{
		SDL_RenderFillRect(RENDERER, &back.hover);
		SDL_RenderCopy(RENDERER, back_text.mTexture, NULL, &back.hover);
	}
	else if (!back.mouseHover(mouse_x, mouse_y, true))
	{
		SDL_RenderFillRect(RENDERER, &back.rect);
		SDL_RenderCopy(RENDERER, back_text.mTexture, NULL, &back.rect);
	}
}

void Battle::renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, Character custom)
{
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
	
	//mute button
	renderMuteButton(RENDERER, mouse_x, mouse_y);

	//back button
	renderBackButton(RENDERER, mouse_x, mouse_y);

	//display
	SDL_RenderPresent(RENDERER);
}

#endif
