#pragma once
#include "Time.h"

struct Contact;

struct Message
{
	Contact* owner;
	string text;
	Time time;

	Message();
	Message(Contact* _owner, const string& _text, const Time& _time);
	void Display() const;
};