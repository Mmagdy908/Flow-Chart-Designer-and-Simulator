#include "Validate.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <iostream>

Validate::Validate(ApplicationManager* pManager, int max, int nDrawnConn) : Action(pManager), MaxVar(max)
{
	nVars = 0;
	nConn = 0;
	nStart = pManager->GetStartCount();
	nEnd = pManager->GetEndCount();
	this->nDrawnConn = nDrawnConn;
	Validated = false;

}


void Validate::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Point P;


	if (nStart == 0)
	{
		pOut->PrintMessage("There is no start statements");
		pIn->GetPointClicked(P);
		return;
	}

	if (nStart > 1)
	{
		pOut->PrintMessage("Chart has more than one start statement. Click anywhere to continue.");
		pIn->GetPointClicked(P);
		return;
	}
	if (nEnd == 0)
	{
		pOut->PrintMessage("There is no End statements");
		pIn->GetPointClicked(P);
		return;
	}

	if (nEnd > 1)
	{
		pOut->PrintMessage("Chart has more than one end statement. Click anywhere to continue.");
		pIn->GetPointClicked(P);
		return;
	}

	if (!pManager->CheckOutConnectors())
	{
		pOut->PrintMessage("Chart is not correctly connected");
		pIn->GetPointClicked(P);
		return;
	}

	Statement* Stat = NULL;
	Stat = pManager->GetStartStatement();


	pManager->CheckLooping();

	

	while (Stat->Validate(Variable, nVars, nConn, pOut))
	{
		if (Stat->IsCondition())
		{
			Statement* CondStat = Stat;

			int Looping = Stat->GetLooping();

			Statement* S2; //statement in no branch


			//sending copy of variable list to condotion scope

			string* tempVar = new string[MaxVar];
			int tempVarCount = nVars;

			for (int i = 0; i < tempVarCount; ++i)
			{
				tempVar[i] = Variable[i];
			}


			if (Looping == 0)
			{
				Statement* IfConditionEnd = pManager->GetIfConditionEnd(Stat);

				S2 = Stat->GetNoOutConn()->getDstStat();
				Stat = Stat->GetOutConn()->getDstStat();
				

				while (Stat != IfConditionEnd)
				{
					if (Stat->Validate(tempVar, tempVarCount, nConn, pOut))
						Stat = Stat->GetOutConn()->getDstStat();
					else
					{
						pIn->GetPointClicked(P);
						return;
					}
				}

				tempVarCount = nVars;


				while (S2 != IfConditionEnd)
				{
					if (S2->Validate(tempVar, tempVarCount, nConn, pOut))
						S2 = S2->GetOutConn()->getDstStat();
					else
					{
						pIn->GetPointClicked(P);
						return;
					}
				}
			}

			else if (Looping == 1)
			{

				Stat = Stat->GetOutConn()->getDstStat();
				while (Stat != CondStat)
				{
					if (Stat->Validate(tempVar, tempVarCount, nConn, pOut))
						Stat = Stat->GetOutConn()->getDstStat();
					else
					{
						pIn->GetPointClicked(P);
						return;
					}
				}

				Stat = Stat->GetNoOutConn()->getDstStat();
			}

			else 
			{
				Stat = Stat->GetNoOutConn()->getDstStat();
				while (Stat != CondStat)
				{
					if (Stat->Validate(tempVar, tempVarCount, nConn, pOut))
						Stat = Stat->GetOutConn()->getDstStat();
					else
					{
						pIn->GetPointClicked(P);
						return;
					}
				}

				Stat = Stat->GetOutConn()->getDstStat();
			}
			delete[]tempVar;
			continue;
		}
		if (!Stat->IsEnd())
			Stat = Stat->GetOutConn()->getDstStat();
		else
			break;
	}

	if (!Stat->Validate(Variable, nVars, nConn, pOut))
	{
		pIn->GetPointClicked(P);
		return;
	}
	if (nConn != nDrawnConn)
	{
			pOut->PrintMessage("Chart is not correctly connected");
			pIn->GetPointClicked(P);
			return;
	}
	


	pOut->PrintMessage("Chart is Valid. Click any where");
	pIn->GetPointClicked(P);
	Validated = true; 

}

bool Validate::IsValid()
{
	return Validated;
}


Validate::~Validate()
{
	delete[] Variable;
}