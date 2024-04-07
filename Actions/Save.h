#pragma once

#include "Action.h"
#include <fstream>


class Save :public Action
{
	ofstream File;
	string FileName;
public:

	Save(ApplicationManager* pAppManager);

	void ReadActionParameters();

	void Execute();
};