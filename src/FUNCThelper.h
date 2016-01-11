#ifndef FUNCTHELPER_H
#define FUNCTHELPER_H

void handleSaberSelectMouseDown(panel saberSelect, vector <button> saberButtons, Character &main_char,
								Character &Luke, Character &Anakin, Character &Vader, bool &switched, 
								bool &soundOn, int mouse_x, int mouse_y)
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
				switched = true, main_char.saber.on = false, soundOn = false;
			}
		}
	}
}

void handleBackgroundSelectMouseDown(panel bgSelect, vector <button> bgButtons, int &background,
		 							 int mouse_x, int mouse_y)
{
	if (bgSelect.visible)
	{
		for (int i = 0; i < bgButtons.size(); i++)
		{
			if (bgButtons.at(i).wasClicked(mouse_x, mouse_y))
				background = i;
		}
	}
}

void handleMuteMouseDown(button muteIC, bool &mute, int mouse_x, int mouse_y)
{
	if (muteIC.wasClicked(mouse_x, mouse_y))
	{	
		mute = !mute;
		Mix_HaltChannel(2);	
	}
}

void handleSaberOnSwitchMouseDown(Character &main_char, button muteIC, int mouse_x, int mouse_y,
								  bool switched, bool mute, bool &soundOn, 
								  bool &soundOff, panel saberSelect, panel bgSelect)
{
	if (!saberSelect.visible && !bgSelect.visible && !muteIC.wasClicked(mouse_x, mouse_y))
		main_char.saber.on = !main_char.saber.on;
				
	if (main_char.saber.on && !switched && !soundOn)
	{
		if (!mute)
			Mix_PlayChannel(2, main_char.ON_SOUND, 0);
		soundOn = true;
		soundOff = false;
	}
	else if (!main_char.saber.on && !switched && !soundOff && !saberSelect.visible && !bgSelect.visible)
	{	
		if (!mute)
			Mix_PlayChannel(2, main_char.OFF_SOUND, 0);
		soundOff = true;
		soundOn = false;
	}
}

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
