#pragma once
#include "Macro.h"

struct Time
{
	int hours;
	int minutes;
	int seconds;

	string ToString() const
	{
		return to_string(hours) + "h "
			+ to_string(minutes) + "min "
			+ to_string(seconds) + "sec";
	}
};