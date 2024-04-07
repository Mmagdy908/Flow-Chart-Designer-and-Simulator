#include <sstream>
#include "End.h"

using namespace std;

End::End(int id, Point center)
{
	ID = id;

	Center = center;

	Inlet.x = Center.x;
	Inlet.y = Center.y - UI.OVAL_HI / 2;

	Text = "End";
}



bool End::IsClicked(Point p)          //states if the point is inside the shape
{
	if (p.x >= (Center.x - UI.OVAL_WIDTH/2) && p.x <= (Center.x + UI.OVAL_WIDTH / 2))
		if (p.y >= (Center.y - UI.OVAL_HI / 2) && p.y <= (Center.y + UI.OVAL_HI / 2))
			return true;
	return false;
}


bool End::IsEnd()
{
	return true;
}

Connector* End::GetOutConn()
{
	return NULL;   //end statement doesn't have out connector
}

Point End::GetInlet()
{
	return Inlet;
}


void End::operator=(End C)
{

}

void End::UpdatePoint(Point Position)
{

	Center = Position;

	

	//setting inlet 
	Inlet.x = Center.x;
	Inlet.y = Center.y - UI.OVAL_HI / 2;
	
}

void End::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawStartEnd(Center, UI.OVAL_WIDTH, UI.OVAL_HI, Text, Selected);

}


void End::Save(ofstream& file)
{
	
	file << "END" << "          ";
	
	file << ID << "       ";
	
	file << Center.x << "       ";
	
	file << Center.y << "       ";
	file << endl;
}

void End::Load(ifstream& file)
{
	file >> ID;
	
	file >> Center.x;
	
	file >> Center.y;
	

	Inlet.x = Center.x;
	Inlet.y = Center.y - UI.OVAL_HI / 2;
}
void End::GenerateCode(ofstream& OutFile, string* Vars, int& nVar)
{
	OutFile << "return 0;\n}";
}
bool End::Validate(string* vars, int& nVars, int& nConn, Output* pOut)
{
	//nConn won't be incremented here
	

	return true;
}
