#pragma once

#include "Action.h"
#include "..\Statements\Write.h"


class AddWrite : public Action
{
private:

	int ID;
	Point Position;	  //Position where the user clicks to add the stat.
	                  //assume it is the center of the shape

	string variable;  //variable to read

public:
	AddWrite(ApplicationManager* pAppManager, int id);

	//Read Write statements position
	virtual void ReadActionParameters();

	//Create and add a Write statement to the list of statements
	virtual void Execute();

};