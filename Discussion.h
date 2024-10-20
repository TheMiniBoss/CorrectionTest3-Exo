#pragma once
#include "Message.h"
#include "UserInteract.h"

struct Discussion
{
	Message* messages;
	u_int messagesCount;
	u_int scrollIndex;

	Discussion()
	{
		messages = nullptr;
		messagesCount = 0;
		scrollIndex = 0;
	}
	~Discussion() //TODO remove
	{
		//delete[] messages;
	}

	void Display()
	{
		if (messagesCount == 0)
		{
			DISPLAY("Il n'y a aucun message !", true);
			return;
		}

		AskAction();
	}
	void AskAction()
	{
		const string _actions[] =
		{
			"Descendre",
			"Supprimer",
			"Monter",
			"Retour",
		};
		const u_int& _actionsCount = sizeof(_actions) / sizeof(const string);

		u_int _index;
		do
		{
			messages[scrollIndex].Display();
			_index = RetrieveNumber(_actions, _actionsCount, false);

		} while (ExecuteAction(_index));
	}
	bool ExecuteAction(const u_int& _index)
	{
		switch (_index)
		{
		case 1:
			Scroll(-1);
			break;

		case 2:
			RemoveMessageByIndex(scrollIndex);
			if (messagesCount <= 0) return false;
			Scroll(-1);
			break;

		case 3:
			Scroll(1);
			break;

		case 4:
			return false;

		default:
			DISPLAY("ERREUR => Index invalide !", true);
			break;
		}

		return true;
	}
	void Scroll(const int _scrollFactor)
	{
		const string& _suffix = _scrollFactor > 0 ? "suivant" : "précédent";
		DISPLAY("Message " + _suffix + ": ", false);

		scrollIndex += _scrollFactor;
		scrollIndex = scrollIndex < 0 ? 0 : scrollIndex;
		scrollIndex = scrollIndex >= messagesCount ? messagesCount - 1 : scrollIndex;
	}

	void AddMessage(const Message& _message)
	{
		Message* _newArray = new Message[messagesCount + 1];

		for (u_int _index = 0; _index < messagesCount; _index++)
		{
			_newArray[_index] = messages[_index];
		}
		_newArray[messagesCount] = _message;

		delete[] messages;
		messages = _newArray;
		messagesCount++;
	}
	void RemoveMessageByIndex(const u_int& _indexToRemove)
	{
		Message* _newArray = new Message[--messagesCount];
		bool _hasSkip = false;

		for (u_int _index = 0; _index < messagesCount; _index++)
		{
			if (!_hasSkip && _index == _indexToRemove)
			{
				_hasSkip = true;
			}
			_newArray[_index] = messages[_index + _hasSkip];
		}

		delete[] messages;
		messages = _newArray;
	}
	bool IsValidIndex(const u_int& _index)
	{
		return _index >= 0 && _index < messagesCount;
	}
};