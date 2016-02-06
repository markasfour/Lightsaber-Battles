#ifndef BATTLE_H
#define BATTLE_H

struct Battle
{
	//background rendering rectangle
	SDL_Rect backgroundRect;

	//player center
	SDL_Point center;
	SDL_Point op_center;
	
	//start
	bool start;
	bool rReady;
	bool rFight;
	LTexture ready;
	LTexture fight;
	Timer ready_time;
	Timer wait;
	Timer fight_time;

	//characters
	Character main_char;
	Character opponent;
	SDL_Rect op_rect;
	SDL_Point op_point;
	SDL_Point temp_point;

	//attack
	bool main_char_attack;
	bool main_char_zoomIn;
	bool main_char_zoomOut;
	bool opponent_attack;
	bool opponent_zoomIn;
	bool opponent_zoomOut;
	Timer attack_timer;
	vector <int> attack_times;
	SDL_Point clash;
	SDL_Rect clashRect;
	bool clash_render;

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

		start = true;
	
		op_rect.x = SCREEN_WIDTH / 2 - 100;
		op_rect.y = SCREEN_HEIGHT / 2 - 150;
		op_rect.w = 200;
		op_rect.h = 300;
	
		op_point.x = rand() % op_rect.w + op_rect.x;
		op_point.y = rand() % op_rect.h + op_rect.y;
		temp_point = op_point;

		Character o(1.00);
		opponent = o;
		
		for (int i = 0; i < 100; i++)
		{
			int x = rand() % 3 + 1;
			attack_times.push_back(x * 1000);
		}

		rReady = false;
		rFight = false;
		SDL_Color color = {0xFF, 0xFF, 0xFF};
		ready.loadFromRenderedText(RENDERER, FONT, "Ready", color);
		color = {0xFF, 0xFF, 0xFF};
		fight.loadFromRenderedText(RENDERER, FONT, "Fight", color);

		main_char_attack = false;
		main_char_zoomIn = false;
		main_char_zoomOut = false;
		opponent_attack = false;
		opponent_zoomIn = false;
		opponent_zoomOut = false;
	
		clash_render = false;
		clashRect.x = 0;
		clashRect.y = 0;
		clashRect.w = 100;
		clashRect.h = 100;

		mute = false;
		soundOn = false;
		soundOff = false;
		button mIC (SCREEN_WIDTH - 25, 5, 20, 20);
		muteIC = mIC;

		button B(0x0F, 0x0F, 0x0F, 0xFF, 0, 0, 50, 30);
		back = B;
		color = {0xFF, 0xFF, 0xFF};
		back_text.loadFromRenderedText(RENDERER, FONT, "back", color);
	}
	
	bool Intersection (SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4);
	bool bladeIntersect();
	void handleBlock();
	void handleAttack(int mouse_x, int mouse_y);
	void handleMuteMouseDown(int mouse_x, int mouse_y);
	void handleBackMouseDown(int mouse_x, int mouse_y);
	void handleMouseDown(int mouse_x, int mouse_y);
	void handleStart(Character custom);
	void handleOpponentAttack(int mouse_x, int mouse_y);
	void handleOpponent(int mouse_x, int mouse_y);
	void handleGame(int mouse_x, int mouse_y, Character custom);
	void renderClash(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderMuteButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderBackButton(SDL_Renderer *RENDERER, int mouse_x, int mouse_y);
	void renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, Character custom, int bg);
};

bool Battle::Intersection (SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4)
{
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
 	 
	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) 
		return false;
 	 
	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 	 
	// Check if the x and y coordinates are within both lines
	if ( x < min(x1, x2) || x > max(x1, x2) ||
		x < min(x3, x4) || x > max(x3, x4) ) 
		return false;
	if ( y < min(y1, y2) || y > max(y1, y2) ||
		y < min(y3, y4) || y > max(y3, y4) ) 
		return false;
 	 
	// Return the point of intersection
	clashRect.x = x - (clashRect.w / 2);
	clashRect.y = y - (clashRect.h / 2);
	return true;
}

bool Battle::bladeIntersect()
{
	SDL_Point p1 = main_char.saber.edge_top;
	SDL_Point p2 = main_char.saber.edge_bot;	
	SDL_Point p3 = opponent.saber.edge_top;
	SDL_Point p4 = opponent.saber.edge_bot;
	if (Intersection(p1, p2, p3, p4))
		return true;
	else
		return false;		
}

void Battle::handleBlock()
{
	if (main_char_attack || opponent_attack)
	{
		if (bladeIntersect())
		{
			clash_render = true;
			//cout << "BLOCKED" << endl;
		}
		else
		{
			clash_render = false;
			//cout << "HIT" << endl;
		}
	}
}

void Battle::handleAttack(int mouse_x, int mouse_y)
{
	if (!muteIC.wasClicked(mouse_x, mouse_y) && !back.wasClicked(mouse_x, mouse_y))
	{
		int x = rand() % HITS.size();
		if (!mute)
			Mix_PlayChannel(-1, HITS.at(x), 0);
		main_char_attack = true;
		main_char_zoomIn = true;
	}
}

void Battle::handleMuteMouseDown(int mouse_x, int mouse_y)
{
	if (muteIC.wasClicked(mouse_x, mouse_y))
	{	
		mute = !mute;
		Mix_HaltChannel(-1);
	}
}

void Battle::handleBackMouseDown(int mouse_x, int mouse_y)
{
	if (back.wasClicked(mouse_x, mouse_y))
	{	
		GAMES.at(2) = false;	
		SDL_ShowCursor(1);
		Mix_HaltChannel(-1);
		start = true;
		op_point.x = rand() % op_rect.w + op_rect.x;
		op_point.y = rand() % op_rect.h + op_rect.y;
		opponent.hilt = &hilts.at(rand() % hilts.size());
		int x = rand() % blades.size();
		opponent.saber.blade.h = 0;
		opponent.blade = &blades.at(x);
		opponent.bladetip = &bladetips.at(x);
		opponent.saber.on = false;
	}
}

void Battle::handleMouseDown(int mouse_x, int mouse_y)
{
	//main char attack
	handleAttack(mouse_x, mouse_y);
	
	//mute button click
	handleMuteMouseDown(mouse_x, mouse_y);
	
	//back button click
	handleBackMouseDown(mouse_x, mouse_y);
}

void Battle::handleStart(Character custom)
{
	if (start)
	{
		//get center points
		center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
		op_center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
		main_char.saber.setCenterPoints();
		opponent.saber.setCenterPoints();

		//handle angle
		main_char.saber.handleAngle(center, SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 4);
		opponent.saber.handleAngle(op_center, op_point.x, op_point.y);
		opponent.saber.angle /= 2;

		main_char.saber.handleSaberPosition(SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 4, false);
		opponent.saber.handleSaberPosition(op_point.x, op_point.y, false);
		
		if (!ready_time.is_started())
		{
			ready_time.start();
			main_char = custom;
			main_char.saber.on = false;
			rReady = true;
			SDL_ShowCursor(0);
		}
		if (ready_time.get_ticks() > 1500)
		{
			rReady = false;
			
			if (!wait.is_started())
				wait.start();
			
			main_char.saber.on = true;
			main_char.saber.handleOnOffSwitch(false);
			if (!mute && !Mix_Playing(2) && wait.get_ticks() < 2000)
				Mix_PlayChannel(2, main_char.ON_SOUND, 0);
			if (wait.get_ticks() > 2000)
			{
				opponent.saber.on = true;
				opponent.saber.handleOnOffSwitch(false);	
				if (!mute && !Mix_Playing(2) && wait.get_ticks() < 2500)
					Mix_PlayChannel(2, opponent.ON_SOUND, 0);
			}
		}
		if (wait.get_ticks() > 3000)
		{
			rFight = true;
			if (!fight_time.is_started())
				fight_time.start();	
		}
		if (fight_time.get_ticks() > 1500)
		{
			rFight = false;
			start = false;
			ready_time.stop();
			wait.stop();
			fight_time.stop();
			attack_timer.start();		//opponent attack timer
		}
	}
}

void Battle::handleOpponentAttack(int mouse_x, int mouse_y)
{
	if (attack_timer.get_ticks() >= attack_times.at(0))
	{
		int x = rand() % HITS.size();
		if (!mute)
			Mix_PlayChannel(-1, HITS.at(x), 0);
		opponent_attack = true;
		opponent_zoomOut = true;
		attack_timer.stop();
		attack_timer.start();
	}
	if (attack_times.size() == 0)
	{
		for (int i = 0; i < 100; i++)
		{
			int x = rand() % 5 + 1;
			attack_times.push_back(x * 1000);
		}
	}
}

void Battle::handleOpponent(int mouse_x, int mouse_y)
{
	if (op_point.x == temp_point.x && op_point.y == temp_point.y)
	{
		temp_point.x = rand() % op_rect.w + op_rect.x;
		temp_point.y = rand() % op_rect.h + op_rect.y;
	}
	if (op_point.x != temp_point.x || op_point.y != temp_point.y)
	{
		if (op_point.x < temp_point.x)
			op_point.x++;
		else if (op_point.x > temp_point.x)
			op_point.x--;
		if (op_point.y < temp_point.y)
			op_point.y++;
		else if (op_point.y > temp_point.y)
			op_point.y--;
	}

	//handle opponent attack
	handleOpponentAttack(mouse_x, mouse_y);
	if (opponent_attack)
	{
		if (opponent.depth > 0 && opponent_zoomOut)
		{
			opponent.zoomOut();
			if (opponent.depth <= 0)
			{
				opponent_zoomOut = false;
				opponent_zoomIn = true;
			}
		}
		else if (opponent.depth < 1 && opponent_zoomIn)
		{	
			opponent.zoomIn();
			if (opponent.depth >= 1)
			{
				opponent_zoomIn = false;
				opponent_attack = false;
			}
		}
	}
}

void Battle::handleGame(int mouse_x, int mouse_y, Character custom)
{
	//handle start
	handleStart(custom);
		
	if (!start)	
	{
		handleBlock();

		//handle main_char attack
		if (main_char_attack)
		{
			if (main_char.depth < 1 && main_char_zoomIn)
			{
				main_char.zoomIn();
				if (main_char.depth >= 1)
				{
					main_char_zoomIn = false;
					main_char_zoomOut = true;
				}
			}
			else if (main_char.depth > 0 && main_char_zoomOut)
			{	
				main_char.zoomOut();
				if (main_char.depth <= 0)
				{
					main_char_zoomOut = false;
					main_char_attack = false;
				}
			}
		}
		
		//handle opponent
		handleOpponent(mouse_x, mouse_y);
		
		//clash image
		if (!main_char_attack && !opponent_attack)
			clash_render = false;

		//handle hum sound 
		main_char.handleHumSound(mute);
		opponent.handleHumSound(mute);

		//get center points
		center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
		op_center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
		main_char.saber.setCenterPoints();
		opponent.saber.setCenterPoints();

		//move background
		backgroundRect.x = (-1 * (((center.x - mouse_x) / double(center.x)) * ((SCREEN_WIDTH - backgroundRect.w))/2)) - ((backgroundRect.w - SCREEN_WIDTH)/2);
		backgroundRect.y = (((center.y - mouse_y) / double(center.y)) * (SCREEN_HEIGHT - backgroundRect.h)/2);

		//handle angle
		main_char.saber.handleAngle(center, mouse_x, mouse_y);
		opponent.saber.handleAngle(op_center, op_point.x, op_point.y);
		opponent.saber.angle /= 2;

		//handle swing
		main_char.saber.handleSwing();
		main_char.handleSwingSound(mute);

		//handle saber position
		main_char.saber.handleSaberPosition(mouse_x, mouse_y, false);
		opponent.saber.handleSaberPosition(op_point.x, op_point.y, false);
	}
}

void Battle::renderClash(SDL_Renderer *RENDERER, int mouse_x, int mouse_y)
{
	if (clash_render)
	{
		SDL_Point c_center = {clashRect.w / 2, clashRect.h / 2};
		SDL_RenderCopyEx(RENDERER, CLASH.mTexture, NULL, &clashRect,
						 (main_char.saber.angle + opponent.saber.angle) / 2, &c_center, SDL_FLIP_NONE);
	}
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

void Battle::renderEverything(SDL_Renderer *RENDERER, int mouse_x, int mouse_y, Character custom, int bg)
{
	//render everything
	//clear screen
	SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
	SDL_RenderClear(RENDERER);
	
	//background
	SDL_RenderCopy(RENDERER, backgrounds.at(bg).mTexture, NULL, &backgroundRect);

	//opponent blade
	opponent.renderBlade(RENDERER);
	
	//opponent hilt
	opponent.renderHilt(RENDERER);

	//main char blade
	main_char.renderBlade(RENDERER);
	
	//main char hilt
	main_char.renderHilt(RENDERER);
	
	//render clash
	renderClash(RENDERER, mouse_x, mouse_y);

	//mute button
	renderMuteButton(RENDERER, mouse_x, mouse_y);

	//back button
	renderBackButton(RENDERER, mouse_x, mouse_y);
	
	//test
	if (DEBUG)
	{
		//opponent rect
		SDL_SetRenderDrawColor(RENDERER, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(RENDERER, &op_rect);
	
		//blade edge lines
		SDL_SetRenderDrawColor(RENDERER, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(RENDERER, &opponent.saber.blade);
		SDL_RenderDrawRect(RENDERER, &main_char.saber.blade);

		SDL_Point p1 = main_char.saber.edge_top;
		SDL_Point p2 = main_char.saber.edge_bot;
		SDL_SetRenderDrawColor(RENDERER, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawLine(RENDERER, p1.x, p1.y, p2.x, p2.y);
		
		SDL_Point p3 = opponent.saber.edge_top;
		SDL_Point p4 = opponent.saber.edge_bot;
		SDL_SetRenderDrawColor(RENDERER, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawLine(RENDERER, p3.x, p3.y, p4.x, p4.y);

		cout << main_char.saber.blade.h << endl;
		cout << opponent.saber.blade.h << endl;
		cout << endl;
	}

	//ready
	SDL_Rect r;
	r.x = SCREEN_WIDTH / 2 - 100;
	r.y = 0;
	r.w = 200;
	r.h = 100;
	if (rReady)
		SDL_RenderCopy(RENDERER, ready.mTexture, NULL, &r);
	if (rFight)
		SDL_RenderCopy(RENDERER, fight.mTexture, NULL, &r);

	//display
	SDL_RenderPresent(RENDERER);
}

#endif
