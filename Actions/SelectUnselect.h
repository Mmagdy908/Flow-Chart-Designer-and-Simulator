#pragma once
#include "Action.h"

class SelectUnselect : public Action
{
	Point P;  //Point user clicks

	Input* pIn;
	Output* pOut;
public:
	

	SelectUnselect(ApplicationManager* pAppManager);

	void ReadActionParameters();

	void Execute();
};

