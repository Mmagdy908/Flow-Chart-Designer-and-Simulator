#pragma once

#include "Action.h"

class Switch :public Action
{
public:

	Switch(ApplicationManager* pManager);

	void Execute();
};
