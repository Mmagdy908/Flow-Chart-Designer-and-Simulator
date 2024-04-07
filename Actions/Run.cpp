#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Run.h"
#include "Validate.h"

Run::Run(ApplicationManager* pManager, int max, int connCount) : Action(pManager), MaxVar(max)
{
	
	nVars = 0;
	Variable = new string[MaxVar];
	Values = new double[MaxVar];
	
	for (int i = 0; i < MaxVar; ++i)
	{
		Variable[i] = "";
		Values[i] = 0.0;
	}
	this->connCount = connCount;
}

void Run::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Validate* pValidate = new Validate(pManager, MaxVar, connCount);
	
	pValidate->Execute();

	if (pValidate->IsValid())   //validate before simulation
	{
		//////*****IF VALID****///////
		pManager->RunAll(Variable, Values, nVars, pIn, pOut);
	}
	
	delete pValidate;
}


Run::~Run()
{
	
	delete[] Variable;
	delete[] Values;
}

