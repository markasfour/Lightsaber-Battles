#ifndef PANEL_H
#define PANEL_H

struct panel
{
	int spacing;
	bool visible;
	SDL_Rect rect;
	string side;

	panel(){}
	
	//horizontal
	panel(int x, int y, int n, int b_dim, int sp)
	{
		visible = false;
		rect.x = x;
		rect.y = y;
		rect.w = sp + (n * (sp + b_dim));
		rect.h = b_dim + (2 * sp);
	
		spacing = sp;
	}

	//vertical
	panel(int x, int y, int n, int b_dim, int sp, bool v)
	{
		visible = false;
		rect.x = x;
		rect.y = y;
		rect.h = sp + (n * (sp + b_dim));
		rect.w = b_dim + (2 * sp);

		spacing = sp;

		//determine side closest to
		if (rect.x > SCREEN_WIDTH / 2)
			side = "right";
		else
			side = "left";
	}

	//hide/show vertical panel
	void move(double time, vector <button> &Buttons, vector <button> &Icons)
	{
		bool noIcons = false;
		if (Icons.size() == 0)
			noIcons = true;
		
		//hide
		if (!visible)
		{
			//moves for duration of time
			if (side == "right")
			{	
				if (rect.x < SCREEN_WIDTH)
				{
					rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
					for (int i = 0; i < Buttons.size(); i++)
						Buttons.at(i).rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
					if (!noIcons)
					{
						for (int i = 0; i < Icons.size(); i++)
							Icons.at(i).rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
					}
				}
			}
			else
			{
				if (rect.x + rect.w >= 0)
				{
					rect.x -= (rect.w) / (time * FRAMES_PER_SECOND);
					for (int i = 0; i < Buttons.size(); i++)
						Buttons.at(i).rect.x -= (rect.w) / (time * FRAMES_PER_SECOND);
					if (!noIcons)
					{
						for (int i = 0; i < Icons.size(); i++)
							Icons.at(i).rect.x -= (rect.w) / (time * FRAMES_PER_SECOND);
					}
				}
				else
				{
					rect.x = 0 - rect.w;
					for (int i = 0; i < Buttons.size(); i++)
						Buttons.at(i).rect.x = rect.x + spacing;
					if (!noIcons)
					{
						for (int i = 0; i < Icons.size(); i++)
							Icons.at(i).rect.x = rect.x + spacing;
					}
				}
			}
		}
		//show
		else
		{
			//moves for duration of time
			if (side == "right")
			{
				if (rect.x > SCREEN_WIDTH - rect.w)
				{	
					rect.x -= (rect.w) / (time * FRAMES_PER_SECOND);
					for (int i = 0; i < Buttons.size(); i++)
						Buttons.at(i).rect.x -= (rect.w) / (time * FRAMES_PER_SECOND);
					if (!noIcons)
					{
						for (int i = 0; i < Icons.size(); i++)
							Icons.at(i).rect.x -= (rect.w) / (time * FRAMES_PER_SECOND);
					}
				}
			}
			else
			{
				if (rect.x + rect.w < 0 + rect.w)
				{	
					rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
					for (int i = 0; i < Buttons.size(); i++)
						Buttons.at(i).rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
					if (!noIcons)
					{
						for (int i = 0; i < Icons.size(); i++)
							Icons.at(i).rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
					}
				}
				else
				{
					rect.x = 0;
					for (int i = 0; i < Buttons.size(); i++)
						Buttons.at(i).rect.x = rect.x + spacing;
					if (!noIcons)
					{
						for (int i = 0; i < Icons.size(); i++)
							Icons.at(i).rect.x = rect.x + spacing;
					}
				}
			}
		}
	}
};

#endif
