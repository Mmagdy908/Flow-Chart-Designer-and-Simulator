#pragma once
#include "Action.h"
#include <fstream>

class GenerateCode :public Action
{
	const int MaxVar;                       //maximum number of variable
	string* Variable=new string[MaxVar];
	int nVars;                              //NO. of existing variables
	int connCount;                          //NO. of connectors
	                                        //to be sent to Validate action
	
	ofstream File;
	string FileName;

public:

	GenerateCode(ApplicationManager* pManager, int max, int connCount);

	void ReadActionParameters();

	void Execute();

	~GenerateCode();
};