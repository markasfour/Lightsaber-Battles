#ifndef PANEL_H
#define PANEL_H

struct panel
{
	bool visible;
	SDL_Rect rect;

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
	}
};

#endif
