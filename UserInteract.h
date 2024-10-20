#pragma once
#include "Macro.h"

void Display(const string& _text, const bool _endl = true);
void Display(const string* _texts, const u_int& _textsCount, const bool _endl = true);
int RetrieveNumber(const string* _texts, const u_int& _textsCount, const bool _endl = true);
int RetrieveNumber(const string& _text, const bool _endl = true);
bool RetrieveBoolean(const string& _text, const bool _endl = true);
string RetrieveText(const string& _text, const bool _endl = true);
u_int AskNumberInRange(const u_int& _min, const u_int& _max, const string& _text, const bool _endl = true);
u_int AskNumberInRange(const u_int& _min, const u_int& _max, const string* _text, const u_int& _textsCount, const bool _endl = true);