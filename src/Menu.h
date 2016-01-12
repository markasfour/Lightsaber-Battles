#ifndef MENU_H
#define MENU_H

struct Menu
{
	//background rendering rectangle
	SDL_Rect backgroundRect;

	//player center
	SDL_Point center;
	
	vector <bool> games;

	Menu()
	{
		backgroundRect.w = SCREEN_WIDTH * 1.05;
		backgroundRect.h = SCREEN_HEIGHT * 1.05;
		backgroundRect.x = (SCREEN_WIDTH - backgroundRect.w) / 2;
		backgroundRect.y = SCREEN_HEIGHT - backgroundRect.h;		

		center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
		
		games.push_back(false);
	}

	void handleMouseDown(int mouse_x, int mouse_y)
	{
		games.at(0) = true;
	}

	void handleBackgroundMovement(int mouse_x, int mouse_y)
	{
		//move background
		backgroundRect.x = (-1 * (((center.x - mouse_x) / double(center.x)) * ((SCREEN_WIDTH - backgroundRect.w))/2)) - ((backgroundRect.w - SCREEN_WIDTH)/2);
		backgroundRect.y = (((center.y - mouse_y) / double(center.y)) * (SCREEN_HEIGHT - backgroundRect.h)/2);
	}

	void renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
	{
		//render everything
		//clear screen
		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
		SDL_RenderClear(RENDERER);
		
		//background
		SDL_RenderCopy(RENDERER, menuBackground.mTexture, NULL, &backgroundRect);
		
		//display
		SDL_RenderPresent(RENDERER);
	}
};

#endif
