#ifndef ADD_END_H
#define ADD_END_H

#include "Action.h"
#include "..\Statements\End.h"



class AddEnd : public Action
{
private:
	

	int ID;
	Point Position;	//Position where the user clicks to add the stat.
	                //assume it is the center of the shape

public:
	AddEnd(ApplicationManager* pAppManager, int id);

	//Read End statements position
	virtual void ReadActionParameters();

	//Create and add an End statement to the list of statements
	virtual void Execute();

};

#endif