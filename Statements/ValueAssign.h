#ifndef VALUE_ASSIGN_H
#define VALUE_ASSIGN_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class ValueAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	
	Connector *pOutConn;	//Value Assignment Stat. has one Connector to next statement
	                        //Each statement type in flowchart has a predefined number of (output) connectors
	                        //For example, conditional statement always has 2 output connectors

	                        //Note: We don't need to keep track with input connectors
	                        //      Whenever we want to iterate on all statements of the flowchart
	                        //      we will begin with start statement then its output connector
	                        //      then the connector's destination statement and so on (follow the connectors)

	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//Top left corenr of the statement block.

	
public:
	ValueAssign(int id , Point Lcorner, string LeftHS="", double RightHS=0);
	

	bool IsClicked(Point);

	void SetOutConn(Connector* pConn);

	Connector* GetOutConn();

	Point GetInlet();

	Point GetOutlet();

	void operator=(ValueAssign C);

	void UpdatePoint(Point);

	void Save(ofstream& file);

	void Load(ifstream& Infile);

    void Draw(Output* pOut) const;


	void GenerateCode(ofstream& OutFile, string* Vars, int& nVar);

	bool Validate(string* vars, int& nVars, int& nConn, Output* pOut);

	Connector* Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut);

};

#endif