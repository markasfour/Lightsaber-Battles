#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

struct Character
{
	string name;
	LTexture *hilt;
	LTexture *blade;
	LTexture *bladetip;
	LTexture *bladebase;
	Mix_Chunk *ON_SOUND;
	Mix_Chunk *OFF_SOUND;
	Mix_Chunk *HUM;
	Saber saber;
	double depth;

	Character()
	{
		name = "Luke";
		hilt = &hilts.at(0);
		blade = &blades.at(0);
		bladetip = &bladetips.at(0);
		bladebase = &bladebases.at(0);
		ON_SOUND = ON_SOUND_1;
		OFF_SOUND = OFF_SOUND_1;
		HUM = HUM_1;
		depth = 0;
	}
	Character(string n)
	{
		name = n;
		if (n == "Luke")
		{
			hilt = &hilts.at(0);
			blade = &blades.at(0);
			bladetip = &bladetips.at(0);
			bladebase = &bladebases.at(0);
			ON_SOUND = ON_SOUND_1;
			OFF_SOUND = OFF_SOUND_1;
			HUM = HUM_1;
			depth = 0;
		}
		else if (name == "Anakin")
		{
			hilt = &hilts.at(1);
			blade = &blades.at(1);
			bladetip = &bladetips.at(1);
			bladebase = &bladebases.at(1);
			ON_SOUND = ON_SOUND_2;
			OFF_SOUND = OFF_SOUND_2;
			HUM = HUM_2;
			depth = 0;
		}
		else if (name == "Vader")
		{
			hilt = &hilts.at(2);
			blade = &blades.at(2);
			bladetip = &bladetips.at(2);
			bladebase = &bladebases.at(2);
			ON_SOUND = ON_SOUND_3;
			OFF_SOUND = OFF_SOUND_3;
			HUM = HUM_3;
			depth = 0;
		}
	}
	Character(double d)
	{
		depth = d;
		saber.hilt.w *= d * (3.0/4);
		saber.hilt.h *= d * 3.0/4;
		saber.blade.w *= d * 3.0/4;
		saber.blade.h *= d * 3.0/4;
		saber.bladetip.w *= d * 3.0/4;
		saber.bladetip.h *= d * 3.0/4;
		saber.bladebase.w *= d * 3.0/4;
		saber.bladebase.h *= d * 3.0/4;
		hilt = &hilts.at(rand() % hilts.size());
		int x = rand() % blades.size();
		blade = &blades.at(x);
		bladetip = &bladetips.at(x);
		bladebase = &bladebases.at(x);
		ON_SOUND = ON_SOUND_3;
		OFF_SOUND = OFF_SOUND_3;
		HUM = HUM_3;
	}
	Character(const Character &c)
	{
		name = c.name;
		hilt = c.hilt;
		blade = c.blade;
		bladetip = c.bladetip;
		bladebase = c.bladebase;
		ON_SOUND = c.ON_SOUND;
		OFF_SOUND = c.OFF_SOUND;
		HUM = c.HUM;
		saber = c.saber;
		depth = c.depth;
	}
	bool operator!=(const Character &r)
	{
		if (hilt != r.hilt || blade != r.blade ||
			bladetip != r.bladetip || bladebase != r.bladebase ||
			HUM != r.HUM)
				return true;
		return false;
	}	

	void zoomIn() //from depth <1 to 1 (going into the screen)
	{
		if (depth >= 1)
		{
			depth = 1;
			return;
		}
		else
		{
			depth += .13333333;
			if (depth >= 1)
				depth = 1;
			saber.hilt.w = 15.0 - ((15.0 - (15.0 * 0.75)) * depth);
			saber.hilt.h = 75.0 - ((75.0 - (75.0 * 0.75)) * depth);
			saber.blade.w = 21.0 - ((21.0 - (21.0 * 0.75)) * depth);
			saber.blade.h = 250.0 - ((250.0 - (250.0 * 0.75)) * depth);
			saber.bladetip.w = 21.0 - ((21.0 - (21.0 * 0.75)) * depth);
			saber.bladetip.h = 7.0  - ((7.0 - (7.0 * 0.75)) * depth);
			saber.bladebase.w = 21.0 - ((21.0 - (21.0 * 0.75)) * depth);
			saber.bladebase.h = 7.0  - ((7.0 - (7.0 * 0.75)) * depth);
		}
	}

	void zoomOut() //from depth >0 to 0 (going out of the screen)
	{
		if (depth <= 0)
		{
			depth = 0;
			return;
		}
		else
		{
			depth -= .13333333;
			if (depth <= 0)
				depth = 0;
			saber.hilt.w = 15.0 - ((15.0 - (15.0 * 0.75)) * depth);
			saber.hilt.h = 75.0 - ((75.0 - (75.0 * 0.75)) * depth);
			saber.blade.w = 21.0 - ((21.0 - (21.0 * 0.75)) * depth);
			saber.blade.h = 250.0 - ((250.0 - (250.0 * 0.75)) * depth);
			saber.bladetip.w = 21.0 - ((21.0 - (21.0 * 0.75)) * depth);
			saber.bladetip.h = 7.0  - ((7.0 - (7.0 * 0.75)) * depth);
			saber.bladebase.w = 21.0 - ((21.0 - (21.0 * 0.75)) * depth);
			saber.bladebase.h = 7.0  - ((7.0 - (7.0 * 0.75)) * depth);
		}
	}

	void handleHumSound(bool mute)
	{
		if (saber.on && !mute)
		{
			Mix_Volume(1, MIX_MAX_VOLUME);	
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
			SDL_RenderCopyEx(RENDERER, blade->mTexture, NULL, &saber.blade, 
						 	 saber.angle, &saber.bladeCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, bladetip->mTexture, NULL, &saber.bladetip, 
						 	 saber.angle, &saber.bladetipCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, bladebase->mTexture, NULL, &saber.bladebase, 
						 	 saber.angle, &saber.bladebaseCenter, SDL_FLIP_NONE);
		}
		if (!saber.on && saber.blade.h > 0)
		{
			SDL_RenderCopyEx(RENDERER, blade->mTexture, NULL, &saber.blade, 
						 	 saber.angle, &saber.bladeCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, bladetip->mTexture, NULL, &saber.bladetip, 
						 	 saber.angle, &saber.bladetipCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, bladebase->mTexture, NULL, &saber.bladebase, 
						 	 saber.angle, &saber.bladebaseCenter, SDL_FLIP_NONE);
		}
	}

	void renderHilt(SDL_Renderer *RENDERER)
	{
		SDL_RenderCopyEx(RENDERER, hilt->mTexture, NULL, &saber.hilt,
						 saber.angle, &saber.hiltCenter, SDL_FLIP_NONE);
	}
};
#endif
