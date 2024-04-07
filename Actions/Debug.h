#pragma once

#include "Action.h"

class Debug :public Action
{
	int MaxVar;                      //maximum number of variable
	string* Variable;                //variable array
	double* Values;                  //values array corresponding to variables in Variable array
	int nVars;                       //NO. of existing variables

	int connCount;                   //NO. of connectors
	                                 //it will be sent to validate
public:

	Debug(ApplicationManager* pManager, int max, int connCount);
	
	// Execute simulate action
	void Execute();

	~Debug();
};


