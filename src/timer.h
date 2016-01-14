#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Timer
{
    private:
		//The clock time when the timer started
		double startTicks;
		//The ticks stored when the timer was paused
		double pausedTicks;
		//The timer status
		bool paused;
		bool started;
	public:
		//Initializes variables
		Timer();
		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();
		//Gets the timer's time
		double get_ticks();
		//Checks the status of the timer
		bool is_started();
		bool is_paused();
};

Timer::Timer()
{
	//Initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::start()
{
	//Start the timer
	started = true;
	//Unpause the timer
	paused = false;
	//Get the current clock time
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop()
{
	//stop the timer
	started = false;
	//unpause the timer
	paused = false;
	//clear tick variables
	startTicks = 0;
	pausedTicks = 0;
}

void Timer::pause()
{
	//if the timer is running and isn't already paused
	if(started && !paused)
	{
		//pause the timer
		paused = true;
		//calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::unpause()
{
	//if the timer is paused
	if(started && paused)
	{
		//unpause the timer
		paused = false;
		//reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;
		//reset the paused ticks
		pausedTicks = 0;
	}
}

double Timer::get_ticks()
{
	//if the timer is running
	if(started)
	{
		//if the timer is paused
		if(paused)
		{
			//return the number of ticks when the timer was paused
			return pausedTicks;
		}
		else
		{
			//return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}
	//if the timer isn't running
	return 0;
}

bool Timer::is_started()
{
	return started;
}

bool Timer::is_paused()
{
	return paused && started;
}

#endif
