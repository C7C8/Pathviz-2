#include <SDL2/SDL.h>

class Timer
{
public:
	Timer();
	unsigned int getTime() const;                   //!< Gets the time since the timer was started.
	void start();                                   //!< Starts the timer.
	void stop();                                    //!< Stops the timer.
	void reset();                                   //!< Resets the timer, erasing accumulated time and setting the start time to now.
	void setInterval(unsigned int ms);              //!< Sets the time period/interval.
	bool hasIntervalPassed() const;                 //!< Checks if the time period/interval has passed yet.
	bool hasIntervalPassed(unsigned int ms) const;  //!< Allows checking for time interval regardless of set interval.
private:
	unsigned int startTime;
	unsigned int timeInterval;
	unsigned int timeSum;
};
