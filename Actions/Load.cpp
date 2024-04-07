#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Load.h"
#include "..\Connector.h"
#include "..\Statements\Condition.h"
#include "..\Statements\ValueAssign.h"
#include "..\Statements\VariableAssign.h"
#include "..\Statements\OperatorAssign.h"
#include "..\Statements\Read.h"
#include "..\Statements\Write.h"
#include "..\Statements\Start.h"
#include "..\Statements\End.h"


Load::Load(ApplicationManager* pAppManager) : Action(pAppManager)
{
	FileName="Saved Charts\\";
	
}

void Load::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Enter the name of the file you want to load from: ");
	FileName+=pIn->GetString(pOut);
	
	FileName += ".txt";
	
}

void Load::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	int StatCount;
	int ConnCount;



	string StatementType;

	Statement* pStat = NULL; //statement to load

	Connector* pConn = NULL; //Connector to load

	ReadActionParameters();

	File.open(FileName);

	if (File.fail())
	{
		pOut->PrintMessage("Failed to open the file. Click anywhere to continue");
		pIn->GetPointClicked(Point(0, 0));

		return;
	}
	

	//Removing StatList and ConnList and clearing draw area//
	pManager->RemoveStatements();
	pManager->RemoveConnectors();
	pOut->ClearDrawArea();
	pOut->ClearOutputBar();
	pOut->ClearDebugBar();


	
	//Loading Statements//
	File >> StatCount;   //get statement count

	//Load All statements
	for (int i = 0; i < StatCount; ++i)
	{
		File >> StatementType;
		
		
		if (StatementType == "STRT")
		{
			
			pStat = new Start(0, Point(0, 0));
			pStat->Load(File);
			pManager->AddStatement(pStat);
		}
		else if (StatementType == "VAL_ASSIGN")
		{
			pStat = new ValueAssign(0, Point(0, 0));
			pStat->Load(File);
			pManager->AddStatement(pStat);
		}
		else if (StatementType == "VAR_ASSIGN")
		{
			pStat = new VariableAssign(0, Point(0, 0));
			pStat->Load(File);
			pManager->AddStatement(pStat);
		}
		else if (StatementType == "OP_ASSIGN")
		{
			pStat = new OperatorAssign(0, Point(0, 0));
			pStat->Load(File);
			pManager->AddStatement(pStat);
		}
		else if (StatementType == "COND")
		{
			pStat = new Condition(0, Point(0, 0));
			pStat->Load(File);
			pManager->AddStatement(pStat);
		}
		else if (StatementType == "READ")
		{
			pStat = new Read(0, Point(0, 0));
			pStat->Load(File);
			pManager->AddStatement(pStat);
		}
		else if (StatementType == "WRITE")
		{
			pStat = new Write(0, Point(0, 0));
			pStat->Load(File);
			pManager->AddStatement(pStat);
		}
		else if (StatementType == "END")
		{
			pStat = new End(0, Point(0, 0));
			pStat->Load(File);
			pManager->AddStatement(pStat);
		}

	}
	

	//Loading Connectors//

	int ID1, ID2;            //IDs of Src and Dst of connectors
	Statement* Src = NULL;   //pointer to src and Dst Statements of connector
	Statement* Dst = NULL;
	int outletBranch;        //outlet branch type of connector

	File >> ConnCount;

	for (int i = 0; i < ConnCount; ++i)
	{
		File >> ID1;
		Src = pManager->GetStatementWithID(ID1);

		File >> ID2;
		Dst = pManager->GetStatementWithID(ID2);

		File >> outletBranch;

		pConn = new Connector(Src, Dst, outletBranch);

		if (outletBranch != 2)
			Src->SetOutConn(pConn);
		else 
			Src->SetNoOutConn(pConn);

		pManager->AddConnectors(pConn);


		//setting start and end points for connector
		pConn->setEndPoint(Dst->GetInlet());

		pConn->setStartPoint(Src->GetOutlet());

		if (Dst->IsCondition() && pConn->getStartPoint().y > Dst->GetInlet().y)
			pConn->setEndPoint(Dst->GetInletLoop());

		if (outletBranch != 0)
		{
			if (abs(Src->GetOutlet().x - Dst->GetInlet().x) > abs(Src->GetOutletL().x - Dst->GetInlet().x)) 
				pConn->setStartPoint(Src->GetOutletL());
		}
	}
	
	pManager->UpdateInterface();
	File.close();
}