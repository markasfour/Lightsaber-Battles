#ifndef SPARK_H
#define SPARK_H

#define PI 3.14159265

struct spark 
{	
	SDL_Rect rect;
	SDL_Point center;
	SDL_Point sparkCenter;
	double angle;
	Timer t;
	int life;

	spark ()
	{ }
	spark (SDL_Point c)
	{
		center.x = c.x;
		center.y = c.y;

		rect.w = rand() % 4 + 2;
		rect.h = 1;
		rect.x = rand() % 10 - 5 + center.x;
		rect.y = rand() % 10 - 5 + center.y;

		sparkCenter.x = rect.w / 2;
		sparkCenter.y = rect.h / 2;

		angle = atan2((double(center.y - (rect.y + sparkCenter.y))) , (double(center.x - (rect.x + sparkCenter.x)))) * (180.0/PI);

		t.start();

		life = rand() % 2 + 1 * 100;
	}

	void move()
	{
		if (t.get_ticks() < life)
		{
			rect.x += 4 * cos(angle);
			rect.y += 4 * sin(angle);
		}
		else
			t.stop();
	}

};

#endif
