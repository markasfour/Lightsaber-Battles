#ifndef CUSTOMIZE_H
#define CUSTOMIZE_H

struct Customize
{
	//background
	SDL_Rect backgroundRect;
	
	//saber to display
	Character custom;

	//hilt selection panel
	panel hiltSelect;
	vector <button> hiltButtons;
	vector <button> hiltIcons;
	button LukeBG;
	button LukeIC;
	button AnakinBG;
	button AnakinIC;
	button VaderBG;
	button VaderIC;
	button SidiusBG;
	button SidiusIC;
	button WinduBG;
	button WinduIC;
	button FistoBG;
	button FistoIC;

	//color selection panel
	panel colorSelect;
	vector <button> colorButtons;
	button green;
	button blue;
	button red;
	button purple;
	button yellow;
	button white;
	button black;

	//mute
	bool mute;
	button muteIC;
	
	//back
	button back;
	LTexture back_text;

	Customize()
	{
		backgroundRect.w = SCREEN_WIDTH * 1.05;
		backgroundRect.h = SCREEN_HEIGHT * 1.05;
		backgroundRect.x = (SCREEN_WIDTH - backgroundRect.w) / 2;
		backgroundRect.y = SCREEN_HEIGHT - backgroundRect.h;
	
		custom.saber.blade.h = 250;
		custom.saber.hilt.x = SCREEN_WIDTH / 2;
		custom.saber.blade.x = custom.saber.hilt.x - 3;
		custom.saber.bladetip.x = custom.saber.blade.x;
		custom.saber.bladebase.x = custom.saber.blade.x;
		custom.saber.hilt.y = 3 * SCREEN_HEIGHT / 4;
		custom.saber.blade.y = custom.saber.hilt.y - 250;
		custom.saber.bladetip.y = custom.saber.blade.y - 7;
		custom.saber.bladebase.y = custom.saber.hilt.y;

		panel h(SCREEN_WIDTH - 65, 0, 6, 45, 10, true);
		hiltSelect = h;

		button LBG(0x00, 0x00, 0x00, 0xFF, hiltSelect.rect.x + 10, 10, 45, 45);
		LukeBG = LBG;
		button ABG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, LukeBG.rect.y + 45 + 10, 45, 45);	
		AnakinBG = ABG;
		button VBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, AnakinBG.rect.y + 45 + 10, 45, 45);
		VaderBG = VBG;
		button SBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, VaderBG.rect.y + 45 + 10, 45, 45);
		SidiusBG = SBG;
		button WBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, SidiusBG.rect.y + 45 + 10, 45, 45);
		WinduBG = WBG;
		button FBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, WinduBG.rect.y + 45 + 10, 45, 45);
		FistoBG = FBG;

		button LIC(LukeBG.rect.x + (LukeBG.rect.w / 2) - 3, LukeBG.rect.y + 3, 9, 40);
		LukeIC = LIC;
		button AIC(AnakinBG.rect.x + (AnakinBG.rect.w / 2) - 3, AnakinBG.rect.y + 3, 9, 40);
		AnakinIC = AIC;
		button VIC(VaderBG.rect.x + (VaderBG.rect.w / 2) - 3, VaderBG.rect.y + 3, 9, 40);
		VaderIC = VIC;
		button SIC(SidiusBG.rect.x + (SidiusBG.rect.w / 2) - 3, SidiusBG.rect.y + 3, 9, 40);
		SidiusIC = SIC;
		button WIC(WinduBG.rect.x + (WinduBG.rect.w / 2) - 3, WinduBG.rect.y + 3, 9, 40);
		WinduIC = WIC;
		button FIC(FistoBG.rect.x + (FistoBG.rect.w / 2) - 3, FistoBG.rect.y + 3, 9, 40);
		FistoIC = FIC;

		hiltButtons.push_back(LukeBG);
		hiltButtons.push_back(AnakinBG);
		hiltButtons.push_back(VaderBG);
		hiltButtons.push_back(SidiusBG);
		hiltButtons.push_back(WinduBG);
		hiltButtons.push_back(FistoBG);

		hiltIcons.push_back(LukeIC);
		hiltIcons.push_back(AnakinIC);
		hiltIcons.push_back(VaderIC);
		hiltIcons.push_back(SidiusIC);
		hiltIcons.push_back(WinduIC);
		hiltIcons.push_back(FistoIC);

		panel c(0, 0, 7, 45, 10, true);
		colorSelect = c;

		button g(0x00, 0xFF, 0x00, 0xFF, colorSelect.rect.x + 10, 10, 45, 45);
		green = g;
		button b(0x00, 0x00, 0xFF, 0xFF, green.rect.x, green.rect.y + 45 + 10, 45, 45);
		blue = b;
		button r(0xFF, 0x00, 0x00, 0xFF, green.rect.x, blue.rect.y + 45 + 10, 45, 45);
		red = r;
		button p(0xFF, 0x00, 0xFF, 0xFF, green.rect.x, red.rect.y + 45 + 10, 45, 45);
		purple = p;
		button y(0xFF, 0xFF, 0x00, 0xFF, green.rect.x, purple.rect.y + 45 + 10, 45, 45);
		yellow = y;
		button w(0xFF, 0xFF, 0xFF, 0xFF, green.rect.x, yellow.rect.y + 45 + 10, 45, 45);
		white = w;
		button bl(0x00, 0x00, 0x00, 0xFF, green.rect.x, white.rect.y + 45 + 10, 45, 45);
		black = bl;

		colorButtons.push_back(green);
		colorButtons.push_back(blue);
		colorButtons.push_back(red);
		colorButtons.push_back(purple);
		colorButtons.push_back(yellow);
		colorButtons.push_back(white);
		colorButtons.push_back(black);

		mute = false;
		button mIC (SCREEN_WIDTH - 25 - 65, 5, 20, 20);
		muteIC = mIC;

		button B(0x0F, 0x0F, 0x0F, 0xFF, colorSelect.rect.x + 65, 0, 50, 30);
		back = B;
		SDL_Color color = {0xFF, 0xFF, 0xFF};
		back_text.loadFromRenderedText(RENDERER, FONT, "back", color);
	}
	
	void handleHiltSelectMouseDown(int mouse_x, int mouse_y, Character &c);
	void handleColorSelectMouseDown(int mouse_x, int mouse_y, Character &c);
	void handleMuteMouseDown(int mouse_x, int mouse_y);
	void handleBackMouseDown(int mouse_x, int mouse_y, Character &c);
	void handleMouseDown(int mouse_x, int mouse_y, Character &c);
	void renderHiltSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderColorSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderMuteButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderBackButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);	
	void close();
};

void Customize::handleHiltSelectMouseDown(int mouse_x, int mouse_y, Character &c)
{
	for (int i = 0; i < hiltButtons.size(); i++)
	{
		if (hiltButtons.at(i).wasClicked(mouse_x, mouse_y))
		{
			custom.hilt = &hilts.at(i); 
		}
	}
	c = custom;
}

void Customize::handleColorSelectMouseDown(int mouse_x, int mouse_y, Character &c)
{
	for (int i = 0; i < colorButtons.size(); i++)
	{
		if (colorButtons.at(i).wasClicked(mouse_x, mouse_y))
		{
			custom.blade = &blades.at(i); 
			custom.bladetip = &bladetips.at(i);
			custom.bladebase = &bladebases.at(i);
		}
	}
	c = custom;
}

void Customize::handleMuteMouseDown(int mouse_x, int mouse_y)
{
	if (muteIC.wasClicked(mouse_x, mouse_y))
	{	
		mute = !mute;
		Mix_HaltChannel(-1);
	}
}

void Customize::handleBackMouseDown(int mouse_x, int mouse_y, Character &c)
{
	if (back.wasClicked(mouse_x, mouse_y))
	{
		custom.saber.blade.h = 0;
		custom.saber.on = false;
		c = custom;
		GAMES.at(1) = false;
		Mix_HaltChannel(-1);
	}
}

void Customize::handleMouseDown(int mouse_x, int mouse_y, Character &c)
{
	//hilt select
	handleHiltSelectMouseDown(mouse_x, mouse_y, c);
	
	//color select
	handleColorSelectMouseDown(mouse_x, mouse_y, c);
	
	//mute button click
	handleMuteMouseDown(mouse_x, mouse_y);
	
	//back button click
	handleBackMouseDown(mouse_x, mouse_y, c);
}

void Customize::renderHiltSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0x0F);
	SDL_RenderFillRect(RENDERER, &hiltSelect.rect);
	//buttons
	for (int i = 0; i < hiltButtons.size(); i++)
	{
		SDL_SetRenderDrawColor(RENDERER, hiltButtons.at(i).r, hiltButtons.at(i).g, hiltButtons.at(i).b, hiltButtons.at(i).a);
		if (hiltButtons.at(i).mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &hiltButtons.at(i).hover);
			hiltIcons.at(i).mouseHover(mouse_x, mouse_y, false);
			SDL_RenderCopyEx(RENDERER, hilts.at(i).mTexture, NULL, &hiltIcons.at(i).hover,
						 	 45, NULL, SDL_FLIP_NONE);	
		}
		else if (!hiltButtons.at(i).mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &hiltButtons.at(i).rect);
			hiltIcons.at(i).mouseHover(mouse_x, mouse_y, false);
			SDL_RenderCopyEx(RENDERER, hilts.at(i).mTexture, NULL, &hiltIcons.at(i).rect,
						 	 45, NULL, SDL_FLIP_NONE);
		}
	}
}

void Customize::renderColorSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0x0F);
	SDL_RenderFillRect(RENDERER, &colorSelect.rect);
	//buttons
	for (int i = 0; i < colorButtons.size(); i++)
	{
		SDL_SetRenderDrawColor(RENDERER, colorButtons.at(i).r, colorButtons.at(i).g, colorButtons.at(i).b, colorButtons.at(i).a);
		if (colorButtons.at(i).mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &colorButtons.at(i).hover);
		}
		else if (!colorButtons.at(i).mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &colorButtons.at(i).rect);
		}
	}
}

void Customize::renderMuteButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
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

void Customize::renderBackButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
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

void Customize::renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	custom.saber.on = true;
	
	//clear screen
	SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
	SDL_RenderClear(RENDERER);
	
	//background
	SDL_RenderCopy(RENDERER, backgrounds.at(0).mTexture, NULL, &backgroundRect);

	//blade
	custom.renderBlade(RENDERER);
	
	//hilt
	custom.renderHilt(RENDERER);

	//hilt select GUI
	renderHiltSelectGUI(RENDERER, mouse_x, mouse_y);
	
	//color select GUI
	renderColorSelectGUI(RENDERER, mouse_x, mouse_y);

	//mute button
	renderMuteButton(RENDERER, mouse_x, mouse_y);

	//back button
	renderBackButton(RENDERER, mouse_x, mouse_y);
			
	//display
	SDL_RenderPresent(RENDERER);
}

void Customize::close()
{
	back_text.free();
}

#endif
