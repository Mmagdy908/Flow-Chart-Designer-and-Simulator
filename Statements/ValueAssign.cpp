#include "ValueAssign.h"


using namespace std;

ValueAssign::ValueAssign(int id, Point Lcorner, string LeftHS, double RightHS)
{
	ID = id;     //setting id

	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	
	// setting LHS and RHS and copying it to text
	LHS = LeftHS;
	RHS = RightHS;

	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();

	LeftCorner = Lcorner;     //setting Top left corner point 
	
	pOutConn = NULL;	//No connectors yet

	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.ASSGN_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}



bool ValueAssign::IsClicked(Point p)          //states if the point is inside the shape
{
	if (p.x >= LeftCorner.x && p.x <= (LeftCorner.x + UI.ASSGN_WIDTH))
		if (p.y >= LeftCorner.y && p.y <= (LeftCorner.y + UI.ASSGN_HI))
			return true;
	return false;
}

void ValueAssign::SetOutConn(Connector* pConn)
{
	pOutConn = pConn;
}

Connector* ValueAssign::GetOutConn()
{
	return pOutConn;
}


Point ValueAssign::GetInlet()
{
	return Inlet;
}

Point ValueAssign::GetOutlet()   //returns outlet 
{
	return Outlet;

}

void ValueAssign::operator=(ValueAssign C)
{
	LHS = C.LHS;
	RHS = C.RHS;
	Text = C.Text;

}

void ValueAssign::UpdatePoint(Point Position)
{

	LeftCorner.x = Position.x - UI.ASSGN_WIDTH / 2;
	LeftCorner.y = Position.y - UI.ASSGN_HI / 2;


	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.ASSGN_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WIDTH, UI.ASSGN_HI, Text, Selected);
	
}

void ValueAssign::Save(ofstream& file)
{
	

	file << "VAL_ASSIGN" << "   ";
	
	file << ID << "       ";
	
	file << LeftCorner.x << "       ";

	file << LeftCorner.y << "       ";
	
	file << LHS << "       ";
	
	file << RHS << "       ";

	file << endl;
}

void ValueAssign::Load(ifstream& file)
{
	
	
	file >> ID;
	
	file >> LeftCorner.x;
	
	file >> LeftCorner.y;
	
	file >> LHS;
	;
	file >> RHS;

	

	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.ASSGN_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}

void ValueAssign::GenerateCode(ofstream& OutFile, string* Vars, int& nVar)
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

bool ValueAssign::Validate(string* vars, int& nVars, int& nConn, Output* pOut)
{
	int i;

	++nConn;        //increment number of connectors

	if (!pOutConn)
	{
		pOut->PrintMessage("Chart is not correctly connected");
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



Connector* ValueAssign::Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut)
{
	int i;          //index of LHS in variable list

	//checking if LHS exists in variable list
	for (i = 0; i < nVars; ++i)
	{
		if (LHS == Vars[i])
		{
			Vals[i] = RHS;            //if it exists, update its value
			break;
		}
	}


	//if it doesn't exist, add it
	if (i == nVars)
	{
		Vars[i] = LHS;
		Vals[i] = RHS;
		++nVars;
	}

	return pOutConn;
}
