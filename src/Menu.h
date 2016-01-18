#ifndef MENU_H
#define MENU_H

//global game being played vector
vector <bool> GAMES;

struct Menu
{
	//background rendering rectangle
	SDL_Rect backgroundRect;

	//player center
	SDL_Point center;
	
	SDL_Rect Title_rect;
	LTexture Title_text;
	
	vector <button> menuButtons; 
	button Simulator;
	LTexture Simulator_text;
	button Customize;
	LTexture Customize_text;

	Menu()
	{
		backgroundRect.w = SCREEN_WIDTH * 1.05;
		backgroundRect.h = SCREEN_HEIGHT * 1.05;
		backgroundRect.x = (SCREEN_WIDTH - backgroundRect.w) / 2;
		backgroundRect.y = SCREEN_HEIGHT - backgroundRect.h;		

		center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
		
		Title_rect.w = 600;
		Title_rect.h = 200;
		Title_rect.x = SCREEN_WIDTH / 2 - 300;
		Title_rect.y = SCREEN_HEIGHT / 2 - 200;
		
		SDL_Color color = {0xFF, 0xFF, 0x00};
		Title_text.loadFromRenderedText(RENDERER, FONT, "Lightsaber Battles", color);
		
		button s(0x4F, 0x4F, 0x4F, 0xFF, (SCREEN_WIDTH / 2) - 100, SCREEN_HEIGHT / 2, 200, 30);
		Simulator = s;
		menuButtons.push_back(Simulator);
		color = {0x00, 0xFF, 0xFF};
		Simulator_text.loadFromRenderedText(RENDERER, FONT, "Simulator", color);

		button c(0x4F, 0x4F, 0x4F, 0xFF, (SCREEN_WIDTH / 2) - 100, Simulator.rect.y + 30 + 10, 200, 30);
		Customize = c;
		menuButtons.push_back(Customize);
		color = {0x00, 0xFF, 0xFF};
		Customize_text.loadFromRenderedText(RENDERER, FONT, "Customize", color);

		GAMES.push_back(false); //simulator
		GAMES.push_back(false); //customize
	}

	void handleMouseDown(int mouse_x, int mouse_y)
	{
		if (Simulator.wasClicked(mouse_x, mouse_y))
			GAMES.at(0) = true;
		else if (Customize.wasClicked(mouse_x, mouse_y))
			GAMES.at(1) = true;
	}

	void handleBackgroundMovement(int mouse_x, int mouse_y)
	{
		//move background
		backgroundRect.x = (-1 * (((center.x - mouse_x) / double(center.x)) * ((SCREEN_WIDTH - backgroundRect.w))/2)) - ((backgroundRect.w - SCREEN_WIDTH)/2);
		backgroundRect.y = (((center.y - mouse_y) / double(center.y)) * (SCREEN_HEIGHT - backgroundRect.h)/2);
	}

	void renderButtons(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
	{
		SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0xFF);
		
		for (int i = 0; i < menuButtons.size(); i++)
		{
			if (menuButtons.at(i).mouseHover(mouse_x, mouse_y, true))
			{
				SDL_RenderFillRect(RENDERER, &menuButtons.at(i).hover);
				if (i == 0)
					SDL_RenderCopy(RENDERER, Simulator_text.mTexture, NULL, &menuButtons.at(0).hover);
				if (i == 1)
					SDL_RenderCopy(RENDERER, Customize_text.mTexture, NULL, &menuButtons.at(1).hover);
			}
			else if (!menuButtons.at(i).mouseHover(mouse_x, mouse_y, true))
			{	
				SDL_RenderFillRect(RENDERER, &menuButtons.at(i).rect);
				if (i == 0)
					SDL_RenderCopy(RENDERER, Simulator_text.mTexture, NULL, &menuButtons.at(0).rect);
				if (i == 1)
					SDL_RenderCopy(RENDERER, Customize_text.mTexture, NULL, &menuButtons.at(1).rect);
			}
		}
	}

	void renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
	{
		//render everything
		//clear screen
		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
		SDL_RenderClear(RENDERER);
		
		//background
		SDL_RenderCopy(RENDERER, menuBackground.mTexture, NULL, &backgroundRect);
		
		//title
		SDL_RenderCopy(RENDERER, Title_text.mTexture, NULL, &Title_rect);

		//buttons
		renderButtons(RENDERER, mouse_x, mouse_y);
		
		//display
		SDL_RenderPresent(RENDERER);
	}

	void close()
	{
		Title_text.free();
		Simulator_text.free();
		Customize_text.free();
	}
};

#endif
