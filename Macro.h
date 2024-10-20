#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef unsigned int u_int;

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define CLEAR	cin.clear(); \
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

#define DISPLAY(_text, _endl)	cout << _text; \
								if (_endl) cout << endl;

#define GET(_value) cin >> _value; \
					system("cls");

#define GET_INT int _answer; \
				GET(_answer); \
				system("cls"); \
				return _answer;

#define GET_STRING	string _answer; \
					getline(cin, _answer); \
					system("cls"); \
					return _answer;

static void AddStringToArray(string*& _array, u_int& _arraySize, const string& _text)
{
	string* _newArray = new string[_arraySize + 1];

	for (u_int _index = 0; _index < _arraySize; _index++)
	{
		_newArray[_index] = _array[_index];
	}
	_newArray[_arraySize] = _text;

	delete[] _array;
	_array = _newArray;
	_arraySize++;
}