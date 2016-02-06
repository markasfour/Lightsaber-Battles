#ifndef PANEL_H
#define PANEL_H

struct panel
{
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
	}

	//vertical
	panel(int x, int y, int n, int b_dim, int sp, bool v)
	{
		visible = false;
		rect.x = x;
		rect.y = y;
		rect.h = sp + (n * (sp + b_dim));
		rect.w = b_dim + (2 * sp);

		//determine side closest to
		if (rect.x > SCREEN_WIDTH / 2)
			side = "right";
		else
			side = "left";
	}

	//hide/show vertical panel
	void move(double time, vector <button> &Buttons, vector <button> &Icons)
	{
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
					for (int i = 0; i < Icons.size(); i++)
						Icons.at(i).rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
				}
			}
			else
			{
				if (rect.x >= 0)
				{
					rect.x -= (rect.w) / 10;
					for (int i = 0; i < Buttons.size(); i++)
						Buttons.at(i).rect.x -= (rect.w) / (time * FRAMES_PER_SECOND);
					for (int i = 0; i < Icons.size(); i++)
						Icons.at(i).rect.x -= (rect.w) / (time * FRAMES_PER_SECOND);
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
					for (int i = 0; i < Icons.size(); i++)
						Icons.at(i).rect.x -= (rect.w) / (time * FRAMES_PER_SECOND);
				}
			}
			else
			{
				if (rect.w < 0 + rect.w)
				{	
					rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
					for (int i = 0; i < Buttons.size(); i++)
						Buttons.at(i).rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
					for (int i = 0; i < Icons.size(); i++)
						Icons.at(i).rect.x += (rect.w) / (time * FRAMES_PER_SECOND);
				}
			}
		}
	}
};

#endif
