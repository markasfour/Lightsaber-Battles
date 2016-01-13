#ifndef MENU_H
#define MENU_H

struct Menu
{
	//background rendering rectangle
	SDL_Rect backgroundRect;

	//player center
	SDL_Point center;
	
	button Simulator;
	
	SDL_Rect Title_rect1;
	LTexture Title_text1;
	SDL_Rect Title_rect2;
	LTexture Title_text2;
	
	LTexture Simulator_text;

	vector <bool> games;

	Menu()
	{
		backgroundRect.w = SCREEN_WIDTH * 1.05;
		backgroundRect.h = SCREEN_HEIGHT * 1.05;
		backgroundRect.x = (SCREEN_WIDTH - backgroundRect.w) / 2;
		backgroundRect.y = SCREEN_HEIGHT - backgroundRect.h;		

		center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
		
		button s(0x4F, 0x4F, 0x4F, 0xFF, (SCREEN_WIDTH / 2) - 100, SCREEN_HEIGHT / 2, 200, 30);
		Simulator = s;

		Title_rect1.w = 400;
		Title_rect1.h = 200;
		Title_rect1.x = SCREEN_WIDTH / 2 - 200;
		Title_rect1.y = SCREEN_HEIGHT / 2 - 200;
		
		Title_rect2 = Title_rect1;
		Title_rect2.y += 200;

		SDL_Color color = {0xFF, 0xFF, 0x00};
		Title_text1.loadFromRenderedText(RENDERER, FONT, "STAR", color);
		Title_text2.loadFromRenderedText(RENDERER, FONT, "WARS", color);
		
		color = {0x00, 0xFF, 0xFF};
		Simulator_text.loadFromRenderedText(RENDERER, FONT, "Simulator", color);

		games.push_back(false);
	}

	void handleMouseDown(int mouse_x, int mouse_y)
	{
		if (Simulator.wasClicked(mouse_x, mouse_y))
			games.at(0) = true;
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
		
		if (Simulator.mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &Simulator.hover);
			SDL_RenderCopy(RENDERER, Simulator_text.mTexture, NULL, &Simulator.hover);
		}
		else if (!Simulator.mouseHover(mouse_x, mouse_y, true))
		{	
			SDL_RenderFillRect(RENDERER, &Simulator.rect);
			SDL_RenderCopy(RENDERER, Simulator_text.mTexture, NULL, &Simulator.rect);
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
		SDL_RenderCopy(RENDERER, Title_text1.mTexture, NULL, &Title_rect1);
		SDL_RenderCopy(RENDERER, Title_text2.mTexture, NULL, &Title_rect2);

		//buttons
		renderButtons(RENDERER, mouse_x, mouse_y);
		
		//display
		SDL_RenderPresent(RENDERER);
	}
};

#endif
