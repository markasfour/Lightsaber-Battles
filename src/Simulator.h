#ifndef FUNCTHELPER_H
#define FUNCTHELPER_H

struct Simulator
{
	//background rendering rectangle
	SDL_Rect backgroundRect;

	//player center
	SDL_Point center;
	
	//init position
	bool start;
	
	//characters
	Character main_char;
	//Character Luke;
	//Character Anakin;
	//Character Vader;

	//lightsaber selection panel
	//panel saberSelect;
	//bool switched;
	//vector <button> saberButtons;
	//vector <button> saberIcons;
	//button LukeBG;
	//button AnakinBG;	
	//button VaderBG;
	//button CustomBG;
	//button LukeIC;
	//button AnakinIC;
	//button VaderIC;
	//button CustomIC;

	//background selection panel
	//int background;
	//panel bgSelect;
	//vector <button> bgButtons;
	//button CarbonFreezing;
	//button EmperorsThrone;
	//button HothEchoBase;

	//mute
	bool soundOn;
	bool soundOff;
	button muteIC;
	button muteMusicIC;

	//back
	button back;
	LTexture back_text;

	//customize
	button customize;
	LTexture customize_text;

	//battle
	button battle;
	LTexture battle_text;

	//bottom bar
	SDL_Rect bottom;

	Simulator(Character custom)
	{
		//Character m("Luke");
		main_char = custom;
		//Character l("Luke");
		//Luke = l;
		//Character a("Anakin");
		//Anakin = a;
		//Character v("Vader");
		//Vader = v;

		backgroundRect.w = SCREEN_WIDTH * 1.05;
		backgroundRect.h = SCREEN_HEIGHT * 1.05;
		backgroundRect.x = (SCREEN_WIDTH - backgroundRect.w) / 2;
		backgroundRect.y = SCREEN_HEIGHT - backgroundRect.h;

		start = true;
		//switched = false;

		//panel s(0, SCREEN_HEIGHT, 4, 45, 10);
		//saberSelect = s;
		
		//button LBG(0x00, 0x00, 0x00, 0xFF, 10, SCREEN_HEIGHT, 45, 45);
		//LukeBG = LBG;
		//button ABG(0x00, 0x00, 0x00, 0xFF, LukeBG.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);	
		//AnakinBG = ABG;
		//button VBG(0x00, 0x00, 0x00, 0xFF, AnakinBG.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);
		//VaderBG = VBG;
		//button CBG(0x00, 0x00, 0x00, 0xFF, VaderBG.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);
		//CustomBG = CBG;

		//button LIC(LukeBG.rect.x + (LukeBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
		//LukeIC = LIC;
		//button AIC(AnakinBG.rect.x + (AnakinBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
		//AnakinIC = AIC;
		//button VIC(VaderBG.rect.x + (VaderBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
		//VaderIC = VIC;
		//button CIC(CustomBG.rect.x + (CustomBG.rect.w / 2) - 3, SCREEN_HEIGHT + 3, 9, 40);
		//CustomIC = CIC;

		//saberButtons.push_back(LukeBG);
		//saberButtons.push_back(AnakinBG);
		//saberButtons.push_back(VaderBG);
		//saberButtons.push_back(CustomBG);

		//saberIcons.push_back(LukeIC);
		//saberIcons.push_back(AnakinIC);
		//saberIcons.push_back(VaderIC);
		//saberIcons.push_back(CustomIC);

		//background = 0;
		
		//panel bgs(465, SCREEN_HEIGHT, 3, 45, 10);
		//bgSelect = bgs;
		
		//button CF(bgSelect.rect.x + 10, SCREEN_HEIGHT, 45, 45);
		//CarbonFreezing = CF;
		//button ET(CarbonFreezing.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);
		//EmperorsThrone = ET;
		//button HEB(EmperorsThrone.rect.x + 45 + 10, SCREEN_HEIGHT, 45, 45);
		//HothEchoBase = HEB;

		//bgButtons.push_back(CarbonFreezing);
		//bgButtons.push_back(EmperorsThrone);
		//bgButtons.push_back(HothEchoBase);

		//mute
		soundOn = false;
		soundOff = false;
		button mIC (SCREEN_WIDTH - 25 - 5, SCREEN_HEIGHT - 25, 20, 20);
		muteIC = mIC;
		button mmIC (muteIC.rect.x - 25, SCREEN_HEIGHT - 25, 20, 20);
		muteMusicIC = mmIC;

		//back
		button B(0x0F, 0x0F, 0x0F, 0xFF, 3, SCREEN_HEIGHT - 25, 45, 25);
		back = B;
		SDL_Color color = {0xFF, 0xFF, 0xFF};
		back_text.loadFromRenderedText(RENDERER, FONT, "back", color);
	
		//customize
		button cu(0x0F, 0x0F, 0x0F, 0xFF, SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT - 25, 100, 25);
		customize = cu;
		color = {0xFF, 0xFF, 0xFF};
		customize_text.loadFromRenderedText(RENDERER, FONT, "customize", color);

		//battle
		button ba(0x0F, 0x0F, 0x0F, 0xFF, SCREEN_WIDTH / 2 + 70, SCREEN_HEIGHT - 25, 70, 25);
		battle = ba;
		color = {0xFF, 0xFF, 0xFF};
		battle_text.loadFromRenderedText(RENDERER, FONT, "battle", color);

		//bottom bar
		bottom.x = 0;
		bottom.y = SCREEN_HEIGHT - 28;
		bottom.w = SCREEN_WIDTH;
		bottom.h = 28;
	}

	//void handleSaberSelectMouseDown(int mosue_x, int mouse_y, Character custom);
	//void handleBackgroundSelectMouseDown(int mouse_x, int mouse_y);
	void handleMuteMouseDown(int mouse_x, int mouse_y);
	void handleMuteMusicMouseDown(int mouse_x, int mouse_y);
	void handleBackMouseDown(int mouse_x, int mouse_y);
	void handleCustomizeMouseDown(int mouse_x, int mouse_y);
	void handleBattleMouseDown(int mouse_x, int mouse_y);
	void handleSaberOnSwitchMouseDown(int mouse_x, int mouse_y, Character &custom);
	//void handleBackgroundSelectGUI(int mouse_x, int mouse_y);
	//void handleSaberSelectGUI(int mouse_x, int mouse_y);
	void handleGame(int mouse_x, int mouse_y, Character custom);
	void handleMouseDown(int mouse_x, int mouse_y, Character &custom);
	//void renderSaberSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, Character custom);
	//void renderBackgroundSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderMuteButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderMuteMusicButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderBackButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderCustomizeButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderBattleButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderBottomBar(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, Character custom, int bg);
	void close();
};

//void Simulator::handleSaberSelectMouseDown(int mouse_x, int mouse_y, Character custom)
//{
	//saber select panel clicks
//	if (saberSelect.visible)
//	{
//		for (int i = 0; i < saberButtons.size(); i++)
//		{
//			if (saberButtons.at(i).wasClicked(mouse_x, mouse_y))
//			{
//				if (i == 0)
//					main_char = Luke;
//				else if (i == 1)
//					main_char = Anakin;
//				else if (i == 2)
//					main_char = Vader;
//				else if (i == saberButtons.size() - 1)
//					main_char = custom;
//				switched = true; 
//				main_char.saber.on = false; 
//				soundOn = false;
//			}
//		}
//	}
//}

//void Simulator::handleBackgroundSelectMouseDown(int mouse_x, int mouse_y)
//{
//	if (bgSelect.visible)
//	{
//		for (int i = 0; i < bgButtons.size(); i++)
//		{
//			if (bgButtons.at(i).wasClicked(mouse_x, mouse_y))
//				background = i;
//		}
//	}
//}

void Simulator::handleMuteMouseDown(int mouse_x, int mouse_y)
{
	if (muteIC.wasClicked(mouse_x, mouse_y))
	{	
		mute = !mute;
		Mix_HaltChannel(-1);
	}
}

void Simulator::handleMuteMusicMouseDown(int mouse_x, int mouse_y)
{
	if (muteMusicIC.wasClicked(mouse_x, mouse_y))
	{	
		mute_music = !mute_music;
		Mix_HaltMusic();
	}
}

void Simulator::handleBackMouseDown(int mouse_x, int mouse_y)
{
	if (back.wasClicked(mouse_x, mouse_y))
	{	
		GAMES.at(0) = false;	
		SDL_ShowCursor(1);
		Mix_HaltChannel(-1);
		Mix_HaltMusic();
	}
}

void Simulator::handleCustomizeMouseDown(int mouse_x, int mouse_y)
{
	if (customize.wasClicked(mouse_x, mouse_y))
	{
		GAMES.at(0) = false;
		Mix_HaltChannel(-1);
		Mix_HaltMusic();
		GAMES.at(1) = true;
	}
}

void Simulator::handleBattleMouseDown(int mouse_x, int mouse_y)
{
	if (battle.wasClicked(mouse_x, mouse_y))
	{
		GAMES.at(0) = false;
		Mix_HaltChannel(-1);
		Mix_HaltMusic();
		GAMES.at(2) = true;
	}
}

void Simulator::handleSaberOnSwitchMouseDown(int mouse_x, int mouse_y, Character &custom)
{
	//if (!saberSelect.visible && !bgSelect.visible && !muteIC.wasClicked(mouse_x, mouse_y) && !back.wasClicked(mouse_x, mouse_y))
	if (!muteIC.wasClicked(mouse_x, mouse_y) && !back.wasClicked(mouse_x, mouse_y) &&
		!customize.wasClicked(mouse_x, mouse_y) && !battle.wasClicked(mouse_x, mouse_y) &&
		!muteMusicIC.wasClicked(mouse_x, mouse_y))	
		main_char.saber.on = !main_char.saber.on;
	
	//if (main_char.saber.on && !switched && !soundOn)
	if (main_char.saber.on && !soundOn)
	{
		if (!mute)
			Mix_PlayChannel(2, main_char.ON_SOUND, 0);
		soundOn = true;
		soundOff = false;
	}
	//else if (!main_char.saber.on && !switched && !soundOff && !saberSelect.visible && !bgSelect.visible && GAMES.at(0))
	else if (!main_char.saber.on && !soundOff && GAMES.at(0))
	{	
		if (!mute)
			Mix_PlayChannel(2, main_char.OFF_SOUND, 0);
		soundOff = true;
		soundOn = false;
	}
}

//void Simulator::handleBackgroundSelectGUI(int mouse_x, int mouse_y)
//{
//	if (mouse_x > bgSelect.rect.x && mouse_y > SCREEN_HEIGHT - 20)
//		bgSelect.visible = true;
//	if (bgSelect.visible)
//	{
//		if (bgSelect.rect.y > SCREEN_HEIGHT - 60)
//			bgSelect.rect.y -= 10;
//		for (int i = 0; i < bgButtons.size(); i++)
//		{
//			if (bgButtons.at(i).rect.y > SCREEN_HEIGHT - 50)
//				bgButtons.at(i).rect.y -= 10;
//		}
//		if (mouse_x < bgSelect.rect.x || mouse_y < SCREEN_HEIGHT - 60)
//			bgSelect.visible = false;
//	}
//	if (!bgSelect.visible)
//	{
//		if (bgSelect.rect.y < SCREEN_HEIGHT)
//			bgSelect.rect.y += 10;
//		for (int i = 0; i < bgButtons.size(); i++)
//		{
//			if (bgButtons.at(i).rect.y < SCREEN_HEIGHT)
//				bgButtons.at(i).rect.y += 10;
//		}
//	}
//}

//void Simulator::handleSaberSelectGUI(int mouse_x, int mouse_y)
//{
//	if (mouse_x < saberSelect.rect.w && mouse_y > SCREEN_HEIGHT - 20)
//		saberSelect.visible = true;
//	if (saberSelect.visible)
//	{
//		if (saberSelect.rect.y > SCREEN_HEIGHT - 60)
//			saberSelect.rect.y -= 10;
//		for (int i = 0; i < saberButtons.size(); i++)
//		{
//			if (saberButtons.at(i).rect.y > SCREEN_HEIGHT - 50)
//			{
//				saberButtons.at(i).rect.y -= 10;
//				saberIcons.at(i).rect.y -= 10;
//			}
//		}
//		if (mouse_x > saberSelect.rect.w || mouse_y < SCREEN_HEIGHT - 60)
//			saberSelect.visible = false;
//	}
//	if (!saberSelect.visible)
//	{
//		if (saberSelect.rect.y < SCREEN_HEIGHT)
//			saberSelect.rect.y += 10;
//		for (int i = 0; i < saberButtons.size(); i++)
//		{
//			if (saberButtons.at(i).rect.y < SCREEN_HEIGHT)
//			{
//				saberButtons.at(i).rect.y += 10;
//				saberIcons.at(i).rect.y += 10;
//			}
//		}
//	}
//}

void Simulator::handleGame(int mouse_x, int mouse_y, Character custom)
{
	//hide cursor
	//if (saberSelect.visible || bgSelect.visible)
	//	SDL_ShowCursor(1);
	//else
		SDL_ShowCursor(0);

	if (main_char != custom)
		main_char = custom;

	if (start && mouse_x == 0 && mouse_y == 0)
	{
		mouse_x = SCREEN_WIDTH / 2;
		mouse_y = 3 * SCREEN_HEIGHT / 4;
	}
	if (start && mouse_x != SCREEN_WIDTH / 2 && mouse_y != SCREEN_HEIGHT / 4)
		start = false;
	
	//switched = false;

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
	main_char.saber.handleSaberPosition(mouse_x, mouse_y, false);

	//lightsaber select gui
	//handleSaberSelectGUI(mouse_x, mouse_y);

	//background select gui
	//handleBackgroundSelectGUI(mouse_x, mouse_y);
}

void Simulator::handleMouseDown(int mouse_x, int mouse_y, Character &custom)
{
	//saber select panel clicks
	//handleSaberSelectMouseDown(mouse_x, mouse_y, custom);
	
	//background select panel clicks
	//handleBackgroundSelectMouseDown(mouse_x, mouse_y);
	
	//mute button click
	handleMuteMouseDown(mouse_x, mouse_y);
	handleMuteMusicMouseDown(mouse_x, mouse_y);

	//back button click
	handleBackMouseDown(mouse_x, mouse_y);

	//customize button click
	handleCustomizeMouseDown(mouse_x, mouse_y);

	//battle button click
	handleBattleMouseDown(mouse_x, mouse_y);

	//saber on switch and sound
	handleSaberOnSwitchMouseDown(mouse_x, mouse_y, custom);
}

//void Simulator::renderSaberSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, Character custom)
//{
//	SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0x0F);
//	SDL_RenderFillRect(RENDERER, &saberSelect.rect);
	//buttons
//	for (int i = 0; i < saberButtons.size(); i++)
//	{
//		SDL_SetRenderDrawColor(RENDERER, saberButtons.at(i).r, saberButtons.at(i).g, saberButtons.at(i).b, saberButtons.at(i).a);
//		if (saberSelect.visible && saberButtons.at(i).mouseHover(mouse_x, mouse_y, true))
//		{
//			SDL_RenderFillRect(RENDERER, &saberButtons.at(i).hover);
//			saberIcons.at(i).mouseHover(mouse_x, mouse_y, false);
//			if (i != saberButtons.size() - 1)
//				SDL_RenderCopyEx(RENDERER, hilts.at(i).mTexture, NULL, &saberIcons.at(i).hover,
//							 	 45, NULL, SDL_FLIP_NONE);	
//			else
//				SDL_RenderCopyEx(RENDERER, custom.hilt->mTexture, NULL, &saberIcons.at(i).hover,
//							 	 45, NULL, SDL_FLIP_NONE);
//		}
//		else if (saberSelect.visible && !saberButtons.at(i).mouseHover(mouse_x, mouse_y, true))
//		{
//			SDL_RenderFillRect(RENDERER, &saberButtons.at(i).rect);
//			saberIcons.at(i).mouseHover(mouse_x, mouse_y, false);
//			if (i != saberButtons.size() - 1)
//				SDL_RenderCopyEx(RENDERER, hilts.at(i).mTexture, NULL, &saberIcons.at(i).rect,
//							 	 45, NULL, SDL_FLIP_NONE);
//			else	
//				SDL_RenderCopyEx(RENDERER, custom.hilt->mTexture, NULL, &saberIcons.at(i).rect,
//							 	 45, NULL, SDL_FLIP_NONE);
//		}
//	}
//}

//void Simulator::renderBackgroundSelectGUI(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
//{
//	SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0xFF);
//	SDL_RenderFillRect(RENDERER, &bgSelect.rect);
//	//buttons
//	for (int i = 0; i < bgButtons.size(); i++)
//	{
//		if (bgSelect.visible && bgButtons.at(i).mouseHover(mouse_x, mouse_y, true))
//			SDL_RenderCopy(RENDERER, backgrounds.at(i).mTexture, NULL, &bgButtons.at(i).hover);
//		else if (bgSelect.visible && !bgButtons.at(i).mouseHover(mouse_x, mouse_y, true))
//			SDL_RenderCopy(RENDERER, backgrounds.at(i).mTexture, NULL, &bgButtons.at(i).rect);
//	}
//}

void Simulator::renderMuteButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
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

void Simulator::renderMuteMusicButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	if (mute_music)
		{
			if (muteMusicIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, muteMusicOn.mTexture, NULL, &muteMusicIC.hover);
			else if (!muteMusicIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, muteMusicOn.mTexture, NULL, &muteMusicIC.rect);
		}
		else if (!mute_music)
		{
			if (muteMusicIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, muteMusicOff.mTexture, NULL, &muteMusicIC.hover);
			else if (!muteMusicIC.mouseHover(mouse_x, mouse_y, true))
				SDL_RenderCopy(RENDERER, muteMusicOff.mTexture, NULL, &muteMusicIC.rect);
		}
}

void Simulator::renderBackButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
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

void Simulator::renderCustomizeButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0xFF);
	if (customize.mouseHover(mouse_x, mouse_y, true))
	{
		SDL_RenderFillRect(RENDERER, &customize.hover);
		SDL_RenderCopy(RENDERER, customize_text.mTexture, NULL, &customize.hover);
	}
	else if (!customize.mouseHover(mouse_x, mouse_y, true))
	{
		SDL_RenderFillRect(RENDERER, &customize.rect);
		SDL_RenderCopy(RENDERER, customize_text.mTexture, NULL, &customize.rect);
	}
}

void Simulator::renderBattleButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0xFF);
	if (battle.mouseHover(mouse_x, mouse_y, true))
	{
		SDL_RenderFillRect(RENDERER, &battle.hover);
		SDL_RenderCopy(RENDERER, battle_text.mTexture, NULL, &battle.hover);
	}
	else if (!battle.mouseHover(mouse_x, mouse_y, true))
	{
		SDL_RenderFillRect(RENDERER, &battle.rect);
		SDL_RenderCopy(RENDERER, battle_text.mTexture, NULL, &battle.rect);
	}
}

void Simulator::renderBottomBar(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	SDL_SetRenderDrawColor(RENDERER, 0x0F, 0x0F, 0x0F, 0xFF);
	SDL_RenderFillRect(RENDERER, &bottom);
}

void Simulator::renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, Character custom, int bg)
{
	//render everything
	//clear screen
	SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
	SDL_RenderClear(RENDERER);
	
	//background
	SDL_RenderCopy(RENDERER, backgrounds.at(bg).mTexture, NULL, &backgroundRect);
	
	//blade
	main_char.renderBlade(RENDERER);
	
	//hilt
	main_char.renderHilt(RENDERER);
	
	//saber select
	//renderSaberSelectGUI(RENDERER, mouse_x, mouse_y, custom);
			
	//background select
	//renderBackgroundSelectGUI(RENDERER, mouse_x, mouse_y);
			
	//bottom bar
	renderBottomBar(RENDERER, mouse_x, mouse_y);
	
	//mute button
	renderMuteButton(RENDERER, mouse_x, mouse_y);
	renderMuteMusicButton(RENDERER, mouse_x, mouse_y);

	//back button
	renderBackButton(RENDERER, mouse_x, mouse_y);
	
	//customize button
	renderCustomizeButton(RENDERER, mouse_x, mouse_y);
	
	//battle button
	renderBattleButton(RENDERER, mouse_x, mouse_y);

	//display
	SDL_RenderPresent(RENDERER);
}

void Simulator::close()
{
	back_text.free();
}

#endif
