#ifndef BUTTON_H
#define BUTTON_H

struct button
{
	SDL_Rect rect;
	SDL_Rect hover;
	Uint8 r = 0xFF;
	Uint8 g = 0xFF;
	Uint8 b = 0xFF;
	Uint8 a = 0xFF;
	int type;

	button(){}
	
	button(int x, int y, int w, int h)
	{
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		type = 1;
	}
	button(Uint8 R, Uint8 G, Uint8 B, Uint8 A, int x, int y, int w, int h)
	{
		r = R;
		g = G;
		b = B;
		a = A;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		type = 2;
	}
	bool mouseHover(int mouse_x, int mouse_y, bool special)
	{
		if (type == 2 || special)
		{
			if (mouse_x > rect.x && mouse_x < (rect.x + rect.w))
			{
				if (mouse_y > rect.y && mouse_y < (rect.y + rect.h))
				{
					cout << mouse_y << "," << rect.y << "," << rect.y + rect.h << endl;
					hover.x = rect.x - 2.5;
					hover.y = rect.y - 2.5;
					hover.w = rect.w + 5;
					hover.h = rect.h + 5;
					return true;
				}
				return false;
			}
			return false;
		}
		else if (type == 1)
		{
			hover.x = rect.x - 2.5;
			hover.y = rect.y - 2.5;
			hover.w = rect.w + 5;
			hover.h = rect.h + 5;
			return true;
		}
	}
	bool wasClicked(int mouse_x, int mouse_y)
	{
		if (mouse_x > rect.x && mouse_x < (rect.x + rect.w))
		{
			if (mouse_y > rect.y && mouse_y < (rect.y + rect.h))
				return true;
			return false;
		}
		return false;
	}
};

#endif
