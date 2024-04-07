#include "VariableAssign.h"

using namespace std;

VariableAssign::VariableAssign(int id, Point Lcorner, string LeftHS, string RightHS)
{
	ID = id;

	// Note: The LeftHS and RightHS should be validated inside (AddVariableAssign) action
	//       before passing it to the constructor of VariableAssign
	LHS = LeftHS;
	RHS = RightHS;


	// setting LHS and RHS and copying it to text
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();


	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}


bool VariableAssign::IsClicked(Point p)          //states if the point is inside the shape
{
	if (p.x >= LeftCorner.x && p.x <= (LeftCorner.x + UI.ASSGN_WIDTH))
		if (p.y >= LeftCorner.y && p.y <= (LeftCorner.y + UI.ASSGN_HI))
			return true;
	return false;
}

void VariableAssign::SetOutConn(Connector* pConn)
{
	pOutConn = pConn;
}

Connector* VariableAssign::GetOutConn()
{
	return pOutConn;
}

Point VariableAssign::GetInlet()
{
	return Inlet;
}

Point VariableAssign::GetOutlet()   //returns outlet 
{
	return Outlet;

}


void VariableAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WIDTH, UI.ASSGN_HI, Text, Selected);

}

void VariableAssign::Save(ofstream& file)
{
	
	file << "VAR_ASSIGN" << "   ";

	file << ID << "       ";
	
	file << LeftCorner.x << "       ";

	file << LeftCorner.y << "       ";
	
	file << LHS << "       ";

	file << RHS << "       ";

	file << endl;
}

void VariableAssign::Load(ifstream& file)
{
	
	
	file >> ID;
	
	file >> LeftCorner.x;
	
	file >> LeftCorner.y;
	
	file >> LHS;
	
	file >> RHS;

	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.ASSGN_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

	// setting LHS and RHS and copying it to text
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}


void VariableAssign::operator=(VariableAssign C)
{
	LHS = C.LHS;
	RHS = C.RHS;
	Text = C.Text;

}

void VariableAssign::UpdatePoint(Point Position)
{

	LeftCorner.x = Position.x - UI.ASSGN_WIDTH / 2;
	LeftCorner.y = Position.y - UI.ASSGN_HI / 2;


	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.ASSGN_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void VariableAssign::GenerateCode(ofstream& OutFile, string* Vars, int& nVar)
{

	int i;

	//check if LHS exists in variable list
	for (i = 0; i < nVar; ++i)
	{
		if (LHS == Vars[i])
			break;
	}


	// if LHS doesn't exist in variable list
	if (i == nVar)
	{
		OutFile << "double ";
		Vars[nVar++] = LHS;
	}

	OutFile << Text << ";\n";

}

bool VariableAssign::Validate(string* vars, int& nVars, int& nConn, Output* pOut)
{

	int i;

	++nConn;        //increment number of connectors

	if (!pOutConn)
	{
		pOut->PrintMessage("Chart is not correctly connected");
		return false;
	}

	//check if RHS exists in variable list
	for (i = 0; i < nVars; ++i)
	{
		if (RHS == vars[i])
			break;
	}

	if (i == nVars)
	{
		pOut->PrintMessage("Invalid Chart. Variable " + RHS + "is used before being initialized.Click anywhere to continue");
		return false;
	}
	
	//check if LHS exists in variable list
	for (i = 0; i < nVars; ++i)
	{
		if (LHS == vars[i])
			break;
	}


	// if LHS doesn't exist in variable list
	if (i == nVars)
	{
		vars[nVars++] = LHS;          //add it
	}


	return true;
}



Connector* VariableAssign::Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut)
{
	int i;            //index of LHS in variable list
	double D;

	//Finding RHS in variable list
	//it must exist as the chart is validated
	for (i = 0; i < nVars; ++i)
	{
		if (RHS == Vars[i])
		{
			D = Vals[i];            //getting RHS value

			break;
		}
	}



	//checking if LHS exists in variable list
	for (i = 0; i < nVars; ++i)
	{
		if (LHS == Vars[i])
		{
			Vals[i] = D;            //if it exists, update its value

			break;
		}
	}


	//if it doesn't exist, add it
	if (i == nVars)
	{
		Vars[i] = LHS;
		Vals[i] = D;
		++nVars;
	}

	return pOutConn;
}
