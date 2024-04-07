#pragma once

#include "Action.h"
#include <fstream>


class Load :public Action
{
	ifstream File;
	string FileName;
public:

	Load(ApplicationManager* pAppManager);

	void ReadActionParameters();

	void Execute();
};