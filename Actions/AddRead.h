#pragma once

#include "Action.h"
#include "..\Statements\Read.h"


class AddRead : public Action
{
private:

	int ID;
	Point Position;	  //Position where the user clicks to add the stat.
	                  //assume it is the center of the shape

	string variable;  //variable to read
	
public:
	AddRead(ApplicationManager* pAppManager, int id);

	//Read the Read statement position
	virtual void ReadActionParameters();

	//Create and add a Read statement to the list of statements
	virtual void Execute();

};