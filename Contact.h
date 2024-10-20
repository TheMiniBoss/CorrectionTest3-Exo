#pragma once
#include "Discussion.h"
#include "UserInteract.h"
#include "TimerSystem.h"

struct Contact
{
	string name;
	string description;
	string password;
	Discussion discussion;

	Contact()
	{
		name = "Unknown";
		description = "Unknown";
		password = "Unknown";
		discussion = Discussion();
	}
	Contact(const string& _name, const string& _password, const string& _description = "Bonjour tout le monde !")
	{
		name = _name;
		description = _description;
		password = _password;
		discussion = Discussion();
	}

	void Introduce()
	{
		DISPLAY("======================", true);
		DISPLAY(name, true);
		DISPLAY(description, true);
		DISPLAY("======================", true);
	}
	void ShowDiscussion()
	{
		discussion.Display();
	}
	void SendMessage(Contact* _sender)
	{
		system("cls");
		CLEAR;
		Contact* _owner = _sender ? _sender : this;
		const string& _text = RetrieveText("Que voulez-vous écrire ?", true);
		const Time& _time = GetTime();
		const Message& _message = Message(_owner, _text, _time);
		discussion.AddMessage(_message);
	}
};