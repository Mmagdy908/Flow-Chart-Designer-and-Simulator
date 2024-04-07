#include "AddStart.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddStart::AddStart(ApplicationManager* pAppManager, int id) :Action(pAppManager)
{
	ID = id;
}

void AddStart::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Start Statement: Click to add the statement");

	//Check where the user clicks to add statement to avoid interference with other areas
	while (1)
	{
		pIn->GetPointClicked(Position);
		if ((Position.x < UI.OVAL_WIDTH / 2 ) || (Position.x > (UI.DrawingAreaWidth - UI.OVAL_WIDTH / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to the statement");
		else if ((Position.y < (UI.ToolBarHeight + UI.OVAL_HI / 2)) || (Position.y > (UI.height - UI.StatusBarHeight - UI.OVAL_HI / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to the statement");
		else
			break;

	}

	pOut->ClearStatusBar();
}

void AddStart::Execute()
{
	ReadActionParameters();


	Point Center;
	Center.x = Position.x;
	Center.y = Position.y;

	Start* pStart = new Start(ID, Center);



	pManager->AddStatement(pStart); // Adds the created statement to application manger's statement list
}

