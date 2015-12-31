#ifndef HELPER_H
#define HELPER_H

#include "texture.h"

using namespace std;

//PROTOTYPES
//starts SDL and creates window
bool init();
//loads media
bool loadMedia(string CurrentPath);
//Frees media and shuts SDL down
void close();

//GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FRAMES_PER_SECOND = 60;

SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDERER = NULL;
SDL_Surface *SCREENSURFACE = NULL;
TTF_Font *FONT = NULL;

LTexture muteOn;
LTexture muteOff;
LTexture hilt_Luke;
LTexture hilt_Anakin;
LTexture hilt_Vader;
LTexture blade_G;
LTexture blade_B;
LTexture blade_R;
LTexture bladetip_G;
LTexture bladetip_B;
LTexture bladetip_R;
LTexture LukeIcon;
LTexture AnakinIcon;
LTexture VaderIcon;

Mix_Chunk *ON_SOUND_1 = NULL;
Mix_Chunk *ON_SOUND_2 = NULL;
Mix_Chunk *ON_SOUND_3 = NULL;
Mix_Chunk *OFF_SOUND_1 = NULL;
Mix_Chunk *OFF_SOUND_2 = NULL;
Mix_Chunk *OFF_SOUND_3 = NULL;
Mix_Chunk *HUM_1 = NULL;
Mix_Chunk *HUM_2 = NULL;
Mix_Chunk *HUM_3 = NULL;

bool init()
{
	//init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		//set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled." << endl;
		}
		
		//create window
		WINDOW = SDL_CreateWindow( "Lightsaber", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (WINDOW == NULL)
		{
			cout << "Window could not be created. SDL_Error: " << SDL_GetError() << endl;
			return false;
		}
		else
		{
			//create renderer for window
			RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
			if (RENDERER == NULL)
			{
				cout << "Renderer could not be created. SDL_Error: " << SDL_GetError() << endl;
				return false;
			}
			else
			{
				//init renderer color
				SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);

				//init PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize. SDL_image Error: " << IMG_GetError() << endl;
					return false;
				}

				//Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
					cout << "SDL_mixer could not initialize. SDL_mixer Error: " << Mix_GetError() << endl;
					return false;
				}

				//Initialize SDL_ttf
				//if (!TTF_Init())
				//{
				//	cout << "SDL_ttf could not initialize. SDL_ttf Error: " << TTF_GetError() << endl;
				//	return false;
				//}

				//get window surface
				SCREENSURFACE = SDL_GetWindowSurface(WINDOW);
			}
		}
	}
	return true;
}

bool loadMedia(string CurrentPath)
{
	stringstream path;
	
	//load mute icons
	path << CurrentPath << "/content/mute_sfx.png";
	muteOn.loadFromFile(path.str(), RENDERER);
	if (muteOn.mTexture == NULL)
		return false;	
	
	//clear stringstream
	path.str("");

	path << CurrentPath << "/content/unmute_sfx.png";
	muteOff.loadFromFile(path.str(), RENDERER);
	if (muteOff.mTexture == NULL)
		return false;	
	
	//clear stringstream
	path.str("");

	//load hilt images
	path << CurrentPath << "/content/Luke_hilt.png";
	hilt_Luke.loadFromFile(path.str(), RENDERER);
	if (hilt_Luke.mTexture == NULL)
		return false;	
	
	//clear stringstream
	path.str("");

	path << CurrentPath << "/content/Anakin_hilt.png";
	hilt_Anakin.loadFromFile(path.str(), RENDERER);
	if (hilt_Anakin.mTexture == NULL)
		return false;	
	
	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/Vader_hilt.png";
	hilt_Vader.loadFromFile(path.str(), RENDERER);
	if (hilt_Vader.mTexture == NULL)
		return false;	
	
	//clear stringstream
	path.str("");

	//load blade images
	path << CurrentPath << "/content/blade_G.png";
	blade_G.loadFromFile(path.str(), RENDERER);
	if (blade_G.mTexture == NULL)
		return false;	

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/blade_B.png";
	blade_B.loadFromFile(path.str(), RENDERER);
	if (blade_B.mTexture == NULL)
		return false;	

	//clear stringstream
	path.str("");

	path << CurrentPath << "/content/blade_R.png";
	blade_R.loadFromFile(path.str(), RENDERER);
	if (blade_R.mTexture == NULL)
		return false;	

	//clear stringstream
	path.str("");

	path << CurrentPath << "/content/bladetip_G.png";
	bladetip_G.loadFromFile(path.str(), RENDERER);
	if (bladetip_G.mTexture == NULL)
		return false;	

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/bladetip_B.png";
	bladetip_B.loadFromFile(path.str(), RENDERER);
	if (bladetip_B.mTexture == NULL)
		return false;	

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/bladetip_R.png";
	bladetip_R.loadFromFile(path.str(), RENDERER);
	if (bladetip_R.mTexture == NULL)
		return false;	

	//clear stringstream
	path.str("");
	
	//load sound effects 
	path << CurrentPath << "/content/SaberOn_1.wav";
	ON_SOUND_1 = Mix_LoadWAV(path.str().c_str());
	if (ON_SOUND_1 == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/SaberOn_2.wav";
	ON_SOUND_2 = Mix_LoadWAV(path.str().c_str());
	if (ON_SOUND_2 == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/SaberOn_3.wav";
	ON_SOUND_3 = Mix_LoadWAV(path.str().c_str());
	if (ON_SOUND_3 == NULL)
		return false;

	//clear stringstream
	path.str("");

	path << CurrentPath << "/content/SaberOff_1.wav";
	OFF_SOUND_1 = Mix_LoadWAV(path.str().c_str());
	if (OFF_SOUND_1 == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/SaberOff_2.wav";
	OFF_SOUND_2 = Mix_LoadWAV(path.str().c_str());
	if (OFF_SOUND_2 == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/SaberOff_3.wav";
	OFF_SOUND_3 = Mix_LoadWAV(path.str().c_str());
	if (OFF_SOUND_3 == NULL)
		return false;

	//clear stringstream
	path.str("");

	path << CurrentPath << "/content/Hum_1.wav";
	HUM_1 = Mix_LoadWAV(path.str().c_str());
	if (HUM_1 == NULL)
		return false;
	
	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/Hum_2.wav";
	HUM_2 = Mix_LoadWAV(path.str().c_str());
	if (HUM_2 == NULL)
		return false;
	
	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/Hum_3.wav";
	HUM_3 = Mix_LoadWAV(path.str().c_str());
	if (HUM_3 == NULL)
		return false;

	return true;
}

void close()
{
	//free loaded images
	hilt_Luke.free();
	hilt_Anakin.free();
	hilt_Vader.free();
	blade_G.free();
	blade_B.free();
	blade_R.free();
	bladetip_G.free();
	bladetip_B.free();
	bladetip_R.free();

	//free loaded music

	//free loaded sound effects
	Mix_FreeChunk(ON_SOUND_1);
	ON_SOUND_1 = NULL;
	Mix_FreeChunk(ON_SOUND_2);
	ON_SOUND_2 = NULL;
	Mix_FreeChunk(ON_SOUND_3);
	ON_SOUND_3 = NULL;
	Mix_FreeChunk(OFF_SOUND_1);
	OFF_SOUND_1 = NULL;
	Mix_FreeChunk(OFF_SOUND_2);
	OFF_SOUND_2 = NULL;
	Mix_FreeChunk(OFF_SOUND_3);
	OFF_SOUND_3 = NULL;
	Mix_FreeChunk(HUM_1);
	HUM_1 = NULL;
	Mix_FreeChunk(HUM_2);
	HUM_2 = NULL;
	Mix_FreeChunk(HUM_3);
	HUM_3 = NULL;
	
	//free loaded fonts

	//Destroy window
	SDL_DestroyRenderer(RENDERER);
	RENDERER = NULL;
	SDL_DestroyWindow(WINDOW);
	WINDOW = NULL;

	//Quit SDL
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

#endif 
