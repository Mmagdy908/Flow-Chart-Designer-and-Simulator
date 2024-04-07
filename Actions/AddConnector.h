#pragma once


#include "Action.h"
#include "..\Statements\Statement.h"

class AddConnector : public Action
{
	Statement* Src;    //source statement
	Statement* Dst;    //destination statement
	int OutletBranch;  //outlet branch type
public:
	AddConnector(ApplicationManager* pAppManager);

	//Read Connectors parameters
	virtual void ReadActionParameters();

	//Create and add the connector to the list of connectors
	virtual void Execute();


};