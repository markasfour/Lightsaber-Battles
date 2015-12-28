#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif
#include "input.h"
#include "timer.h"
#include "texture.h"

#define PI 3.14

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
LTexture lightsaber;
LTexture blade;
LTexture bladetip;
LTexture glow;
LTexture glow2;
LTexture glowtip;
Mix_Chunk *ON_SOUND = NULL;
Mix_Chunk *OFF_SOUND = NULL;
Mix_Chunk *HUM = NULL;

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
	//load hilt images
	path << CurrentPath << "/content/lightsaber.png";
	lightsaber.loadFromFile(path.str(), RENDERER);
	if (lightsaber.mTexture == NULL)
		return false;	

	//clear stringstream
	path.str("");

	//load blade images
	path << CurrentPath << "/content/blade.png";
	blade.loadFromFile(path.str(), RENDERER);
	if (blade.mTexture == NULL)
		return false;	

	//clear stringstream
	path.str("");
	
	path << CurrentPath << "/content/bladetip.png";
	bladetip.loadFromFile(path.str(), RENDERER);
	if (bladetip.mTexture == NULL)
		return false;	

	//clear stringstream
	path.str("");

	//load sound effects 
	path << CurrentPath << "/content/SaberOn.wav";
	ON_SOUND = Mix_LoadWAV(path.str().c_str());
	if (ON_SOUND == NULL)
		return false;

	//clear stringstream
	path.str("");

	path << CurrentPath << "/content/SaberOff.wav";
	OFF_SOUND = Mix_LoadWAV(path.str().c_str());
	if (OFF_SOUND == NULL)
		return false;

	//clear stringstream
	path.str("");

	path << CurrentPath << "/content/Hum.wav";
	HUM = Mix_LoadWAV(path.str().c_str());
	if (HUM == NULL)
		return false;

	return true;
}

void close()
{
	//free loaded images
	lightsaber.free();
	blade.free();
	bladetip.free();

	//free loaded music

	//free loaded sound effects
	Mix_FreeChunk(ON_SOUND);
	ON_SOUND = NULL;
	Mix_FreeChunk(OFF_SOUND);
	OFF_SOUND = NULL;
	Mix_FreeChunk(HUM);
	HUM = NULL;

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


int main()
{
	if (!init())
		return -1;

	char CurrentPath[FILENAME_MAX];
	if (!GetCurrentDir(CurrentPath, sizeof(CurrentPath)))
     	 return -1;
	CurrentPath[sizeof(CurrentPath) - 1] = '\0';

	if (!loadMedia(CurrentPath))
		return -1;
	
	//main loop flag
	bool quit = false;

	//event handler
	SDL_Event e;

	//mouse location
	int mouse_x = 0; 
	int mouse_y = 0;

	//mouse click boolean
	bool click = false;

	//keyboard input handler
	Input input;

	//frame rate regulator
	Timer fps;

	//lightsaber rendering rectangle 
	SDL_Rect lightsaberRect;
	lightsaberRect.x = SCREEN_WIDTH / 2;
	lightsaberRect.y = 3 * SCREEN_HEIGHT / 4;
	lightsaberRect.w = 14;
	lightsaberRect.h = 60;

	//blade rendering rectangle
	SDL_Rect bladeRect;
	bladeRect.x = SCREEN_WIDTH / 2 - 4;
	bladeRect.y = 3 * SCREEN_HEIGHT / 4 - 3;
	bladeRect.w = 21;
	bladeRect.h = 3;
	
	//blade tip rendering rectangle
	SDL_Rect bladetipRect;
	bladetipRect.x = bladeRect.x;
	bladetipRect.y = bladeRect.y - 7;
	bladetipRect.w = 21;
	bladetipRect.h = 3;
	
	//lightsaber on/off
	bool on = false;
	
	//rotate blade
	bool rotate = false;
	double angle = 0;
	SDL_Point center;
	SDL_Point bladeCenter;
	SDL_Point bladetipCenter;
	
	//shift blade
	bool shift = false;

	//init position
	bool start = true;

	//Main loop
	while (!quit)
	{
		//start input handler
		input.beginNewFrame();
		
		//start the frame timer
		fps.start();
		
		//get mouse location
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
		if (start && mouse_x == 0 && mouse_y == 0)
		{
			mouse_x = SCREEN_WIDTH / 2;
			mouse_y = 3 * SCREEN_HEIGHT / 4;
		}
		if (start && mouse_x != SCREEN_WIDTH / 2 && mouse_y != SCREEN_HEIGHT / 4)
			start = false;

		//Handle events in the queue
		while (SDL_PollEvent(&e) != 0)
		{
			//user quits
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				on = !on;
				if (on)
					Mix_PlayChannel(-1, ON_SOUND, 0);
				if (!on)
					Mix_PlayChannel(-1, OFF_SOUND, 0);
			}
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.repeat == 0) 
					input.keyDownEvent(e);
			}
			else if (e.type == SDL_KEYUP) 
				input.keyUpEvent(e);
		}

		//handle key presses
		if (input.wasKeyPressed(SDL_SCANCODE_LSHIFT) || input.isKeyHeld(SDL_SCANCODE_LSHIFT) || 
			input.wasKeyPressed(SDL_SCANCODE_RSHIFT) || input.isKeyHeld(SDL_SCANCODE_RSHIFT) )
			shift = true;
		else if (input.wasKeyReleased(SDL_SCANCODE_LSHIFT) || input.wasKeyReleased(SDL_SCANCODE_RSHIFT))
			shift = false;
		if (input.wasKeyPressed(SDL_SCANCODE_LCTRL) || input.isKeyHeld(SDL_SCANCODE_LCTRL) || 
			input.wasKeyPressed(SDL_SCANCODE_RCTRL) || input.isKeyHeld(SDL_SCANCODE_RCTRL) )
			rotate = true;
		else if (input.wasKeyReleased(SDL_SCANCODE_LCTRL) || input.wasKeyReleased(SDL_SCANCODE_RCTRL))
			rotate = false;
		
		//handle music
		if (on)
			if (Mix_Playing(1) == 0)
				Mix_PlayChannel(1, HUM, 0);
		if (!on)
			Mix_HaltChannel(1);

		//get center points
		center = {lightsaberRect.x + (lightsaberRect.w / 2), lightsaberRect.y + (lightsaberRect.h / 2)};
		bladeCenter = {bladeRect.w / 2, bladeRect.h + (lightsaberRect.h / 2)};
		bladetipCenter = {bladetipRect.w / 2, bladetipRect.h + bladeRect.h + (lightsaberRect.h / 2)};

		//handle angle
		if (rotate)
		{
			if (mouse_x - center.x != 0)
				angle = atan2((double(center.y - mouse_y)) , (double(center.x - mouse_x))) * (180.0/PI) - 90;
			else if (mouse_y < center.y)
				angle = 0;
			else
				angle = 180;
		}
		
		//handle blade position
		if (!rotate)
		{
			bladeRect.x = mouse_x - 11;
			bladetipRect.x = bladeRect.x;
			if (shift)
			{
				bladeRect.y = mouse_y - 30 - bladeRect.h;
				bladetipRect.y = bladeRect.y - 3;
			}
		}
		
		//clear screen
		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
		SDL_RenderClear(RENDERER);
		
		//blade on
		if (on)
		{
			if (bladeRect.h < 300)
			{
				bladeRect.y -= 10 ;//* sin(angle + 90);
				bladeRect.h += 10;
				bladetipRect.y = bladeRect.y - 3;
			}
			SDL_RenderCopyEx(RENDERER, blade.mTexture, NULL, &bladeRect, 
							 angle, &bladeCenter, SDL_FLIP_NONE);
			SDL_RenderCopyEx(RENDERER, bladetip.mTexture, NULL, &bladetipRect, 
							 angle, &bladetipCenter, SDL_FLIP_NONE);
		}
		//blade off
		if (!on)
		{	
			if (bladeRect.h > 0) 
			{
				bladeRect.y += 4 ;//* sin(angle + 90);
				bladeRect.h -= 4;
				bladetipRect.y = bladeRect.y - 3;
				SDL_RenderCopyEx(RENDERER, blade.mTexture, NULL, &bladeRect, 
					   			 angle, &bladeCenter, SDL_FLIP_NONE);
				SDL_RenderCopyEx(RENDERER, bladetip.mTexture, NULL, &bladetipRect, 
								 angle, &bladetipCenter, SDL_FLIP_NONE);
			}
		}

		//draw hilt
		if (!rotate)
		{
			lightsaberRect.x = mouse_x - 8;
			if (shift)
				lightsaberRect.y = mouse_y - 30;
		}
		
		SDL_RenderCopyEx(RENDERER, lightsaber.mTexture, NULL, &lightsaberRect,
						 angle, NULL, SDL_FLIP_NONE);
		
		//update the screen
		SDL_RenderPresent(RENDERER);
		
		//cap the frame rate
		if (fps.get_ticks() < 1000/FRAMES_PER_SECOND)
			SDL_Delay((1000/FRAMES_PER_SECOND) - fps.get_ticks());
	}

	close();
	return 0;
}
