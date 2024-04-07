#include "Write.h"


Write::Write(int id, Point Lcorner, string variable)
{
	ID = id;               //setting id
    Variable = variable;  // setting variable

	ostringstream T;
	T << "Write " << Variable;
	Text = T.str();

	LeftCorner = Lcorner;     //setting Bottom left corner point 

	pOutConn = NULL;	      //No connectors yet

	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.IO_WIDTH / 2;
	Inlet.y = LeftCorner.y - UI.IO_HI;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y;
}

bool Write::IsClicked(Point p)          //states if the point is inside the shape
{
	if (p.x >= LeftCorner.x && p.x <= (LeftCorner.x + UI.IO_WIDTH))
		if (p.y >= (LeftCorner.y - UI.IO_HI) && p.y <= LeftCorner.y)
			return true;
	return false;
}

void Write::SetOutConn(Connector* pConn)
{
	pOutConn = pConn;
}

Connector* Write::GetOutConn()
{
	return pOutConn;
}


Point Write::GetInlet()
{
	return Inlet;
}

Point Write::GetOutlet()   //returns outlet 
{
	return Outlet;

}

void Write::operator=(Write C)
{
	Text = C.Text;

	Variable = C.Variable;
}

void Write::UpdatePoint(Point Position)
{

	LeftCorner.x = Position.x - UI.IO_WIDTH / 2;
	LeftCorner.y = Position.y + UI.IO_HI / 2;

	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.IO_WIDTH / 2;
	Inlet.y = LeftCorner.y - UI.IO_HI;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y;
}


void Write::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawReadWrite(LeftCorner, UI.IO_WIDTH, UI.IO_HI, Text, Selected);

}

void Write::Save(ofstream& file)
{
	
	file << "WRITE" << "        ";
	
	file << ID << "       ";

	file << LeftCorner.x << "       ";
	
	file << LeftCorner.y << "       ";

	file << Variable << "       ";
	file << endl;

	
}

void Write::Load(ifstream& file)
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
	T << "Write " << Variable;
	Text = T.str();
}

void Write::GenerateCode(ofstream& OutFile, string* Vars, int& nVar)
{
	OutFile << "cout << " + Variable + ";\n";
}
bool Write::Validate(string* vars, int& nVars, int& nConn, Output* pOut)
{
	++nConn;        //increment number of connectors
	
	if (!pOutConn)
	{
		pOut->PrintMessage("Chart is not correctly connected");
		return false;
	}

	//if writing a string
	if (Variable[0] == '"' && Variable[Variable.size() - 1] == '"')
		return true;

	//check if variable is initialized before being used
	for (int i = 0; i < nVars; ++i)
	{
		if (Variable == vars[i])
			return true;
	}

	pOut->PrintMessage("Invalid Chart. Variable " + Variable + "is used before being initialized.Click anywhere to continue");
	return false;
}



Connector* Write::Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut)
{
	int i;          //index of the variable to write in variable list

	//checking if writing a string
	if (Variable[0] == '"' && Variable[Variable.size() - 1] == '"')
	{
		pOut->PrintOutput(Variable);
		return pOutConn;
	}

	//Finding variable to write in variable list
	//It must Exist as the chart is validated
	for (i = 0; i < nVars; ++i)
	{
		if (Variable == Vars[i])      
			
			break;
	}


	//Writing value of the variable in the output area
	ostringstream s;
	s << Vals[i];
	pOut->PrintOutput(s.str());


	return pOutConn;
}
