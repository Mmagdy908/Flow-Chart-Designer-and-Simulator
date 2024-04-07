#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Save.h"


Save::Save(ApplicationManager* pAppManager) : Action(pAppManager)
{
	FileName="Saved Charts\\";
}

void Save::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Enter the name of the file you want to save to: ");
	FileName+=pIn->GetString(pOut);
	
	FileName += ".txt";
	
}

void Save::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();

	File.open(FileName);

	if (File.fail())
	{
		pOut->PrintMessage("Failed to open the file. Click anywhere to continue");
		pIn->GetPointClicked(Point(0, 0));
		return;
	}


	pManager->SaveAll(File);

	File.close();
}