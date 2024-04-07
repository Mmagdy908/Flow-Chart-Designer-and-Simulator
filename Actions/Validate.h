#pragma once
#include "Action.h"

class Validate :public Action
{
	const int MaxVar;                       //maximum number of variable
	string* Variable=new string[MaxVar];
	int nVars;                              //NO. of existing variables
	int nDrawnConn;                         //No. Of connectors already drawn in chart

	int nConn;                              //NO. of connectors if the chart is correctly connected
	                                        //this variable will be incremented in each statement 
                                            //according to number of out connectors 
	
	int nStart;                             //NO. of start statements in chart
	int nEnd;                               //NO. of end statements in chart
	bool Validated;
public:

	Validate(ApplicationManager* pManager, int max, int nDrawnConn);


	// Execute validate action
	void Execute();
	bool IsValid();
	~Validate();
};