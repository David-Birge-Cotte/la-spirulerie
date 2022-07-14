#ifndef TIME_SYSTEM_H
#define TIME_SYSTEM_H

#include <Arduino.h>
#include <TimeLib.h>

/*
** Simple helper functions to change and get time
*/

namespace TimeSystem
{
	void SetTime(tmElements_t t);
	void SetTime(int hour, int minute);
	tmElements_t GetTime();
	void ResetToFactoryTime();
};

#endif