#ifndef CHARACTER_H
#define CHARACTER_H

#include "helper.h"
using namespace std;

struct Character
{
	LTexture hilt;
	LTexture blade;
	LTexture bladetip;
	Mix_Chunk *ON_SOUND;
	Mix_Chunk *OFF_SOUND;
	Mix_Chunk *HUM;

	Character()
	{
		hilt = hilt_Luke;
		blade = blade_G;
		bladetip = bladetip_G;
		ON_SOUND = ON_SOUND_1;
		OFF_SOUND = OFF_SOUND_1;
		HUM = HUM_1;
	}
	Character(string name)
	{
		if (name == "Luke")
		{
			hilt = hilt_Luke;
			blade = blade_G;
			bladetip = bladetip_G;
			ON_SOUND = ON_SOUND_1;
			OFF_SOUND = OFF_SOUND_1;
			HUM = HUM_1;
		}
		else if (name == "Anakin")
		{
			hilt = hilt_Anakin;
			blade = blade_B;
			bladetip = bladetip_B;
			ON_SOUND = ON_SOUND_2;
			OFF_SOUND = OFF_SOUND_2;
			HUM = HUM_2;
		}
		else if (name == "Vader")
		{
			hilt = hilt_Vader;
			blade = blade_R;
			bladetip = bladetip_R;
			ON_SOUND = ON_SOUND_3;
			OFF_SOUND = OFF_SOUND_3;
			HUM = HUM_3;
		}
	}
	Character(const Character &c)
	{
		hilt = c.hilt;
		blade = c.blade;
		bladetip = c.bladetip;
		ON_SOUND = c.ON_SOUND;
		OFF_SOUND = c.OFF_SOUND;
		HUM = c.HUM;
	}
};
#endif
