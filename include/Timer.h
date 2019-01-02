#ifndef TIMER_H
#define TIMER_H

#include "global.h"

class Timer {
    private:
		Uint32 mStartTicks;
		Uint32 mPausedTicks;
		bool mPaused;
		bool mStarted;
    public:
		Timer();
		void start();
		void stop();
		void pause();
		void unpause();
		Uint32 getTicks();
		bool isStarted();
		bool isPaused();
};

#endif