#include "AddValueAssign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddValueAssign::AddValueAssign(ApplicationManager *pAppManager, int id):Action(pAppManager)
{
	ID = id;
}

void AddValueAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
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

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter Variable:");
	LHS = pIn->GetVariable(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter Value:");
	RHS = pIn->GetValue(pOut);

	
}

void AddValueAssign::Execute()
{
	ReadActionParameters();
		
	
	//Calculating Top left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WIDTH / 2;
	Corner.y = Position.y - UI.ASSGN_HI / 2;
	
	ValueAssign *pAssign = new ValueAssign(ID, Corner, LHS, RHS);
	
	
	

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

