#include "AddRead.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

//constructor: set the ApplicationManager pointer inside this action
AddRead::AddRead(ApplicationManager* pAppManager, int id) :Action(pAppManager)
{
	ID = id;
}

void AddRead::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Read Statement: Click to add the statement");


	//Check where the user clicks to add statement to avoid interference with other areas
	while (1)
	{
		pIn->GetPointClicked(Position);
		if ((Position.x < UI.IO_WIDTH / 2) || (Position.x > (UI.DrawingAreaWidth - UI.IO_WIDTH / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to the statement");
		else if ((Position.y < (UI.ToolBarHeight + UI.IO_HI / 2)) || (Position.y > (UI.height - UI.StatusBarHeight - UI.IO_HI / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to the statement");
		else
			break;

	}

	pOut->ClearStatusBar();

	//asking user to enter the variable to read
	pOut->PrintMessage("Please enter Variable:");
	variable = pIn->GetVariable(pOut);
	


}

void AddRead::Execute()
{
	ReadActionParameters();


	//Calculating bottom left corner of Read statement block
	Point Corner;
	Corner.x = Position.x - UI.IO_WIDTH / 2;
	Corner.y = Position.y + UI.IO_HI / 2;

	Read* pAssign = new Read(ID, Corner, variable);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

