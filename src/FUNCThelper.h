#ifndef FUNCTHELPER_H
#define FUNCTHELPER_H

void handleBackgroundSelectGUI(panel &bgSelect, vector <button> &bgButtons, int mouse_x, int mouse_y)
{
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
}

void handleSaberSelectGUI(panel &saberSelect, vector <button> &saberButtons, vector <button> &saberIcons,
						  int mouse_x, int mouse_y)
{
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
}

void renderSaberSelectGUI(SDL_Renderer *RENDERER, panel saberSelect, vector <button> saberButtons,
						  vector <button> saberIcons, vector <LTexture> &hilts, int mouse_x, int mouse_y)
{
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
}

void renderBackgroundSelectGUI(SDL_Renderer *RENDERER, panel bgSelect, vector <button> bgButtons, 
							   vector <LTexture> &backgrounds, int mouse_x, int mouse_y)
{
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
}

void renderMuteButton(SDL_Renderer *RENDERER, button muteIC, int mouse_x, int mouse_y, bool mute)
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
#endif
