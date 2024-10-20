#pragma once
#include "Messaging.h"

void GameLoop();
bool DoAction(Messaging& _messaging, const u_int& _actionIndex);
void TestMessaging();
void TestUserInteract();