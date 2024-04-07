#ifndef ADD_CONDITION_H
#define ADD_CONDITION_H

#include "Action.h"
#include "..\Statements\Condition.h"



class AddCondition : public Action
{
private:
	int ID;
	Point Position;	//Position where the user clicks to add the stat.
	                //assume it is the center of the shape

	string operand1;
	string operand2;
	string Operator; //comparision operator

	

public:
	AddCondition(ApplicationManager* pAppManager, int id);

	//Read Conditional statements position
	virtual void ReadActionParameters();

	//Create and add a Conditional statement to the list of statements
	virtual void Execute();

};

#endif