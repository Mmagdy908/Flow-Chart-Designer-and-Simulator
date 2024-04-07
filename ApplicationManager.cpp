#include "ApplicationManager.h"
#include "Actions\AddConnector.h"
#include "Actions\AddValueAssign.h"
#include "Actions\AddVariableAssign.h"
#include "Actions\AddOperatorAssign.h"
#include "Actions\AddCondition.h"
#include "Actions\AddRead.h"
#include "Actions\AddWrite.h"
#include "Actions\AddStart.h"
#include "Actions\AddEnd.h"
#include "Actions\SelectUnselect.h"
#include "Actions\CopyStatement.h"
#include "Actions\PasteStatement.h"
#include "Actions\Delete.h"
#include "Actions\Save.h"
#include "Actions\Load.h"
#include "Actions\GenerateCode.h"
#include "Actions\Validate.h"
#include "Actions\Debug.h"
#include "Actions\Run.h"
#include "Actions\Switch.h"
#include "GUI\Input.h"
#include "GUI\Output.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pSelectedConn = NULL;	//no connector is selected yet
	pClipboard = NULL;
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	pOut->PrintMessage("Click on any Action");
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this, StatCount+1);
			break;

		case ADD_VAR_ASSIGN:
			pAct = new AddVariableAssign(this, StatCount + 1);
			break;

		case ADD_OPER_ASSIGN:
			pAct = new AddOperatorAssign(this, StatCount + 1);
			break;
		case ADD_CONDITION:
			pAct = new AddCondition(this, StatCount + 1);
			break;

		case ADD_READ:
			pAct = new AddRead(this, StatCount + 1);
			break;

		case ADD_WRITE:
			pAct = new AddWrite(this, StatCount + 1);
			break;

		case ADD_START:
			pAct = new AddStart(this, StatCount + 1);
			break;

		case ADD_END:
			pAct = new AddEnd(this, StatCount + 1);
			break;

		case ADD_CONNECTOR:
			pAct = new AddConnector(this);
			break;

		case VALIDATE:
			pAct = new Validate(this, MaxCount, ConnCount);
			break;

		case RUN:
			pAct = new Run(this, MaxCount, ConnCount);    //Setting max. variable number to max. statements number 
			                                              //as variables number can't exceed statement number
			break;

		case SELECT:
			
			pAct = new SelectUnselect(this);
			break;

		case COPY:

			pAct = new CopyStatement(this);
			break;

		case PASTE:

			pAct = new PasteStatement(this, StatCount);
			break;

		case DEL:
			pAct = new Delete(this);
			break;

		case SAVE:
			pAct = new Save(this);
			break;

		case LOAD:
			pAct = new Load(this);
			break;

		case DEBUG:
			pAct = new Debug(this, MaxCount, ConnCount);
			break;

		case Convert_CPP:
			pAct = new GenerateCode(this, MaxCount, ConnCount);
			break;

		case SWITCH_SIM_MODE:
			pAct = new Switch(this);
			break;

		case SWITCH_DSN_MODE :
			pAct = new Switch(this);
			break;

		case EXIT:
			///create Exit Action here
			
			break;
		
		case STATUS:
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement* pStat)
{
	if (StatCount < MaxCount)
		StatList[StatCount++] = pStat;

}

////////////////////////////////////////////////////////////////////////////////////
Statement* ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL

	for (int i = 0; i < StatCount; i++)
		if (StatList[i]->IsClicked(P))
			return StatList[i];

	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement* ApplicationManager::GetSelectedStatement() const
{
	return pSelectedStat;
}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement* pStat)
{
	pSelectedStat = pStat;
}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement* ApplicationManager::GetClipboard() const
{
	return pClipboard;
}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement* pStat)
{
	pClipboard = pStat;
}
/////////////////////////////////////////////////////////////////////////////////////
Statement* ApplicationManager::GetStatementWithID(int id)
{
	for (int i = 0; i < StatCount; i++)
	{
		if (id == StatList[i]->GetID())
			return StatList[i];
	}

}
/////////////////////////////////////////////////////////////////////////////////////
Connector* ApplicationManager::GetInConnectors(Statement* State)
{
	//Connector* conn;

	if (!pSelectedStat->IsStart())
	{
		for (int i = 0; i < ConnCount; ++i)
		{
			if (ConnList[i]->getDstStat() == State)
				return ConnList[i];

		}
	}
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteSelectedStatement()
{
	
	int i;

	//delete statement
	for (i = 0; i < StatCount; i++)
	{
		if (StatList[i] == pSelectedStat)
		{
			delete StatList[i];
			break;
		}
	}

	//update id of next statments
	int j;
	for (j = i; j < StatCount - 1; j++)
	{
		StatList[j] = StatList[j + 1];
		StatList[j]->UpdateID(j + 1);
	}
	
	SetSelectedStatement(NULL);

	StatList[j] = NULL;
	--StatCount;

}
//////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::RemoveStatements()   //removes all statement list
{
	for (int i = 0; i<StatCount; ++i)
	{
		delete StatList[i];
		StatList[i] = NULL;
	}

	StatCount = 0;
}
//==================================================================================//
//						Connectors Management Functions								//
//==================================================================================//


void ApplicationManager::AddConnectors(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}

Connector* ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++)
		if (ConnList[i]->IsClicked(P))
			return ConnList[i];
	return NULL;
}

Connector* ApplicationManager::GetSelectedConnector() const
{
	return pSelectedConn;
}
void ApplicationManager::SetSelectedConnector(Connector* Conn)
{
	pSelectedConn = Conn;
}

void ApplicationManager::DeleteConnector(Connector* pConn)
{
	int i;

	//delete connector
	for (i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == pConn)
		{

			delete ConnList[i];
			break;
		}
	}

	//removing gaps
	int j;
	for (j = i; j < ConnCount - 1; j++)
	{
		ConnList[j] = ConnList[j + 1];
	}


	ConnList[j] = NULL;
	--ConnCount;
}
//////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::RemoveConnectors()   //removes all connector list
{
	for (int i = 0; i<ConnCount; ++i)
	{
		delete ConnList[i];
		ConnList[i] = NULL;
	}

	ConnCount = 0;
}
//==================================================================================//
//						Save/Load Management Functions								//
//==================================================================================//

void ApplicationManager::SaveAll(ofstream& File)
{
	File << StatCount << endl;

	for (int i = 0; i < StatCount; i++)
	{
		StatList[i]->Save(File);
	}

	File << ConnCount << endl;

	for (int i = 0; i < ConnCount; i++)
	{
		ConnList[i]->Save(File);
	}
}

//==================================================================================//
//						Simulation Management Functions								//
//==================================================================================//

int ApplicationManager::GetStartCount()
{
	int nStart = 0;

	for (int i = 0; i < StatCount; ++i)
	{
		if (StatList[i]->IsStart())
			nStart++;

		
	}

	return nStart;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicationManager::GetEndCount()
{
	int nEnd = 0;

	for (int i = 0; i < StatCount; ++i)
	{
		if (StatList[i]->IsEnd())
			nEnd++;
	}

	return nEnd;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
Statement* ApplicationManager::GetStartStatement()
{
	for (int i = 0; i < StatCount; ++i)
	{
		if (StatList[i]->IsStart())
			return StatList[i];
	}
	
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
Statement* ApplicationManager::GetEndStatement()
{
	for (int i = 0; i < StatCount; ++i)
	{
		if (StatList[i]->IsEnd())
			return StatList[i];
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::CheckOutConnectors()    //checks if every statement has its out connectors
{
	for (int i = 0; i < StatCount; ++i)
	{
		if (StatList[i]->IsCondition() && (!StatList[i]->GetOutConn() || !StatList[i]->GetNoOutConn()))
		{
			return false;
		}
		else if (!StatList[i]->GetOutConn() && !StatList[i]->IsEnd())
		{
			
			return false;
		}
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
Statement* ApplicationManager::GetIfConditionEnd(Statement* Stat)
{
	Statement* S1;    //a statement in yes branch
	Statement* S2;    //a statement in no branch

	S1 = Stat->GetOutConn()->getDstStat();
	S2 = Stat->GetNoOutConn()->getDstStat();
	while (S1 != S2)
	{
		S2 = Stat->GetNoOutConn()->getDstStat();
		while (S1 != S2)
		{
			if (S2->IsEnd())
				break;
			S2 = S2->GetOutConn()->getDstStat();
		}

		if (S1 == S2)
		{
			break;
		}
		S1 = S1->GetOutConn()->getDstStat();
	}

	return S1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::CheckLooping() //checks if there are any loops and set looping in condition statements
{
	for (int i = 0; i < StatCount; ++i)
	{
		if (StatList[i]->IsCondition())
		{
			Statement* S1= StatList[i];

			while (!S1->IsEnd())
			{
				S1 = S1->GetOutConn()->getDstStat();
				if (S1 == StatList[i])
				{
					StatList[i]->SetLooping(1);
					return;
				}
			}

			S1 = StatList[i]->GetNoOutConn()->getDstStat();

			while (!S1->IsEnd())
			{
				if (S1 == StatList[i])
				{
					StatList[i]->SetLooping(2);
					return;
				}

				S1 = S1->GetOutConn()->getDstStat();
				
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::RunAll(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut)          //passing NO. of variables by reference to modify it
{
	Statement* Stat = NULL;
	Connector* pArrow = NULL;      //connector to next statement to execute

	Stat = GetStartStatement();


	//running start statement  and getting next arrow
	pArrow = Stat->Simulate(Vars, Vals, nVars, pIn, pOut);      


	while (pArrow = (pArrow->getDstStat()->Simulate(Vars, Vals, nVars, pIn, pOut)));     
	//This Loop gets destination statement the arrow points and
    //calls its run statement and gets its out connector and 
	//stores it in pArrow
	//when the run func of end stat is called it returns NULL
	//and the loop ends
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	RemoveStatements();
	RemoveConnectors();

	//deleting pclipboard 
	if (pClipboard)
		delete pClipboard;

	delete pIn;
	delete pOut;
	
}
