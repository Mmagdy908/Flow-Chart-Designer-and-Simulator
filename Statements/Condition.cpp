#include "Condition.h"


using namespace std;

Condition::Condition(int id, Point LCorner, string operand1, string Op, string operand2)
{
	ID = id;        //setting id for statement
	
	LeftCorner = LCorner;

	pOutConn1 = NULL;	//No connectors yet
	pOutConn2 = NULL;

	//setting inlet and outlets
	Inlet.x = LeftCorner.x + UI.COND_WIDTH / 2;
	Inlet.y = LeftCorner.y - UI.COND_HI / 2;

	InletLoop.x = LeftCorner.x + UI.COND_WIDTH / 2;
	InletLoop.y = LeftCorner.y + UI.COND_HI / 2;

	OutletR.x = LeftCorner.x + UI.COND_WIDTH;
	OutletR.y = LeftCorner.y;

	OutletL.x = LeftCorner.x;
	OutletL.y = LeftCorner.y;

	//seting LHS, RHS, Comparison Operator
	FirstOperand = operand1;              
	SecondOperand = operand2;
	Operator = Op;

	//Build the statement text: Left handside then equals then right handside
	stringstream T;
	T << FirstOperand << " " << Operator << " " << SecondOperand;
	Text = T.str();

	Looping = 0;

	nIterations = 0;
}

bool Condition::IsClicked(Point p)          //states if the point is inside the shape
{
	if (p.x >= LeftCorner.x && p.x <= (LeftCorner.x + UI.COND_WIDTH))
		if (p.y >= (LeftCorner.y - UI.COND_HI / 2) && p.y <= (LeftCorner.y + UI.COND_HI / 2))
			return true;
	return false;
}

bool Condition::IsCondition()
{
	return true;
}


void Condition::SetOutConn(Connector* pConn)      //sets Yes connector
{
	pOutConn1 = pConn;
}
Connector* Condition::GetOutConn()     //return yes connector
{
	return pOutConn1;
}

Connector* Condition::GetNoOutConn()    //return No connector
{
	return pOutConn2;
}

void Condition::SetNoOutConn(Connector* pConn)  //sets No connector
{
	pOutConn2 = pConn;
}


Point Condition::GetInlet()
{
	return Inlet;
}

Point Condition::GetInletLoop()
{
	return InletLoop;
}

Point Condition::GetOutlet()   //returns right outlet 
{
	return OutletR;

}

Point Condition::GetOutletL()  //returns left outlet 
{
	return OutletL;
}

void Condition::operator=(Condition C)
{
	Text = C.Text;
	FirstOperand = C.FirstOperand;
	SecondOperand = C.SecondOperand;
	Operator = C.Operator;
}

void Condition::UpdatePoint(Point Position)
{

	LeftCorner.x = Position.x - UI.COND_WIDTH / 2;

	LeftCorner.y = Position.y;

	//setting inlet and outlets
	Inlet.x = LeftCorner.x + UI.COND_WIDTH / 2;
	Inlet.y = LeftCorner.y - UI.COND_HI / 2;

	InletLoop.x = LeftCorner.x + UI.COND_WIDTH / 2;
	InletLoop.y = LeftCorner.y + UI.COND_HI / 2;

	OutletR.x = LeftCorner.x + UI.COND_WIDTH;
	OutletR.y = LeftCorner.y;

	OutletL.x = LeftCorner.x;
	OutletL.y = LeftCorner.y;
}
void Condition::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw Conditional statement 	
	pOut->DrawConditionalstat(LeftCorner, UI.COND_WIDTH, UI.COND_HI, Text, Selected);
}

void Condition::SetLooping(int l)
{
	Looping = l;
}

int Condition::GetLooping()
{
	return Looping;
}

int Condition::GetnIterations()
{
	return nIterations;
}

void Condition::Save(ofstream& file)
{
	

	file << "COND" << "         ";
	
	file << ID << "       ";
	
	file << LeftCorner.x << "       ";
	
	file << LeftCorner.y << "       ";
	
	file << FirstOperand << "       ";
	

	//setting operator
	if(Operator==">")
		file << "GRT" << "       ";
	else if (Operator == "<")
		file << "LESS" << "       ";
	else if (Operator == ">=")
		file << "GRTOREQ" << "       ";
	else if (Operator == "<=")
		file << "LESSOREQ" << "       ";
	else if (Operator == "==")
		file << "EQ" << "       ";
	else if (Operator == "!=")
		file << "NOTEQ" << "       ";

	
	file << SecondOperand << "       ";

	file << endl;
}

void Condition::Load(ifstream& file)
{

	string op;
	
	file >> ID;

	file >> LeftCorner.x;
	
	file >> LeftCorner.y;
	
	file >> FirstOperand;
	
	file >> op;

	//setting operator
	if (op == "GRT")
		Operator = ">";

	else if (op == "LESS")
		Operator = "<";

	else if (op == "GRTOREQ")
		Operator = ">=";

	else if (op == "LESSOREQ")
		Operator = "<=";

	else if (op == "EQ")
		Operator = "==";

	else if (op == "NOTEQ")
		Operator = "!=";

	file >>SecondOperand;


	//setting inlet and outlets
	Inlet.x = LeftCorner.x + UI.COND_WIDTH / 2;
	Inlet.y = LeftCorner.y - UI.COND_HI / 2;

	InletLoop.x = LeftCorner.x + UI.COND_WIDTH / 2;
	InletLoop.y = LeftCorner.y + UI.COND_HI / 2;

	OutletR.x = LeftCorner.x + UI.COND_WIDTH;
	OutletR.y = LeftCorner.y;

	OutletL.x = LeftCorner.x;
	OutletL.y = LeftCorner.y;

	InletLoop.x = LeftCorner.x + UI.COND_WIDTH / 2;
	InletLoop.y = LeftCorner.y + UI.COND_HI / 2;


	stringstream T;
	T << FirstOperand << " " << Operator << " " << SecondOperand;
	Text = T.str();

}

void Condition::GenerateCode(ofstream& OutFile, string* Vars, int& nVar)
{
	if (Looping == 0)
	{
		OutFile << "if (" + Text + ")\n{\n";
	}
	else if (Looping == 1)
	{
		OutFile << "while (" + Text + ")\n{\n";
	}
	else
	{
		OutFile << "while (!(" + Text + "))\n{\n";
	}
}

bool Condition::Validate(string* vars, int& nVars, int& nConn, Output* pOut)
{

	int i;

	nConn+=2;        //increment number of connectors
	                 //conition statement has 2 out connectors
	if (!pOutConn1 || !pOutConn2)
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
			pOut->PrintMessage("Invalid Chart. Variable " + FirstOperand + " is used before being initialized.Click anywhere to continue");
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
			pOut->PrintMessage("Invalid Chart. Variable " + SecondOperand + " is used before being initialized.Click anywhere to continue");
			return false;
		}
	}

	return true;
}

Connector* Condition::Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut)
{
	int j, k;                    //indices of the two operands if they are variables
	double D1, D2;               //values of the two Operands
	bool CheckCondition = false; //Condition result->true Or flase

	nIterations++;   //increment no. of iterations

	if (nIterations > MaxIterations)
	{
		nIterations = 0;
		pOut->PrintMessage("ERROR!!There is an infinite loop. Click anywhere to continue");
		pIn->GetPointClicked(Point(0, 0));
		return NULL;
	}

	//Finding Two operands in variable list
	//it must exist as the chart is validated
	for (j = 0; j < nVars; ++j)           //finding first operand
	{
		if (FirstOperand == Vars[j])      //if found, get its value and exit the loop
		{
			D1 = Vals[j];
			break;
		}
	}


	for (k = 0; k < nVars; ++k)           //finding second operand
	{
		if (SecondOperand == Vars[k])     //if found, get its value and exit the loop
		{
			D2 = Vals[k];
			break;
		}
	}


	if (j == nVars)                        //if First Operand is not variable
	{
		D1 = stod(FirstOperand);
	}

	if (k == nVars)                        //if second Operand is not variable
	{
		D2 = stod(SecondOperand);
	}






	//checking the operator
	if (Operator == ">")
	{
		if (D1 > D2)               //Checking the condition
			CheckCondition = true;	
	}

	if (Operator == "<")
	{
		if (D1 < D2)               //Checking the condition
			CheckCondition = true;
	}

	if (Operator == "==")
	{
		if (D1 == D2)               //Checking the condition
			CheckCondition = true;
	}

	if (Operator == "!=")
	{
		if (D1 != D2)               //Checking the condition
			CheckCondition = true;
	}

	if (Operator == ">=")
	{
		if (D1 >= D2)               //Checking the condition
			CheckCondition = true;
	}
	if (Operator == "<=")
	{
		if (D1 <= D2)               //Checking the condition
			CheckCondition = true;
	}

	if (CheckCondition)
	{
		if (Looping == 2)
			nIterations = 0;
		return pOutConn1;
	}
	else
	{
		if (Looping == 1)
			nIterations = 0;
		return pOutConn2;
	}
	
}