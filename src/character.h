#ifndef CHARACTER_H
#define CHARACTER_H

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
	Saber saber;

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
		saber = c.saber;
	}

	void handleHumSound(bool mute)
	{
		if (saber.on && !mute)
		{
			Mix_Volume(1, MIX_MAX_VOLUME/2);	//play at half volume
			if (Mix_Playing(1) == 0)
				Mix_PlayChannel(1, HUM, 0);
		}
		if (!saber.on || mute)
			Mix_HaltChannel(1);
	}

	void handleSwingSound(bool mute)
	{
		if (saber.swing && saber.on && !mute)
		{
			if (Mix_Playing(3) == 0)
			{	
				Mix_Volume(3, MIX_MAX_VOLUME/3);	//play at third of volume
				if (abs(saber.prev_angle - saber.angle) <= 25)
					Mix_PlayChannel(3, SWING_SOUND_2, 0);
			}
			if (Mix_Playing(4) == 0)
			{
				Mix_Volume(4, MIX_MAX_VOLUME/3);	//play at third of volume
				if (abs(saber.prev_angle - saber.angle) > 25)
					Mix_PlayChannel(4, SWING_SOUND_1, 0);
			}
		}
		else if (mute)
		{
			Mix_HaltChannel(3);
			Mix_HaltChannel(4);
		}
	}

	void renderBlade(SDL_Renderer *RENDERER)
	{
		if (saber.on)
		{
			SDL_RenderCopyEx(RENDERER, blade.mTexture, NULL, &saber.blade, 
						 	 saber.angle, &saber.bladeCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, bladetip.mTexture, NULL, &saber.bladetip, 
						 	 saber.angle, &saber.bladetipCenter, SDL_FLIP_NONE);
		}
		if (!saber.on && saber.blade.h > 0)
		{
			SDL_RenderCopyEx(RENDERER, blade.mTexture, NULL, &saber.blade, 
						 	 saber.angle, &saber.bladeCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, bladetip.mTexture, NULL, &saber.bladetip, 
						 	 saber.angle, &saber.bladetipCenter, SDL_FLIP_NONE);
		}
	}

	void renderHilt(SDL_Renderer *RENDERER)
	{
		SDL_RenderCopyEx(RENDERER, hilt.mTexture, NULL, &saber.hilt,
						 saber.angle, &saber.hiltCenter, SDL_FLIP_NONE);
	}
};
#endif
