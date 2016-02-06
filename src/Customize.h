#ifndef CUSTOMIZE_H
#define CUSTOMIZE_H

struct Customize
{
	private: 
	//background
	SDL_Rect backgroundRect;
	
	//saber to display
	Character custom;

	//hilt selection panel
	button hiltIC;
	panel hiltSelect;
	vector <button> hiltButtons;
	vector <button> hiltIcons;
	
	//background selection panel
	button bgIC;
	panel bgSelect;
	vector <button> bgButtons;
	vector <button> bgIcons;

	//color selection panel
	panel colorSelect;
	vector <button> colorButtons;

	//mute
	bool mute;
	button muteIC;
	
	//back
	button back;
	LTexture back_text;
	
	public:
	Customize()
	{
		//background
		backgroundRect.w = SCREEN_WIDTH * 1.05;
		backgroundRect.h = SCREEN_HEIGHT * 1.05;
		backgroundRect.x = (SCREEN_WIDTH - backgroundRect.w) / 2;
		backgroundRect.y = SCREEN_HEIGHT - backgroundRect.h;
	
		//lightsaber
		custom.saber.blade.h = 250;
		custom.saber.hilt.x = SCREEN_WIDTH / 2;
		custom.saber.blade.x = custom.saber.hilt.x - 3;
		custom.saber.bladetip.x = custom.saber.blade.x;
		custom.saber.bladebase.x = custom.saber.blade.x;
		custom.saber.hilt.y = 3 * SCREEN_HEIGHT / 4;
		custom.saber.blade.y = custom.saber.hilt.y - 250;
		custom.saber.bladetip.y = custom.saber.blade.y - 7;
		custom.saber.bladebase.y = custom.saber.hilt.y;

		//hilt
		button hi (SCREEN_WIDTH - 55 - 5, 40, 55, 55);
		hiltIC = hi;

		panel h(SCREEN_WIDTH, 0, 6, 45, 10, true);
		hiltSelect = h;

		button LukeBG(0x00, 0x00, 0x00, 0xFF, hiltSelect.rect.x + 10, 10, 45, 45);
		button AnakinBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, LukeBG.rect.y + 45 + 10, 45, 45);	
		button VaderBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, AnakinBG.rect.y + 45 + 10, 45, 45);
		button SidiusBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, VaderBG.rect.y + 45 + 10, 45, 45);
		button WinduBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, SidiusBG.rect.y + 45 + 10, 45, 45);
		button FistoBG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x, WinduBG.rect.y + 45 + 10, 45, 45);

		button LukeIC(LukeBG.rect.x + (LukeBG.rect.w / 2) - 3, LukeBG.rect.y + 3, 9, 40);
		button AnakinIC(AnakinBG.rect.x + (AnakinBG.rect.w / 2) - 3, AnakinBG.rect.y + 3, 9, 40);
		button VaderIC(VaderBG.rect.x + (VaderBG.rect.w / 2) - 3, VaderBG.rect.y + 3, 9, 40);
		button SidiusIC(SidiusBG.rect.x + (SidiusBG.rect.w / 2) - 3, SidiusBG.rect.y + 3, 9, 40);
		button WinduIC(WinduBG.rect.x + (WinduBG.rect.w / 2) - 3, WinduBG.rect.y + 3, 9, 40);
		button FistoIC(FistoBG.rect.x + (FistoBG.rect.w / 2) - 3, FistoBG.rect.y + 3, 9, 40);

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
		
		//background
		button bg (SCREEN_WIDTH - 55 - 5, hiltIC.rect.y + hiltIC.rect.h + 20, 55, 55);
		bgIC = bg;

		panel btemp(SCREEN_WIDTH, 0, 3, 45, 10, true);
		bgSelect = btemp;
		
		button BG1(0x00, 0x00, 0x00, 0xFF, bgSelect.rect.x + 10, 10, 45, 45);
		button BG2(0x00, 0x00, 0x00, 0xFF, BG1.rect.x, BG1.rect.y + 45 + 10, 45, 45);	
		button BG3(0x00, 0x00, 0x00, 0xFF, BG1.rect.x, BG2.rect.y + 45 + 10, 45, 45);
	
		button BG1IC(BG1.rect.x, BG1.rect.y, 45, 45);
		button BG2IC(BG2.rect.x, BG2.rect.y, 45, 45);
		button BG3IC(BG3.rect.x, BG3.rect.y, 45, 45);

		bgButtons.push_back(BG1);
		bgButtons.push_back(BG2);
		bgButtons.push_back(BG3);

		bgIcons.push_back(BG1IC);
		bgIcons.push_back(BG2IC);
		bgIcons.push_back(BG3IC);

		//colors
		panel c(0, 0, 7, 45, 10, true);
		colorSelect = c;

		button g(0x00, 0xFF, 0x00, 0xFF, colorSelect.rect.x + 10, 10, 45, 45);
		button b(0x00, 0x00, 0xFF, 0xFF, g.rect.x, g.rect.y + 45 + 10, 45, 45);
		button r(0xFF, 0x00, 0x00, 0xFF, g.rect.x, b.rect.y + 45 + 10, 45, 45);
		button p(0xFF, 0x00, 0xFF, 0xFF, g.rect.x, r.rect.y + 45 + 10, 45, 45);
		button y(0xFF, 0xFF, 0x00, 0xFF, g.rect.x, p.rect.y + 45 + 10, 45, 45);
		button w(0xFF, 0xFF, 0xFF, 0xFF, g.rect.x, y.rect.y + 45 + 10, 45, 45);
		button bl(0x00, 0x00, 0x00, 0xFF, g.rect.x, w.rect.y + 45 + 10, 45, 45);

		colorButtons.push_back(g);
		colorButtons.push_back(b);
		colorButtons.push_back(r);
		colorButtons.push_back(p);
		colorButtons.push_back(y);
		colorButtons.push_back(w);
		colorButtons.push_back(bl);

		//mute
		mute = false;
		button mIC (SCREEN_WIDTH - 25 - 65, 5, 20, 20);
		muteIC = mIC;

		//back
		button B(0x0F, 0x0F, 0x0F, 0xFF, colorSelect.rect.x + 65, 0, 50, 30);
		back = B;
		SDL_Color color = {0xFF, 0xFF, 0xFF};
		back_text.loadFromRenderedText(RENDERER, FONT, "back", color);
	}
	private:
	void handleHiltIconMouseDown(int mouse_x, int mouse_y);
	void handleBackgroundIconMouseDown(int mouse_x, int mouse_y);
	void handleHiltSelectMouseDown(int mouse_x, int mouse_y, Character &c);
	void handleBackgroundSelectMouseDown(int mouse_x, int mouse_y, int &bg);
	void handleColorSelectMouseDown(int mouse_x, int mouse_y, Character &c);
	void handleMuteMouseDown(int mouse_x, int mouse_y);
	void handleBackMouseDown(int mouse_x, int mouse_y, Character &c);
	public:
	void handleMouseDown(int mouse_x, int mouse_y, Character &c, int &bg);
	void handleGame(int mouse_x, int mouse_y);
	private:
	void renderHiltIcon(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderBackgroundIcon(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderHiltSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderBackgroundSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderColorSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderMuteButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderBackButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	public:
	void renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, int bg);	
	void close();
};

void Customize::handleHiltIconMouseDown(int mouse_x, int mouse_y)
{
	if (hiltIC.wasClicked(mouse_x, mouse_y) && !bgSelect.visible)
		hiltSelect.visible = true;
}

void Customize::handleBackgroundIconMouseDown(int mouse_x, int mouse_y)
{
	if (bgIC.wasClicked(mouse_x, mouse_y) && !hiltSelect.visible)
		bgSelect.visible = true;
}

void Customize::handleHiltSelectMouseDown(int mouse_x, int mouse_y, Character &c)
{
	for (int i = 0; i < hiltButtons.size(); i++)
	{
		if (hiltButtons.at(i).wasClicked(mouse_x, mouse_y))
		{
			custom.hilt = &hilts.at(i); 
			hiltSelect.visible = false;
		}
	}
	//save hilt	
	c = custom;
}

void Customize::handleBackgroundSelectMouseDown(int mouse_x, int mouse_y, int &bg)
{
	for (int i = 0; i < bgButtons.size(); i++)
	{
		if (bgButtons.at(i).wasClicked(mouse_x, mouse_y))
		{
			bg = i;
			bgSelect.visible = false;
		}
	}
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

void Customize::handleMouseDown(int mouse_x, int mouse_y, Character &c, int &bg)
{	
	//hilt icon
	handleHiltIconMouseDown(mouse_x, mouse_y);

	//background icon
	handleBackgroundIconMouseDown(mouse_x, mouse_y);

	//hilt select
	handleHiltSelectMouseDown(mouse_x, mouse_y, c);
	
	//background select
	handleBackgroundSelectMouseDown(mouse_x, mouse_y, bg);	

	//color select
	handleColorSelectMouseDown(mouse_x, mouse_y, c);
	
	//mute button click
	handleMuteMouseDown(mouse_x, mouse_y);
	
	//back button click
	handleBackMouseDown(mouse_x, mouse_y, c);
}

void Customize::handleGame(int mouse_x, int mouse_y)
{
	hiltSelect.move(0.5, hiltButtons, hiltIcons);

	bgSelect.move(0.5, bgButtons, bgIcons);
}

void Customize::renderHiltIcon(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	if (hiltIC.mouseHover(mouse_x, mouse_y, true))
			SDL_RenderCopy(RENDERER, hilt_icon.mTexture, NULL, &hiltIC.hover);
	else if (!hiltIC.mouseHover(mouse_x, mouse_y, true))
		SDL_RenderCopy(RENDERER, hilt_icon.mTexture, NULL, &hiltIC.rect);
}

void Customize::renderBackgroundIcon(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	if (bgIC.mouseHover(mouse_x, mouse_y, true))
			SDL_RenderCopy(RENDERER, background_icon.mTexture, NULL, &bgIC.hover);
	else if (!bgIC.mouseHover(mouse_x, mouse_y, true))
		SDL_RenderCopy(RENDERER, background_icon.mTexture, NULL, &bgIC.rect);
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

void Customize::renderBackgroundSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0x0F);
	SDL_RenderFillRect(RENDERER, &bgSelect.rect);
	//buttons
	for (int i = 0; i < bgButtons.size(); i++)
	{
		SDL_SetRenderDrawColor(RENDERER, bgButtons.at(i).r, bgButtons.at(i).g, bgButtons.at(i).b, bgButtons.at(i).a);
		if (bgButtons.at(i).mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &bgButtons.at(i).hover);
			bgIcons.at(i).mouseHover(mouse_x, mouse_y, false);
			SDL_RenderCopy(RENDERER, backgrounds.at(i).mTexture, NULL, &bgIcons.at(i).hover);
		}
		else if (!bgButtons.at(i).mouseHover(mouse_x, mouse_y, true))
		{
			SDL_RenderFillRect(RENDERER, &bgButtons.at(i).rect);
			bgIcons.at(i).mouseHover(mouse_x, mouse_y, false);
			SDL_RenderCopy(RENDERER, backgrounds.at(i).mTexture, NULL, &bgIcons.at(i).rect);
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

void Customize::renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, int bg)
{
	custom.saber.on = true;
	custom.saber.blade.h = 250;
	
	//clear screen
	SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
	SDL_RenderClear(RENDERER);
	
	//background
	SDL_RenderCopy(RENDERER, backgrounds.at(bg).mTexture, NULL, &backgroundRect);

	//blade
	custom.renderBlade(RENDERER);
	
	//hilt
	custom.renderHilt(RENDERER);
	
	//hilt icon
	renderHiltIcon(RENDERER, mouse_x, mouse_y);
	
	//background icon
	renderBackgroundIcon(RENDERER, mouse_x, mouse_y);	

	//hilt select GUI
	renderHiltSelectGUI(RENDERER, mouse_x, mouse_y);
	
	//background select GUI
	renderBackgroundSelectGUI(RENDERER, mouse_x, mouse_y);

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
