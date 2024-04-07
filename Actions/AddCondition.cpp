#include "AddCondition.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddCondition::AddCondition(ApplicationManager* pAppManager, int id) :Action(pAppManager)
{
	ID = id;
}

void AddCondition::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Conditional Statement: Click to add the statement");


	//Check where the user clicks to add statement to avoid interference with other areas
	while (1)
	{
		pIn->GetPointClicked(Position);
		if ((Position.x < UI.COND_WIDTH / 2) || (Position.x > (UI.DrawingAreaWidth - UI.COND_WIDTH / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to the statement");
		else if ((Position.y < (UI.ToolBarHeight + UI.COND_HI / 2)) || (Position.y > (UI.height - UI.StatusBarHeight - UI.COND_HI / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to the statement");
		else
			break;

	}

	pOut->ClearStatusBar();

	//setting First Operand
	pOut->PrintMessage("Please enter first operand:");
	while (1)
	{
		operand1 = pIn->GetString(pOut);
		if (ValueOrVariable(operand1) == INVALID_OP)    //check if operand is not a value or a variable
			pOut->PrintMessage("The entered operand is neither a value nor a variable. Please enter first operand:");
		else
			break;
	}

	//setting operator
	pOut->PrintMessage("Please enter a Comparison Operator:");

	Operator = pIn->GetCompOperator(pOut);

	//setting Second Operand
	pOut->PrintMessage("Please enter second operand:");
	while (1)
	{
		operand2 = pIn->GetString(pOut);
		if (ValueOrVariable(operand2) == INVALID_OP)    //check if operand is not a value or a variable
		{
			pOut->PrintMessage("The entered operand is neither a value nor a variable. Please enter second operand:");
			continue;
		}
		
		if (IsValue(operand1) && IsValue(operand2))   //checking if both operands are values
			pOut->PrintMessage("The entered operands are both values. Please enter valid second operand:");
		else
			break;
			
	}

}

void AddCondition::Execute()
{
	ReadActionParameters();


	Point Corner;
	Corner.x = Position.x - UI.COND_WIDTH / 2;
	Corner.y = Position.y;

	Condition* pCond = new Condition(ID, Corner, operand1, Operator, operand2);

	

	pManager->AddStatement(pCond); // Adds the created statement to application manger's statement list
}

