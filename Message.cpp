#include "Message.h"
#include "Contact.h"

Message::Message()
{
	owner = nullptr;
	text = "";
	time = Time();
}

Message::Message(Contact* _owner, const string& _text, const Time& _time)
{
	owner = _owner;
	text = _text;
	time = _time;
}

void Message::Display() const
{
	DISPLAY("Message de " + owner->name + ": " + text + " (" + time.ToString() + ")", true);
}