#include"Action.h"
#include"PasteStatement.h"
#include"../GUI/Input.h"
#include"../GUI/Output.h"
#include"../Statements/Condition.h"
#include"../Statements/End.h"
#include"../Statements/Start.h"
#include"../Statements/Read.h"
#include"../Statements/Write.h"
#include"../Statements/OperatorAssign.h"
#include"../Statements/ValueAssign.h"
#include"../Statements/VariableAssign.h"
#include"../ApplicationManager.h"
#include"../Statements/Statement.h"


PasteStatement::PasteStatement(ApplicationManager* pAppManager, int C) : Action(pAppManager){

	StatCount = C;
}
void PasteStatement::ReadActionParameters() 
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Click somewhere in the drawing area to paste.");
	//Check where the user clicks to add statement to avoid interference with other areas
	while (1)
	{
		pIn->GetPointClicked(Position);
		if ((Position.x < UI.COND_WIDTH / 2) || (Position.x > (UI.DrawingAreaWidth - UI.COND_WIDTH / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to add the statement");
		else if ((Position.y < (UI.ToolBarHeight + UI.COND_HI / 2)) || (Position.y > (UI.height - UI.StatusBarHeight - UI.COND_HI / 2)))
			pOut->PrintMessage("Your statement can not be drawn here. Click anywhere to add the statement");
		else
			break;

	}

}

void PasteStatement::Execute() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	if (pManager->GetClipboard() == NULL) {
		pOut->PrintMessage("Can't paste, please copy a statement first. Click anywhere to continue");
		pIn->GetPointClicked(P);
		return;
	}

	ReadActionParameters();



	//*********checking stat type and creating copy of it*********//

	Statement* Ptr = NULL;
	
	Ptr = dynamic_cast<ValueAssign*>(pManager->GetClipboard());
	if (Ptr != NULL) {
		ValueAssign* Stat = NULL;
		Stat = new ValueAssign(0, P);
		*Stat = *((ValueAssign*)pManager->GetClipboard());
		Stat->UpdatePoint(Position);
		Stat->UpdateID(StatCount + 1);
		pManager->AddStatement(Stat);
		pManager->UpdateInterface();
		return;
	}

	Ptr = dynamic_cast<VariableAssign*>(pManager->GetClipboard());
	if (Ptr != NULL) {
		VariableAssign* Stat = NULL;
		Stat = new VariableAssign(0, P);
		*Stat = *((VariableAssign*)pManager->GetClipboard());
		Stat->UpdatePoint(Position);
		Stat->UpdateID(StatCount + 1);
		pManager->AddStatement(Stat);
		pManager->UpdateInterface();
		return;
	}

	Ptr = dynamic_cast<OperatorAssign*>(pManager->GetClipboard());
	if (Ptr != NULL) {
		OperatorAssign* Stat = NULL;
		Stat = new OperatorAssign(0, P);
		*Stat = *((OperatorAssign*)pManager->GetClipboard());
		Stat->UpdatePoint(Position);
		Stat->UpdateID(StatCount + 1);
		pManager->AddStatement(Stat);
		pManager->UpdateInterface();
		return;
	}

	Ptr = dynamic_cast<Condition*>(pManager->GetClipboard());
	if (Ptr != NULL) {
		Condition* Stat = NULL;
		Stat = new Condition(0, P);
		*Stat = *((Condition*)pManager->GetClipboard());
		Stat->UpdatePoint(Position);
		Stat->UpdateID(StatCount + 1);
		pManager->AddStatement(Stat);
		pManager->UpdateInterface();
		return;
	}

	Ptr = dynamic_cast<Write*>(pManager->GetClipboard());
	if (Ptr != NULL) {
		Write* Stat = NULL;
		Stat = new Write(0, P);
		*Stat = *((Write*)pManager->GetClipboard());
		Stat->UpdatePoint(Position);
		Stat->UpdateID(StatCount + 1);
		pManager->AddStatement(Stat);
		pManager->UpdateInterface();
		return;
	}

	Ptr = dynamic_cast<Read*>(pManager->GetClipboard());
	if (Ptr != NULL) {
		Read* Stat = NULL;
		Stat = new Read(0, P);
		*Stat = *((Read*)pManager->GetClipboard());
		Stat->UpdatePoint(Position);
		Stat->UpdateID(StatCount + 1);
		pManager->AddStatement(Stat);
		pManager->UpdateInterface();
		return;
	}

	Ptr = dynamic_cast<Start*>(pManager->GetClipboard());
	if (Ptr != NULL) {
		Start* Stat = NULL;
		Stat = new Start(0, P);
		*Stat = *((Start*)pManager->GetClipboard());
		Stat->UpdatePoint(Position);
		Stat->UpdateID(StatCount + 1);
		pManager->AddStatement(Stat);
		pManager->UpdateInterface();
		return;
	}

	Ptr = dynamic_cast<End*>(pManager->GetClipboard());
	if (Ptr != NULL) {
		End* Stat = NULL;
		Stat = new End(0, P);
		*Stat = *((End*)pManager->GetClipboard());
		Stat->UpdatePoint(Position);
		Stat->UpdateID(StatCount+1);
		pManager->AddStatement(Stat);
		pManager->UpdateInterface();
		return;
	}


}