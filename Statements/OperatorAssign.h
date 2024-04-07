#ifndef OPERATOR_ASSIGN_H
#define OPERATOR_ASSIGN_H

#include "Statement.h"


class OperatorAssign : public Statement
{
	string LHS;              //represents the variable we want to assign to
	string RHS;              //represents the whole expression we want to assign to LHS

	string FirstOperand;     //these are the operands and the operator
	string SecondOperand;    //all o them are parts of right handside
	char Operator; 

	Connector* pOutConn;	//Operator Assignment Stat. has one Connector to next statement
	                        
	                        

	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//Top left corenr of the statement block.

	

public:

	OperatorAssign(int id, Point LCorner, string lhs = "", string Oper1 = "", char Op = '\0', string Oper2 = "");


	bool IsClicked(Point);

	void SetOutConn(Connector* pConn);


	Connector* GetOutConn();

	Point GetInlet();

	Point GetOutlet();

	void operator=(OperatorAssign C);

	void UpdatePoint(Point);

	void Draw(Output* pOut) const;

	void Save(ofstream& file);

	void Load(ifstream& Infile);

	void GenerateCode(ofstream& OutFile, string* Vars, int& nVar);


	bool Validate(string* vars, int& nVars, int& nConn, Output* pOut);


	Connector* Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut);
};

#endif