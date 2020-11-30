#include "TimeSystem.h"

static const tmElements_t factoryTime = { // January 1st 2019 at 12:00pm
	0,	// seconds
	0,	// minutes
	12,	// hour
	2,	// day of week (sunday is 1)
	1,	// day
	1,	// month
	49 	// offset from 1970
};

void TimeSystem::SetTime(tmElements_t t)
{
	time_t time_to_set = makeTime(t);
	setTime(time_to_set);
}

void TimeSystem::SetTime(int hour, int minute)
{
	setTime(hour, minute, 0, 1, 1, 2020);
}

tmElements_t TimeSystem::GetTime()
{
	tmElements_t t;
	breakTime(now(), t);

	return (t);
}

void TimeSystem::ResetToFactoryTime()
{
	SetTime(factoryTime);
}