#include "AddConnector.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddConnector::AddConnector(ApplicationManager* pAppManager) : Action(pAppManager)
{
	Src = NULL;
	Dst = NULL;
	OutletBranch = 0;
}

//Read Connectors parameters
void AddConnector::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	Point P;    //point where user clicks

	//Read the (Src) parameter
	pOut->PrintMessage("Add Connector: Click on source statement");

	pIn->GetPointClicked(P);

	Src = pManager->GetStatement(P);

	if (!Src)                //check if user didn't click on a statement
	{
		pOut->PrintMessage("Invalid Click. Click anywhere to continue");
		pIn->GetPointClicked(P);		
		return;
	}

	if (Src->IsEnd())             //check if source statement is end statement
	{
		Src = NULL;
		pOut->PrintMessage("Invalid Statement is clicked. Click anywhere to continue");
		pIn->GetPointClicked(P);
		return;
	}

	if (Src->IsCondition() && Src->GetOutConn() && Src->GetNoOutConn())   //check for conditional statement connectors
	{
		Src = NULL;
		pOut->PrintMessage("Clicked Statement already has its connectors. Click anywhere to continue");
		pIn->GetPointClicked(P);
		return;
	}


	if(!Src->IsCondition() && Src->GetOutConn())     //check for other statements connectors
	{
		Src = NULL;

		pOut->PrintMessage("Clicked Statement already has its connectors. Click anywhere to continue");
		pIn->GetPointClicked(P);
		return;
	}




	//Read the (Dst) parameter
	pOut->PrintMessage("Add Connector: Click on destination statement");

	pIn->GetPointClicked(P);

	Dst = pManager->GetStatement(P);

	if (!Dst)                  //check if user didn't click on a statement
	{
		pOut->PrintMessage("Invalid Click. Click anywhere to continue");
		pIn->GetPointClicked(P);

		return;
	}

	if (Dst->IsStart())        //check if source statement is start statement
	{
		Dst = NULL;

		pOut->PrintMessage("Invalid Statement is clicked. Click anywhere to continue");
		pIn->GetPointClicked(P);
		return;
	}

	if (Dst==Src)        //check if source statement is start statement
	{
		Dst = NULL;

		pOut->PrintMessage("Invalid Statement is clicked. Click anywhere to continue");
		pIn->GetPointClicked(P);
		return;
	}

	if (Src->IsCondition())       //getting branch type from user in case of conditional statement
	{
		pOut->PrintMessage("Enter 1 for \"YES\" branch and 2 for \"NO\" branch");
		double D;
		while (1)
		{
			D = pIn->GetValue(pOut);
			if(D != 1.0 && D != 2.0)   //checks for invalid input
				pOut->PrintMessage("Invalid input!! Enter 1 for \"YES\" branch and 2 for \"NO\" branch");
			else if(D==1.0 && Src->GetOutConn())
				pOut->PrintMessage("Yes branch already exists!! Enter 1 for \"YES\" branch and 2 for \"NO\" branch");
			else if (D == 2.0 && Src->GetNoOutConn())
				pOut->PrintMessage("No branch already exists!! Enter 1 for \"YES\" branch and 2 for \"NO\" branch");
			else
			{
				OutletBranch = (int)D;
				break;
			}
		}
	}


 }

//Create and add the connector to the list of connectors
void AddConnector::Execute()
{

	ReadActionParameters();

	
	if (!Src || !Dst)      //check if parameters from ReadActionParameters are invalid
		return;


	//creating connector
	Connector* pConn = new Connector(Src, Dst, OutletBranch);

	pManager->AddConnectors(pConn);

	pConn->setEndPoint(Dst->GetInlet());
	
	pConn->setStartPoint(Src->GetOutlet());

	if (OutletBranch != 0)
	{
		if (abs(Src->GetOutlet().x- Dst->GetInlet().x)> abs(Src->GetOutletL().x - Dst->GetInlet().x)) ///???///
			pConn->setStartPoint(Src->GetOutletL());
	}

	if (Dst->IsCondition() && pConn->getStartPoint().y > Dst->GetInlet().y)
		pConn->setEndPoint(Dst->GetInletLoop());

	if (OutletBranch == 2)
	{
		Src->SetNoOutConn(pConn);
	}
	else
		Src->SetOutConn(pConn);

}