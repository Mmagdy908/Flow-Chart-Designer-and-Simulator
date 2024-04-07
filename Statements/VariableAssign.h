#ifndef VARIABLE_ASSIGN_H
#define VARIABLE_ASSIGN_H

#include "Statement.h"

//Variable Assignment statement class
//The variable assignment statement assigns a value of a varible to a variable
class VariableAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (namr of a Variable)

	Connector* pOutConn;	//Variable Assignment Stat. has one Connector to next statement
	                        

	

	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector
 
	Point LeftCorner;	//Top left corenr of the statement block.


public:
	VariableAssign(int id, Point Lcorner, string LeftHS = "", string RightHS = "");


	bool IsClicked(Point);

	void SetOutConn(Connector* pConn);

	Connector* GetOutConn();

	Point GetInlet();

	Point GetOutlet();

	void operator=(VariableAssign C);

	void UpdatePoint(Point);

	void Save(ofstream& file);

	void Load(ifstream& Infile);

	virtual void Draw(Output* pOut) const;

	void GenerateCode(ofstream& OutFile, string* Vars, int& nVar);

	bool Validate(string* vars, int& nVars, int& nConn, Output* pOut);


	Connector* Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut);

};

#endif
