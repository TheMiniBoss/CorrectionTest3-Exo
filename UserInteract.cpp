#include "UserInteract.h"
#include "Macro.h"

void Display(const string& _text, const bool _endl)
{
	DISPLAY(_text, _endl);
}

void Display(const string* _texts, const u_int& _textsCount, const bool _endl)
{
	DISPLAY("==============", true);
	for (u_int _index = 0; _index < _textsCount; _index++)
	{
		const string& _indexText = _endl ? to_string(_index + 1) + "- " : "";
		Display(_indexText + _texts[_index], _endl);

		if (!_endl)
		{
			if (_index < _textsCount - 1)
			{
				DISPLAY(" - ", false);
			}

			else if (_index == _textsCount - 1)
			{
				DISPLAY("", true);
			}
		}
	}

	DISPLAY("==============", true);
}

int RetrieveNumber(const string& _text, const bool _endl)
{
	Display(_text, _endl);
	GET_INT;
}

int RetrieveNumber(const string* _texts, const u_int& _textsCount, const bool _endl)
{
	Display(_texts, _textsCount, _endl);
	GET_INT;
}

bool RetrieveBoolean(const string& _text, const bool _endl)
{
	Display(_text, _endl);
	string _answer; 
	GET(_answer);
	return _answer == "oui"; // TODO make ToLower function
}

string RetrieveText(const string& _text, const bool _endl)
{
	Display(_text, _endl);
	GET_STRING;
}

u_int AskNumberInRange(const u_int& _min, const u_int& _max, const string& _text, const bool _endl)
{
	if (_max < _min)
	{
		DISPLAY("ERREUR => Le maximum est plus grand que le minimum !", true);
		return UINT_MAX;
	}

	bool _isValid;
	u_int _index;

	do
	{
		_index = RetrieveNumber(_text, true);
		_isValid = _index >= _min && _index <= _max;

		if (!_isValid)
		{
			system("cls");
			DISPLAY("ERREUR => Vous devez renseigner un index compris entre " + to_string(_min) + " et " + to_string(_max) + " !", true);
		}

	} while (!_isValid);

	system("cls");
	return _index;
}

u_int AskNumberInRange(const u_int& _min, const u_int& _max, const string* _texts, const u_int& _textsCount, const bool _endl)
{
	if (_max < _min)
	{
		DISPLAY("ERREUR => Le maximum est plus grand que le minimum !", true);
		return UINT_MAX;
	}

	bool _isValid;
	u_int _index;

	do
	{
		_index = RetrieveNumber(_texts, _textsCount, _endl);
		_isValid = _index >= _min && _index <= _max;

		if (!_isValid)
		{
			system("cls");
			DISPLAY("ERREUR => Vous devez renseigner un index compris entre " + to_string(_min) + " et " + to_string(_max) + " !", true);
		}

	} while (!_isValid);

	system("cls");
	return _index;
}