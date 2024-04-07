#ifndef ADD_START_H
#define ADD_START_H

#include "Action.h"
#include "..\Statements\Start.h"



class AddStart : public Action
{
private:
	

	int ID;
	Point Position;	//Position where the user clicks to add the stat.
	                //assume it is the center of the shape

public:
	AddStart(ApplicationManager* pAppManager, int id);

	//Read Start statements position
	virtual void ReadActionParameters();

	//Create and add an Start statement to the list of statements
	virtual void Execute();

};

#endif