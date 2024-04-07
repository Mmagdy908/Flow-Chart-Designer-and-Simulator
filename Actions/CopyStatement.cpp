#include"Action.h"
#include"CopyStatement.h"
#include"AddEnd.h"
#include"AddOperatorAssign.h"
#include"AddRectAction.h"
#include"AddStart.h"
#include"AddValueAssign.h"
#include"AddVariableAssign.h"
#include"..\Statements\VariableAssign.h"
#include"..\Statements\Condition.h"
#include"..\Statements\End.h"
#include"..\Statements\OperatorAssign.h"
#include"..\Statements\Read.h"
#include"..\Statements\Write.h"
#include"..\Statements\Start.h"
#include"..\Statements\ValueAssign.h"
#include"..\ApplicationManager.h"





CopyStatement::CopyStatement(ApplicationManager* pAppManager) :Action(pAppManager){

}



void CopyStatement::Execute() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Point P;    //dummy Point


	// check if there is a selected statement
	if (pManager->GetSelectedStatement() == NULL) {
		pOut->PrintMessage("Please select a statement before copying. Click anywhere to continue");
		pIn->GetPointClicked(P);
		return;
	}
	else {
		Statement* Ptr;
		int tempID = 999;

		//clean clipboard
		if (pManager->GetClipboard())
		{
			delete (pManager->GetClipboard());
			pManager->SetClipboard(NULL);
		}


		//*********checking stat type and creating copy of it*********//

		Ptr = dynamic_cast<ValueAssign*>(pManager->GetSelectedStatement());
		if (Ptr != NULL) {

			ValueAssign* PStat = new ValueAssign(tempID, P);
			*PStat = *((ValueAssign*)pManager->GetSelectedStatement());
			pManager->SetClipboard(PStat);
			pOut->PrintMessage("Statement is copied succesfully. Click anywhere to continue");
			pIn->GetPointClicked(P);
			return;
		}

		Ptr = dynamic_cast<VariableAssign*>(pManager->GetSelectedStatement());
		if (Ptr != NULL) {

			VariableAssign* PStat = new VariableAssign(tempID, P);
			*PStat = *((VariableAssign*)pManager->GetSelectedStatement());
			pManager->SetClipboard(PStat);
			pOut->PrintMessage("Statement is copied succesfully. Click anywhere to continue");
			pIn->GetPointClicked(P);
			return;
		}

		Ptr = dynamic_cast<OperatorAssign*>(pManager->GetSelectedStatement());
		if (Ptr != NULL) {

			OperatorAssign* PStat = new OperatorAssign(tempID, P);
			*PStat = *((OperatorAssign*)pManager->GetSelectedStatement());
			pManager->SetClipboard(PStat);
			pOut->PrintMessage("Statement is copied succesfully. Click anywhere to continue");
			pIn->GetPointClicked(P);
			return;
		}

		Ptr = dynamic_cast<Condition*>(pManager->GetSelectedStatement());
		if (Ptr != NULL) {

			Condition* PStat = new Condition(tempID, P);
			*PStat = *((Condition*)pManager->GetSelectedStatement());
			pManager->SetClipboard(PStat);
			pOut->PrintMessage("Statement is copied succesfully. Click anywhere to continue");
			pIn->GetPointClicked(P);
			return;
		}

		Ptr = dynamic_cast<Read*>(pManager->GetSelectedStatement());
		if (Ptr != NULL) {

			Read* PStat = new Read(tempID, P);
			*PStat = *((Read*)pManager->GetSelectedStatement());
			pManager->SetClipboard(PStat);
			pOut->PrintMessage("Statement is copied succesfully. Click anywhere to continue");
			pIn->GetPointClicked(P);
			return;
		}

		Ptr = dynamic_cast<Write*>(pManager->GetSelectedStatement());
		if (Ptr != NULL) {

			Write* PStat = new Write(tempID, P);
			*PStat = *((Write*)pManager->GetSelectedStatement());
			pManager->SetClipboard(PStat);
			pOut->PrintMessage("Statement is copied succesfully. Click anywhere to continue");
			pIn->GetPointClicked(P);
			return;
		}

		Ptr = dynamic_cast<Start*>(pManager->GetSelectedStatement());
		if (Ptr != NULL) {

			Start* PStat = new Start(tempID, P);
			*PStat = *((Start*)pManager->GetSelectedStatement());
			pManager->SetClipboard(PStat);
			pOut->PrintMessage("Statement is copied succesfully. Click anywhere to continue");
			pIn->GetPointClicked(P);
			return;
		}

		Ptr = dynamic_cast<End*>(pManager->GetSelectedStatement());
		if (Ptr != NULL) {
			
			End* PStat = new End(tempID,P);
			*PStat = *((End*)pManager->GetSelectedStatement());
			pManager->SetClipboard(PStat);
			pOut->PrintMessage("Statement is copied succesfully. Click anywhere to continue");
			pIn->GetPointClicked(P);
			return;
		}

	}
	
}