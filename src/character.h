#ifndef CHARACTER_H
#define CHARACTER_H

#include "helper.h"
using namespace std;

struct Character
{
	string name;
	LTexture hilt;
	LTexture blade;
	LTexture bladetip;
	Mix_Chunk *ON_SOUND;
	Mix_Chunk *OFF_SOUND;
	Mix_Chunk *HUM;

	Character()
	{
		name = "Luke";
		hilt = hilts.at(0);
		blade = blade_G;
		bladetip = bladetip_G;
		ON_SOUND = ON_SOUND_1;
		OFF_SOUND = OFF_SOUND_1;
		HUM = HUM_1;
	}
	Character(string n)
	{
		name = n;
		if (n == "Luke")
		{
			hilt = hilts.at(0);
			blade = blade_G;
			bladetip = bladetip_G;
			ON_SOUND = ON_SOUND_1;
			OFF_SOUND = OFF_SOUND_1;
			HUM = HUM_1;
		}
		else if (name == "Anakin")
		{
			hilt = hilts.at(1);
			blade = blade_B;
			bladetip = bladetip_B;
			ON_SOUND = ON_SOUND_2;
			OFF_SOUND = OFF_SOUND_2;
			HUM = HUM_2;
		}
		else if (name == "Vader")
		{
			hilt = hilts.at(2);
			blade = blade_R;
			bladetip = bladetip_R;
			ON_SOUND = ON_SOUND_3;
			OFF_SOUND = OFF_SOUND_3;
			HUM = HUM_3;
		}
	}
	Character(const Character &c)
	{
		name = c.name;
		hilt = c.hilt;
		blade = c.blade;
		bladetip = c.bladetip;
		ON_SOUND = c.ON_SOUND;
		OFF_SOUND = c.OFF_SOUND;
		HUM = c.HUM;
	}
};
#endif
