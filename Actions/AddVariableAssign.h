#ifndef ADD_VARIABLE_ASSIGN_H
#define ADD_VARIABLE_ASSIGN_H

#include "Action.h"
#include "..\Statements\VariableAssign.h"

//Add Variable Assignment Statement Action
//This class is responsible for 
// 1 - Getting Assignment stat. coordinates from the user (one of the parameters of this action)
// 2 - Getting the LHS and RHS of the statement from the user (some of the parameters of this action)
// 3 - Creating an object of Assignment class and passing it parameters
// 4 - Adding the created object to the list of statements of the application manager
class AddVariableAssign : public Action
{
private:
	// in the data members of the actions
	// we put the paramaters of the action
	// to be set in ReadActionParameters() then used in Execute()

	int ID;
	Point Position;	//Position where the user clicks to add the stat.
	                //assume it is the center of the shape
	
	string LHS;
	string RHS;
public:
	AddVariableAssign(ApplicationManager* pAppManager, int id);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

#endif
