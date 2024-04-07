#include "OperatorAssign.h"
#include <sstream>

using namespace std;

OperatorAssign::OperatorAssign(int id, Point LCorner, string lhs, string Oper1, char Op, string Oper2)
{
	ID = id;        //setting id for statement


	// setting LHS and RHS and copying it to text
	LHS = lhs;

	FirstOperand = Oper1;    //setting Operands and operator
	SecondOperand = Oper2;
	Operator = Op;

	RHS = FirstOperand + " " + Operator + " " + SecondOperand;  //Builing the RHS

	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();


	LeftCorner = LCorner;   //setting Top left corner point 

	pOutConn = NULL;	//No connectors yet

	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.ASSGN_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

}


bool OperatorAssign::IsClicked(Point p)          //states if the point is inside the shape
{
	if (p.x >= LeftCorner.x && p.x <= (LeftCorner.x + UI.ASSGN_WIDTH))
		if (p.y >= LeftCorner.y && p.y <= (LeftCorner.y + UI.ASSGN_HI))
			return true;
	return false;
}

void OperatorAssign::SetOutConn(Connector* pConn)
{
	pOutConn = pConn;
}

Connector* OperatorAssign::GetOutConn()
{
	return pOutConn;
}

Point OperatorAssign::GetInlet()
{
	return Inlet;
}

Point OperatorAssign::GetOutlet()   //returns outlet 
{
	return Outlet;

}

void OperatorAssign::operator=(OperatorAssign C)
{
	LHS = C.LHS;
	RHS = C.RHS;
	Text = C.Text;

	FirstOperand = C.FirstOperand;
	SecondOperand = C.SecondOperand;

	Operator = C.Operator;
}

void OperatorAssign::UpdatePoint(Point Position)
{

	LeftCorner.x = Position.x - UI.ASSGN_WIDTH / 2;
	LeftCorner.y = Position.y - UI.ASSGN_HI / 2;


	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.ASSGN_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void OperatorAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WIDTH, UI.ASSGN_HI, Text, Selected);

}

void OperatorAssign::Save(ofstream& file)
{
	

	file << "OP_ASSIGN" << "    ";
	
	file << ID << "       ";
	
	file << LeftCorner.x << "       ";
	
	file << LeftCorner.y << "       ";
	
	file << LHS << "       ";
	
	file << FirstOperand << "       ";

	

	//setting operator
	if (Operator == '+')
		file << "ADD" << "       ";
	else if (Operator == '-')
		file << "SUB" << "       ";
	else if (Operator == '*')
		file << "MULT" << "       ";
	else if (Operator == '/')
		file << "DIV" << "       ";
	

	
	file << SecondOperand << "       ";

	file << endl;
}

void OperatorAssign::Load(ifstream& file)
{
	string op;
	
	file >> ID;
	
	file >> LeftCorner.x;
	
	file >> LeftCorner.y;
	
	file >> LHS;
	
	file >> FirstOperand;

	file >> op;

	//setting operator
	if (op == "ADD")
		Operator = '+';
	else if (op == "SUB")
		Operator = '-';
	else if (op == "MULT")
		Operator = '*';
	else if (op == "DIV")
		Operator = '/';


	file >> SecondOperand;

	
	//setting inlet and outlet
	Inlet.x = LeftCorner.x + UI.ASSGN_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

	RHS = FirstOperand + " " + Operator + " " + SecondOperand;  //Builing the RHS

	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();


}

void OperatorAssign::GenerateCode(ofstream& OutFile, string* Vars, int &nVar)
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

	OutFile << Text<<";\n";

}

bool OperatorAssign::Validate(string* vars, int& nVars, int& nConn, Output* pOut)
{

	int i; 

	++nConn;        //increment number of connectors

	if (!pOutConn)
	{
		pOut->PrintMessage("Chart is not correctly connected");
		return false;
	}


	if (IsVariable(FirstOperand))
	{
		//check if First operand exists in variable list
		for (i = 0; i < nVars; ++i)
		{
			if (FirstOperand == vars[i])
				break;
		}

		// if FirstOperand doesn't exist in variable list
		if (i == nVars)
		{
			pOut->PrintMessage("Invalid Chart. Variable " + FirstOperand + "is used before being initialized.Click anywhere to continue");
			return false;
		}
	}

	if (IsVariable(SecondOperand))
	{
		//check if Second Operand exists in variable list
		for (i = 0; i < nVars; ++i)
		{
			if (SecondOperand == vars[i])
				break;
		}

		// if SecondOperand doesn't exist in variable list
		if (i == nVars)
		{
			pOut->PrintMessage("Invalid Chart. Variable " + SecondOperand + "is used before being initialized.Click anywhere to continue");
			return false;
		}
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


Connector* OperatorAssign::Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut)
{
	int i;               //index of LHS in variable list
	double D1, D2;       //values of the two Operands



	//Finding RHS in variable list
	//it must exist as the chart is validated
	if (IsVariable(FirstOperand))
	{
		for (int j = 0; j < nVars; ++j)           //finding first operand
		{
			if (FirstOperand == Vars[j])      //if found, get its value and exit the loop
			{
				D1 = Vals[j];
				break;
			}
		}
	}
	else           // if it is not a variable
		D1 = stod(FirstOperand);



	if (IsVariable(SecondOperand))
	{
		for (int k = 0; k < nVars; ++k)           //finding second operand
		{
			if (SecondOperand == Vars[k])      //if found, get its value and exit the loop
			{
				D2 = Vals[k];
				break;
			}
		}
	}
	else      // if it is not a variable
		D2 = stod(SecondOperand);




	


	//checking if LHS exists in variable list
	for (i = 0; i < nVars; ++i)
	{
		if (LHS == Vars[i])         //if it exists, exit the loop
			break;
	}


	//if it doesn't exist, add it
	if (i == nVars)
	{
		Vars[i] = LHS;
		++nVars;
	}



	//checking the operator
	switch (Operator)
	{
	case'+':
		Vals[i] = D1 + D2;
		break;
	case'-':
		Vals[i] = D1 - D2;
		break;
	case'*':
		Vals[i] = D1 * D2;
		break;
	case'/':
		if (D2 != 0.0)           //Check division by zero
		{
			Vals[i] = D1 / D2;
			break;
		}
		else
		{
			pOut->PrintMessage("ERROR!! Dividing by zero"); 
			pIn->GetPointClicked(Point(0,0));
			return NULL;
		}
	}

	return pOutConn;
}