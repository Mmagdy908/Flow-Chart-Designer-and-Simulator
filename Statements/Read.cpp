#include "Read.h"


Read::Read(int id, Point Lcorner, string variable)
{
	ID = id;     //setting id

	// setting variable
	
	Variable = variable;

	ostringstream T;
	T << "Read " << Variable;
	Text = T.str();

	LeftCorner = Lcorner;     //setting Bottom left corner point 

	pOutConn = NULL;	      //No connectors yet

	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.IO_WIDTH / 2;
	Inlet.y = LeftCorner.y - UI.IO_HI;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y;
}


bool Read::IsClicked(Point p)          //states if the point is inside the shape
{
	if (p.x >= LeftCorner.x && p.x <= (LeftCorner.x + UI.IO_WIDTH))
		if (p.y >= (LeftCorner.y - UI.IO_HI) && p.y <= LeftCorner.y)
			return true;
	return false;
}

void Read::SetOutConn(Connector* pConn)
{
	pOutConn = pConn;
}

Connector* Read::GetOutConn()
{
	return pOutConn;
}

Point Read::GetInlet()
{
	return Inlet;
}

Point Read::GetOutlet()   //returns outlet 
{
	return Outlet;

}

void Read::operator=(Read C)
{
	Text = C.Text;
	
	Variable = C.Variable;
}

void Read::UpdatePoint(Point Position)
{

	LeftCorner.x = Position.x - UI.IO_WIDTH / 2;
	LeftCorner.y = Position.y + UI.IO_HI / 2;

	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.IO_WIDTH / 2;
	Inlet.y = LeftCorner.y - UI.IO_HI;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y;
}

void Read::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawReadWrite(LeftCorner, UI.IO_WIDTH, UI.IO_HI, Text, Selected);

}

void Read::Save(ofstream& file)
{
	
	file << "READ" << "         ";
	
	file << ID << "       ";
	
	file << LeftCorner.x << "       ";
	
	file << LeftCorner.y << "       ";
	
	file << Variable << "       ";
	file << endl;
}

void Read::Load(ifstream& file)
{

	file >> ID;
	
	file >> LeftCorner.x;

	file >> LeftCorner.y;
	
	file >> Variable;

	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.IO_WIDTH / 2;
	Inlet.y = LeftCorner.y - UI.IO_HI;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y;

	ostringstream T;
	T << "Read " << Variable;
	Text = T.str();

}

void Read::GenerateCode(ofstream& OutFile, string* Vars, int& nVar)
{

	int i;

	//check if LHS exists in variable list
	for (i = 0; i < nVar; ++i)
	{
		if (Variable == Vars[i])
			break;
	}


	// if LHS doesn't exist in variable list
	if (i == nVar)
	{
		OutFile << "double "+Variable+";\n";
		Vars[nVar++] = Variable;
	}

	OutFile << "cin >> " + Variable+";\n";

}

bool Read::Validate(string* vars, int& nVars, int& nConn, Output* pOut)
{
	int i;

	++nConn;        //increment number of connectors

	if (!pOutConn)
	{
		pOut->PrintMessage("Chart is not correctly connected");
		return false;
	}
	

	//check if variable exists in variable list
	for (i = 0; i < nVars; ++i)
	{
		if (Variable == vars[i])
			break;
	}

	// if variable doesn't exist in variable list
	if (i == nVars)
	{
		vars[nVars++] = Variable;          //add it
	}

	return true;
}


Connector* Read::Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut)
{
	int i;          //index of the variable to read in variable list

	//checking if variable exists in variable list
	for (i = 0; i < nVars; ++i)
	{
		if (Variable == Vars[i])      
			break;
	}


	//if it doesn't exist, add it
	if (i == nVars)
	{
		Vars[i] = Variable;
		++nVars;
	}

	//Reading a value from the user and storing it in variable
	pOut->PrintMessage("Enter a value");
	Vals[i] = pIn->GetValue(pOut);


	return pOutConn;
}
