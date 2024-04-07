#include "SelectUnselect.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"




SelectUnselect::SelectUnselect(ApplicationManager* pAppManager) :Action(pAppManager)
{
	 pIn = pManager->GetInput();
	 pOut = pManager->GetOutput();
}

void SelectUnselect::ReadActionParameters()
{

	pOut->PrintMessage("Click on a statement or a connector");
	pIn->GetPointClicked(P);
}


void SelectUnselect::Execute()
{
	ReadActionParameters();


	Statement* Stat = NULL;

	Connector* Conn = NULL;

	Stat = pManager->GetStatement(P);
	Conn = pManager->GetConnector(P);

	if (!Stat && !Conn)   //user clicks on invalid area
	{
		pOut->PrintMessage("Invalid Click. Clicl anywhere to continue");
		pIn->GetPointClicked(P);
		return;
	}

	// user Clicks on a statement
	if (Stat)
	{
		//user clicked os selected statement
		if (Stat == pManager->GetSelectedStatement())
		{
			//unselect it
			Stat->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			return;
		}

		//if there is a selected statement
		if (pManager->GetSelectedStatement())
		{
			pManager->GetSelectedStatement()->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
		}

		//if there is a selected connector
		if (pManager->GetSelectedConnector())
		{
			pManager->GetSelectedConnector()->SetSelected(false);
			pManager->SetSelectedConnector(NULL);
		}

		//select the statement user clicked
		Stat->SetSelected(true);
		pManager->SetSelectedStatement(Stat);
		pManager->UpdateInterface();
		return;
	}


	// user Clicks on a connector
	if (Conn)
	{
		//user clicked os selected connector
		if (Conn == pManager->GetSelectedConnector())
		{
			//unselect it
			Conn->SetSelected(false);
			pManager->SetSelectedConnector(NULL);
			return;
		}

		//if there is a selected statement
		if (pManager->GetSelectedStatement())
		{
			pManager->GetSelectedStatement()->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
		}

		//if there is a selected connector
		if (pManager->GetSelectedConnector())
		{
			pManager->GetSelectedConnector()->SetSelected(false);
			pManager->SetSelectedConnector(NULL);

		}

		//select the connector user clicked
		Conn->SetSelected(true);
		pManager->SetSelectedConnector(Conn);
		pManager->UpdateInterface();
		return;
	}	

}