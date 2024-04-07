#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Switch.h"


Switch::Switch(ApplicationManager* pManager): Action(pManager)
{

}


void Switch::Execute()
{

	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->ClearToolbar();
	if(UI.AppMode==DESIGN)
		pOut->CreateSimulationToolBar();
	else
		pOut->CreateDesignToolBar();

}

