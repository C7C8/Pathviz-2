#include "Timer.h"

Timer::Timer()
{
	timeSum = 0;
}
unsigned int Timer::getTime() const
{
	return (SDL_GetTicks() - startTime) + timeSum;
}
void Timer::start()
{
	startTime = SDL_GetTicks();
}
void Timer::stop()
{
	timeSum += SDL_GetTicks() - startTime;
}
void Timer::reset()
{
	timeSum = 0;
	startTime = SDL_GetTicks();
}
void Timer::setInterval(unsigned int ms)
{
	timeInterval = ms;
}
bool Timer::hasIntervalPassed() const
{
	if (getTime() >= timeInterval)
		return true;
	return false;
}
bool Timer::hasIntervalPassed(unsigned int ms) const
{
	if (getTime() >= ms)
		return true;
	return false;
}
