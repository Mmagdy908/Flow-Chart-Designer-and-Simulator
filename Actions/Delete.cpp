#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Delete.h"

Delete::Delete(ApplicationManager* pAppManager) :Action(pAppManager){}

void Delete::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Point P;


	Statement* Stat = pManager->GetSelectedStatement();

	Connector* Conn = pManager->GetSelectedConnector();

	

	//if no statement or connector is selected
	if (!Stat && !Conn)
	{
		pOut->PrintMessage("No statement or connector is selected. Click anywhere to continue");
		pIn->GetPointClicked(P);
		return;
	}

	//if a connector is selected
	if (Conn)
	{
		if (Conn->GetOutletBranch() != 2)
			Conn->getSrcStat()->SetOutConn(NULL);
		else
			Conn->getSrcStat()->SetNoOutConn(NULL);

		pManager->DeleteConnector(Conn);
		pManager->SetSelectedConnector(NULL);
		return;
	}


	//remove in connectors

	Connector* InConn=NULL;

	if (Stat)
	{
		//remove in connectors

		while (1)
		{
			InConn = pManager->GetInConnectors(Stat);

			if (InConn)
			{
				if (InConn->GetOutletBranch() != 2)
					InConn->getSrcStat()->SetOutConn(NULL); //setteng out connector of source statement to NULL
				else
					InConn->getSrcStat()->SetNoOutConn(NULL);

				pManager->DeleteConnector(InConn);
			}
			else 
				break;
		}


		//remove out connectors
		if (!Stat->IsEnd())
		{
			if (Stat->GetOutConn())
				pManager->DeleteConnector(Stat->GetOutConn());

			if (Stat->IsCondition())
			{
				if (Stat->GetNoOutConn())
					pManager->DeleteConnector(Stat->GetNoOutConn());   //delete no connector of condition stat
			}
		}
		pManager->DeleteSelectedStatement();
	}

	pManager->UpdateInterface();
}

