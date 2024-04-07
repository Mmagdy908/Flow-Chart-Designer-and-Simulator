#include "GenerateCode.h"
#include "Validate.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <iostream>

GenerateCode::GenerateCode(ApplicationManager* pManager, int max, int connCount) : Action(pManager), MaxVar(max)
{
	nVars = 0;
	this->connCount = connCount;

	FileName = "Converted C++ files\\";
}

void GenerateCode::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Enter the name of the C++ file you want: ");
	FileName += pIn->GetString(pOut);

	FileName += ".cpp";

}

void GenerateCode::Execute()
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

	Validate* pValidate = new Validate(pManager, MaxVar, connCount);

	pValidate->Execute();
	Point P;

	if (pValidate->IsValid())   //validate before converting
	{
		//////*****IF VALID****///////
		Statement* Stat = NULL;
		Stat = pManager->GetStartStatement();


		while (!Stat->IsEnd())
		{
			Stat->GenerateCode(File, Variable, nVars);

			Stat = Stat->GetOutConn()->getDstStat();

			if (Stat->IsCondition())
			{
				Statement* CondStat = Stat;

				int Looping = Stat->GetLooping();

				Statement* S2; //statement in no branch

				//converting thee condition stat
				Stat->GenerateCode(File, Variable, nVars);

				//sending copy of variable list to condition scope

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
						Stat->GenerateCode(File, tempVar, tempVarCount);

						Stat = Stat->GetOutConn()->getDstStat();
					}

					File << "}\nelse\n{\n";

					tempVarCount = nVars;


					while (S2 != IfConditionEnd)
					{
						S2->GenerateCode(File, tempVar, tempVarCount);

						S2 = S2->GetOutConn()->getDstStat();
					}
					File << "}\n";
				}

				else if (Looping == 1)
				{

					Stat = Stat->GetOutConn()->getDstStat();
					while (Stat != CondStat)
					{
						Stat->GenerateCode(File, tempVar, tempVarCount);

						Stat = Stat->GetOutConn()->getDstStat();
					}
					File << "}\n";

					Stat = Stat->GetNoOutConn()->getDstStat();
				}

				else
				{
					Stat = Stat->GetNoOutConn()->getDstStat();
					while (Stat != CondStat)
					{
						Stat->GenerateCode(File, tempVar, tempVarCount);

						Stat = Stat->GetOutConn()->getDstStat();
					}
					File << "}\n";

					Stat = Stat->GetOutConn()->getDstStat();
				}
				delete[]tempVar;
				continue;
			}
		}

		//generate code of end stat
		Stat->GenerateCode(File, Variable, nVars);

	}

	File.close();

	delete pValidate;
}




GenerateCode::~GenerateCode()
{
	delete[] Variable;
}