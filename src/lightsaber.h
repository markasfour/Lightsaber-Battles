#ifndef LIGHTSABER_H
#define LIGHTSABER_H

#define PI 3.14159265

struct Saber
{
	SDL_Rect hilt;
	SDL_Rect blade;
	SDL_Rect bladetip;
	bool on;
	double angle;
	double prev_angle;
	bool swing;
	SDL_Point center;
	SDL_Point hiltCenter;
	SDL_Point bladeCenter;
	SDL_Point bladetipCenter;
	
	Saber()
	{
		hilt.w = 15;
		hilt.h = 75;
		blade.w = 21;
		blade.h = 1;
		bladetip.w = 21;
		bladetip.h = 7;
		on = false;
		angle = 0;
		prev_angle = 0;
		swing = false;
	}

	void setCenterPoints()
	{
		hiltCenter = {hilt.w / 2, hilt.h / 2};
		bladeCenter = {blade.w / 2, (blade.h) + (hilt.h / 2)};
		bladetipCenter = {bladetip.w / 2, bladetip.h + blade.h + (hilt.h / 2)};
	}
	
	void handleAngle(SDL_Point center, int mouse_x, int mouse_y)
	{
		prev_angle = angle;
		if (mouse_x - center.x != 0)
			angle = atan2((double(center.y - mouse_y)) , (double(center.x - mouse_x))) * (180.0/PI) - 90;
		else if (mouse_y < center.y)
			angle = 0;
		else
			angle = 180;
		angle *= 2;
	}

	void handleSwing()
	{
		swing = false;
		if (abs(prev_angle - angle) > 15)
			swing = true;
		else
			swing = false;
	}
	
	void handleOnOffSwitch(bool switched)
	{
		//blade on
		if (on)
		{
			if (blade.h < 250 && !switched)
			{
				blade.h += 10;
				blade.y -= (10 * sin((angle + 90) * (PI/180)));
				blade.x -= (10 * cos((angle + 90) * (PI/180)));
			}
			else
				blade.h = 250;
		}
		//blade off
		if (!on)
		{	
			if (blade.h > 0 && !switched) 
			{
				blade.h -= 4;
				blade.y += (4 * sin((angle + 90) * (PI/180)));
				blade.x += (4 * cos((angle + 90) * (PI/180)));
			}
			else
				blade.h = 0;
		}
	}

	void handleBladePosition(int mouse_x, int mouse_y, bool switched)
	{
		//handle blade position
		blade.x = mouse_x - (blade.w / 2) + (6 * cos((angle + 90) * (PI/180)));
		blade.y = mouse_y - (hilt.h / 2) - (blade.h - (6 * sin((angle + 90) * (PI/180)))); 
		handleOnOffSwitch(switched);
	}

	void handleBladeTipPosition(int mouse_x, int mouse_y)
	{
		//handle blade tip position
		bladetip.x = blade.x;
		bladetip.y = blade.y - bladetip.h;
	}
	
	void handleHiltPosition(int mouse_x, int mouse_y)
	{
		//hilt position
		hilt.x = mouse_x - (hilt.w / 2);
		hilt.y = mouse_y - (hilt.h / 2);
	}

	void handleSaberPosition(int mouse_x, int mouse_y, bool switched)
	{
		handleBladePosition(mouse_x, mouse_y, switched);
		handleBladeTipPosition(mouse_x, mouse_y);
		handleHiltPosition(mouse_x, mouse_y);
	}
};

#endif
