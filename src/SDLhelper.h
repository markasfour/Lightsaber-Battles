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

bool mute = false;
bool mute_music = false;

SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDERER = NULL;
SDL_Surface *SCREENSURFACE = NULL;
TTF_Font *FONT = NULL;

LTexture menuBackground;
vector <LTexture> backgrounds (3);
LTexture muteOn;
LTexture muteOff;
LTexture muteMusicOn;
LTexture muteMusicOff;
vector <LTexture> hilts (6);
vector <LTexture> blades (7);
vector <LTexture> bladetips (7);
vector <LTexture> bladebases (7);
LTexture hilt_icon;
LTexture background_icon;
LTexture color_icon;
LTexture HEART;
LTexture CLASH;
LTexture SPARK;
LTexture DAMAGE;

Mix_Chunk *ON_SOUND_1 = NULL;
Mix_Chunk *ON_SOUND_2 = NULL;
Mix_Chunk *ON_SOUND_3 = NULL;
Mix_Chunk *OFF_SOUND_1 = NULL;
Mix_Chunk *OFF_SOUND_2 = NULL;
Mix_Chunk *OFF_SOUND_3 = NULL;
Mix_Chunk *HUM_1 = NULL;
Mix_Chunk *HUM_2 = NULL;
Mix_Chunk *HUM_3 = NULL;
Mix_Chunk *SWING_SOUND_1 = NULL;
Mix_Chunk *SWING_SOUND_2 = NULL;
Mix_Chunk *CLICK_SOUND = NULL;
Mix_Chunk *BATTLE_START = NULL;
vector <Mix_Chunk*> HITS(7);

Mix_Music *MENU_THEME = NULL;
Mix_Music *CUSTOMIZE_THEME = NULL;
Mix_Music *BATTLE_THEME = NULL;

bool DEBUG = false;

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
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize. SDL_ttf Error: " << TTF_GetError() << endl;
					return false;
				}

				//get window surface
				SCREENSURFACE = SDL_GetWindowSurface(WINDOW);
			}
		}
	}
	return true;
}

bool loadImage(LTexture &x, string CurrentPath, string file)
{
	stringstream path;
	path << CurrentPath << file;
	x.loadFromFile(path.str(), RENDERER);
	if (x.mTexture == NULL)
		return false;	
	return true;
}

bool loadMedia(string CurrentPath)
{
	stringstream path;
	
	//load fonts
	path << CurrentPath << "/content/Starjedi.ttf";
	FONT = TTF_OpenFont(path.str().c_str(), 200);
	if( FONT == NULL )
		return false;

	//clear stringstream
	path.str("");	
	
	//load backgrounds
	if (!loadImage(menuBackground, CurrentPath, "/content/MenuBackground.jpg"))
		return false;

	if (!loadImage(backgrounds.at(0), CurrentPath, "/content/background1.jpg"))
		return false;
	
	if (!loadImage(backgrounds.at(1), CurrentPath, "/content/background2.jpg"))
		return false;
	
	if (!loadImage(backgrounds.at(2), CurrentPath, "/content/background3.jpg"))
		return false;

	//load mute icons
	if (!loadImage(muteOn, CurrentPath, "/content/mute_sfx.png"))
		return false;	
	
	if (!loadImage(muteOff, CurrentPath, "/content/unmute_sfx.png"))
		return false;	

	if (!loadImage(muteMusicOn, CurrentPath, "/content/mute_music.png"))
		return false;

	if (!loadImage(muteMusicOff, CurrentPath, "/content/unmute_music.png"))
		return false;

	//load hilt images
	if (!loadImage(hilts.at(0), CurrentPath, "/content/Luke_hilt.png"))
		return false;	

	if (!loadImage(hilts.at(1), CurrentPath, "/content/Anakin_hilt.png"))
		return false;	
	
	if (!loadImage(hilts.at(2), CurrentPath, "/content/Vader_hilt.png"))
		return false;	

	if (!loadImage(hilts.at(3), CurrentPath, "/content/Sidius_hilt.png"))
		return false;

	if (!loadImage(hilts.at(4), CurrentPath, "/content/Windu_hilt.png"))
		return false;

	if (!loadImage(hilts.at(5), CurrentPath, "/content/Fisto_hilt.png"))
		return false;

	//load blade images
	if (!loadImage(blades.at(0), CurrentPath, "/content/blade_G.png"))
		return false;
	
	if (!loadImage(blades.at(1), CurrentPath, "/content/blade_B.png"))
		return false;
	
	if (!loadImage(blades.at(2), CurrentPath, "/content/blade_R.png"))
		return false;

	if (!loadImage(blades.at(3), CurrentPath, "/content/blade_P.png"))
		return false;

	if (!loadImage(blades.at(4), CurrentPath, "/content/blade_Y.png"))
		return false;

	if (!loadImage(blades.at(5), CurrentPath, "/content/blade_W.png"))
		return false;

	if (!loadImage(blades.at(6), CurrentPath, "/content/blade_BL.png"))
		return false;
	
	//tips
	if (!loadImage(bladetips.at(0), CurrentPath, "/content/bladetip_G.png"))
		return false;
	
	if (!loadImage(bladetips.at(1), CurrentPath, "/content/bladetip_B.png"))
		return false;

	if (!loadImage(bladetips.at(2), CurrentPath, "/content/bladetip_R.png"))
		return false;

	if (!loadImage(bladetips.at(3), CurrentPath, "/content/bladetip_P.png"))
		return false;

	if (!loadImage(bladetips.at(4), CurrentPath, "/content/bladetip_Y.png"))
		return false;

	if (!loadImage(bladetips.at(5), CurrentPath, "/content/bladetip_W.png"))
		return false;

	if (!loadImage(bladetips.at(6), CurrentPath, "/content/bladetip_BL.png"))
		return false;

	//bases
	if (!loadImage(bladebases.at(0), CurrentPath, "/content/bladebase_G.png"))
		return false;
	
	if (!loadImage(bladebases.at(1), CurrentPath, "/content/bladebase_B.png"))
		return false;

	if (!loadImage(bladebases.at(2), CurrentPath, "/content/bladebase_R.png"))
		return false;

	if (!loadImage(bladebases.at(3), CurrentPath, "/content/bladebase_P.png"))
		return false;

	if (!loadImage(bladebases.at(4), CurrentPath, "/content/bladebase_Y.png"))
		return false;

	if (!loadImage(bladebases.at(5), CurrentPath, "/content/bladebase_W.png"))
		return false;

	if (!loadImage(bladebases.at(6), CurrentPath, "/content/bladebase_BL.png"))
		return false;
	
	//icons
	if (!loadImage(hilt_icon, CurrentPath, "/content/hilt_icon.png"))
		return false;	

	if (!loadImage(background_icon, CurrentPath, "/content/background_icon.png"))
		return false;

	if (!loadImage(color_icon, CurrentPath, "/content/color_icon.png"))
		return false;

	//heart
	if (!loadImage(HEART, CurrentPath, "/content/heart.png"))
		return false;

	//spark
	if (!loadImage(SPARK , CurrentPath, "/content/white_pixel.png"))
		return false;

	//clash
	if (!loadImage(CLASH, CurrentPath, "/content/clash.png"))
		return false;	

	//damage
	if (!loadImage(DAMAGE, CurrentPath, "/content/damage.png"))
		return false;	

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

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/swing1.wav";
	SWING_SOUND_1 = Mix_LoadWAV(path.str().c_str());
	if (SWING_SOUND_1 == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/swing2.wav";
	SWING_SOUND_2 = Mix_LoadWAV(path.str().c_str());
	if (SWING_SOUND_2 == NULL)
		return false;
	
	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/hit_1.wav";
	HITS.at(0) = Mix_LoadWAV(path.str().c_str());
	if (HITS.at(0) == NULL)
		return false;
	
	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/hit_2.wav";
	HITS.at(1) = Mix_LoadWAV(path.str().c_str());
	if (HITS.at(1) == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/hit_3.wav";
	HITS.at(2) = Mix_LoadWAV(path.str().c_str());
	if (HITS.at(2) == NULL)
		return false;
	
	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/hit_4.wav";
	HITS.at(3) = Mix_LoadWAV(path.str().c_str());
	if (HITS.at(3) == NULL)
		return false;
	
	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/hit_5.wav";
	HITS.at(4) = Mix_LoadWAV(path.str().c_str());
	if (HITS.at(4) == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/hit_6.wav";
	HITS.at(5) = Mix_LoadWAV(path.str().c_str());
	if (HITS.at(5) == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/hit_7.wav";
	HITS.at(6) = Mix_LoadWAV(path.str().c_str());
	if (HITS.at(6) == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/click_sound.wav";
	CLICK_SOUND = Mix_LoadWAV(path.str().c_str());
	if (CLICK_SOUND == NULL)
		return false;

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/battle_start.wav";
	BATTLE_START = Mix_LoadWAV(path.str().c_str());
	if (BATTLE_START == NULL)
		return false;
	
	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/menu_theme.wav";
	MENU_THEME = Mix_LoadMUS(path.str().c_str());
	if (MENU_THEME == NULL)
		return false;

	//clear stringstream
	path.str("");
		
	path << CurrentPath << "/content/customize_theme.mp3";
	CUSTOMIZE_THEME = Mix_LoadMUS(path.str().c_str());
	if (CUSTOMIZE_THEME == NULL)
		return false;
	
	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/battle_theme.wav";
	BATTLE_THEME = Mix_LoadMUS(path.str().c_str());
	if (BATTLE_THEME == NULL)
		return false;

	return true;
}

void close()
{
	//free loaded images
	menuBackground.free();
	for (int i = 0; i < backgrounds.size(); i++)
		backgrounds.at(i).free();
	muteOn.free();
	muteOff.free();
	muteMusicOn.free();
	muteMusicOff.free();
	for (int i = 0; i < hilts.size(); i++)
		hilts.at(i).free();
	for (int i = 0; i < blades.size(); i++)
		blades.at(i).free();
	for (int i = 0; i < bladetips.size(); i++)
		bladetips.at(i).free();
	for (int i = 0; i < bladebases.size(); i++)
		bladebases.at(i).free();
	hilt_icon.free();
	background_icon.free();
	color_icon.free();
	HEART.free();
	SPARK.free();
	CLASH.free();
	DAMAGE.free();

	//free loaded music
	Mix_FreeMusic(MENU_THEME);
	MENU_THEME = NULL;
	Mix_FreeMusic(CUSTOMIZE_THEME);
	CUSTOMIZE_THEME = NULL;
	Mix_FreeMusic(BATTLE_THEME);
	BATTLE_THEME = NULL;

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
	Mix_FreeChunk(SWING_SOUND_1);
	SWING_SOUND_1 = NULL;
	Mix_FreeChunk(SWING_SOUND_2);
	SWING_SOUND_2 = NULL;
	Mix_FreeChunk(CLICK_SOUND);
	CLICK_SOUND = NULL;
	Mix_FreeChunk(BATTLE_START);
	BATTLE_START = NULL;

	//free loaded fonts
	TTF_CloseFont(FONT);
	FONT = NULL;	

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
