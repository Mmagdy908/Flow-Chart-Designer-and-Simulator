#include "AddOperatorAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddOperatorAssign::AddOperatorAssign(ApplicationManager* pAppManager, int id) :Action(pAppManager)
{
	ID = id;
}

void AddOperatorAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Value Assignment Statement: Click to add the statement");


	//Check where the user clicks to add statement to avoid interference with other areas
	while (1)
	{
		pIn->GetPointClicked(Position);
		if ((Position.x < UI.ASSGN_WIDTH / 2) || (Position.x > (UI.DrawingAreaWidth - UI.ASSGN_WIDTH / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to the statement");
		else if ((Position.y < (UI.ToolBarHeight + UI.ASSGN_HI / 2)) || (Position.y > (UI.height - UI.StatusBarHeight - UI.ASSGN_HI / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to the statement");
		else
			break;

	}

	pOut->ClearStatusBar();

	// Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter Variable:");
	LHS = pIn->GetVariable(pOut);

	//setting RHS
	pOut->PrintMessage("Please enter first operand:");
	while (1)
	{
		operand1 = pIn->GetString(pOut);
		if (ValueOrVariable(operand1) == INVALID_OP)    //check if operand is not a value or a variable
			pOut->PrintMessage("The entered operand is neither a value nor a variable. Please enter first operand:");
		else
			break;
	}
	

	pOut->PrintMessage("Please enter an Arithmatic Operator:");

	Operator = pIn->GetArithOperator(pOut);
	
	pOut->PrintMessage("Please enter second operand:");
	while (1)
	{
		operand2 = pIn->GetString(pOut);
		if (ValueOrVariable(operand2) == INVALID_OP)     //check if operand is not a value or a variable
			pOut->PrintMessage("The entered operand is neither a value nor a variable. Please enter second operand:");
		else
			break;
	}

}

void AddOperatorAssign::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WIDTH / 2;
	Corner.y = Position.y - UI.ASSGN_HI / 2;

	OperatorAssign* pAssign = new OperatorAssign(ID, Corner, LHS, operand1, Operator, operand2);
	
	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

