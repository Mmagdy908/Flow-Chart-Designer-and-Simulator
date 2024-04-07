#include "Statement.h"

Statement::Statement()	
{ 
	Text = "";
	Selected = false;		
}


void Statement::UpdateID(int id)
{
	ID=id;
}

int Statement::GetID()
{
	return ID;
}

void Statement::SetSelected(bool s)
{   Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }


bool Statement::IsStart()
{
	return false;
}

bool Statement::IsCondition()
{
	return false;
}


bool Statement::IsEnd()
{
	return false;
}

Point Statement::GetInlet()
{
	return Point(0, 0);
}

Point Statement::GetInletLoop()
{
	return Point(0, 0);
}

Point Statement::GetOutlet()
{
	return Point(0, 0);
}

Point Statement::GetOutletL()
{
	return Point(0, 0);
}


Connector* Statement::GetNoOutConn()  //returns null for all statements except condition statement
{
	return NULL;
}




