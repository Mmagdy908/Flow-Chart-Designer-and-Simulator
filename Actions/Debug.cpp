#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Debug.h"
#include "Validate.h"

Debug::Debug(ApplicationManager* pManager, int max, int connCount) : Action(pManager), MaxVar(max), connCount(connCount)
{
	
	nVars = 0;
	Variable = new string[MaxVar];
	Values = new double[MaxVar];
	
	//initializing variable and value arrays
	for (int i = 0; i < MaxVar; ++i)
	{
		Variable[i] = "";
		Values[i] = 0.0;
	}

}

void Debug::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//validate before debugging
	Validate* pValidate = new Validate(pManager, MaxVar, connCount);
	
	pValidate->Execute();

	pOut->ClearDebugBar();

	if (pValidate->IsValid())   //validate before simulation
	{
		//////*****IF VALID****///////

		Statement* Stat = NULL;
		Connector* pArrow = NULL;      //connector to next statement to execute

		Stat = pManager->GetStartStatement();    //starting from start stat
		Stat->SetSelected(true);                 //highlighting current stat
		pManager->UpdateInterface();

		pOut->PrintMessage("Click anywhere to proceed to next statement");
		pIn->GetPointClicked(Point(0, 0));

		//running start statement  and getting next arrow
		pArrow = Stat->Simulate(Variable, Values, nVars, pIn, pOut);

		while (pArrow = (pArrow->getDstStat()->Simulate(Variable, Values, nVars, pIn, pOut)))
		{
			Stat->SetSelected(false);
			Stat = pArrow->getSrcStat();
			Stat->SetSelected(true);
			pManager->UpdateInterface();

			if (Stat->IsCondition())
			{
				pOut->PrintMessage("Click anywhere to proceed to next statement");
				pIn->GetPointClicked(Point(0, 0));

				Statement* CondStat = Stat;

				int Looping = Stat->GetLooping();


				//sending a copy of current var & val arrays to conditional stat scope 
				string* tempVar = new string[MaxVar];
				int tempVarCount = nVars;

				for (int i = 0; i < tempVarCount; ++i)
				{
					tempVar[i] = Variable[i];
				}


				//handling loops
				if (Looping == 0)
				{
					Statement* IfConditionEnd = pManager->GetIfConditionEnd(Stat);

					while (pArrow->getDstStat() != IfConditionEnd)
					{
						if (pArrow = (pArrow->getDstStat()->Simulate(tempVar, Values, tempVarCount, pIn, pOut)))
						{
							Stat->SetSelected(false);
							Stat = pArrow->getSrcStat();
							Stat->SetSelected(true);		
							pOut->PrintDebug(tempVar, Values, tempVarCount);
							pManager->UpdateInterface();
							pOut->PrintMessage("Click anywhere to proceed to next statement");
							pIn->GetPointClicked(Point(0, 0));

						}
						else
							break;
					
					}
				}

				else if (Looping == 1)
				{
					while (pArrow != CondStat->GetNoOutConn())
					{
						if (pArrow = (pArrow->getDstStat()->Simulate(tempVar, Values, tempVarCount, pIn, pOut)))
						{
							Stat->SetSelected(false);
							Stat = pArrow->getSrcStat();
							Stat->SetSelected(true);
							pOut->PrintDebug(tempVar, Values, tempVarCount);
							pManager->UpdateInterface();
							pOut->PrintMessage("Click anywhere to proceed to next statement");
							pIn->GetPointClicked(Point(0, 0));
						}

					}
				}

				else
				{
					while (pArrow != CondStat->GetOutConn())
					{
						if (pArrow = (pArrow->getDstStat()->Simulate(tempVar, Values, tempVarCount, pIn, pOut)))
						{
							Stat->SetSelected(false);
							Stat = pArrow->getSrcStat();
							Stat->SetSelected(true);
							pOut->PrintDebug(tempVar, Values, tempVarCount);
							pManager->UpdateInterface();
							pOut->PrintMessage("Click anywhere to proceed to next statement");
							pIn->GetPointClicked(Point(0, 0));
						}

					}
				}
				delete[]tempVar;
				continue;
			}

			pOut->PrintDebug(Variable, Values, nVars);

			pOut->PrintMessage("Click anywhere to proceed to next statement");
			pIn->GetPointClicked(Point(0, 0));

		}

		// getting end stat and highliting it
		Stat->SetSelected(false);
		Stat = pManager->GetEndStatement();
		Stat->SetSelected(true);
		pManager->UpdateInterface();

		pOut->PrintMessage("Click anywhere to proceed to next statement");
		pIn->GetPointClicked(Point(0, 0));

		Stat->SetSelected(false);
		pManager->UpdateInterface();

		pOut->PrintMessage("Program Debugged successfully. Click anywhere to continue");
		pIn->GetPointClicked(Point(0, 0));

	}

	delete pValidate;
}
	


Debug::~Debug()
{
	delete[] Variable;
	delete[] Values;
}

