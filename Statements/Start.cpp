#include "Start.h"

using namespace std;

Start::Start(int id, Point center)
{
	ID = id;

	Center = center;

	pOutConn = NULL;	//No connectors yet

	Outlet.x = Center.x;
	Outlet.y = Center.y + UI.OVAL_HI / 2;

	Text = "Start";
}


bool Start::IsClicked(Point p)          //states if the point is inside the shape
{
	if (p.x >= (Center.x - UI.OVAL_WIDTH / 2) && p.x <= (Center.x + UI.OVAL_WIDTH / 2))
		if (p.y >= (Center.y - UI.OVAL_HI / 2) && p.y <= (Center.y + UI.OVAL_HI / 2))
			return true;
	return false;
}

bool Start::IsStart()
{
	return true;
}


void Start::SetOutConn(Connector* pConn)
{
	pOutConn = pConn;
}

Connector* Start::GetOutConn()
{
	return pOutConn;
}


Point Start::GetOutlet()   //returns outlet 
{
	return Outlet;

}

void Start::operator=(Start C)
{
	
}

void Start::UpdatePoint(Point Position)
{

	Center = Position;



	//setting inlet 
	Outlet.x = Center.x;
	Outlet.y = Center.y + UI.OVAL_HI / 2;

}

void Start::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawStartEnd(Center, UI.OVAL_WIDTH, UI.OVAL_HI, Text, Selected);

}

void Start::Save(ofstream& file)
{
	
	file << "STRT" << "         ";
	
	file << ID << "       ";

	file << Center.x << "       ";
	
	file << Center.y << "       ";
	file << endl;
}

void Start::Load(ifstream& file)
{
	file >> ID;

	file >> Center.x;

	file >> Center.y;


	Outlet.x = Center.x;
	Outlet.y = Center.y + UI.OVAL_HI / 2;
}

void Start::GenerateCode(ofstream& OutFile, string* Vars, int& nVar)
{
	OutFile << "#include <iostream>\n\n";

	OutFile << "using namespace std;\n\n";

	OutFile << "int main()\n{\n";
}

bool Start::Validate(string* vars, int& nVars, int& nConn, Output* pOut)
{
	++nConn;        //increment number of connectors

	if (!pOutConn)
	{
		pOut->PrintMessage("Chart is not correctly connected");
		return false;
	}
	return true;
}


Connector* Start::Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut)
{
	
	pOut->ClearOutputBar();            //clear Output area before running

	return pOutConn;
}

