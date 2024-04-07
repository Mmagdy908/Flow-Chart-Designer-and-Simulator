#pragma once

#include "Action.h"

class Run :public Action
{
	int MaxVar;                      //maximum number of variable
	string* Variable;                //variable array
	double* Values;                  //values array corresponding to variables in Variable array
	int nVars;                       //NO. of existing variables
	int connCount;                   //NO. of connectors
public:

	Run(ApplicationManager* pManager, int max, int connCount);
	
	// Execute simulate action
	void Execute();

	~Run();
};


