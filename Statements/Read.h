#pragma once

#include "Statement.h"


//Read statement class
//The Read statement reads a value from the user
class Read : public Statement
{
	string Variable;  //variable to read

	Connector* pOutConn;	//Read Stat. has one Connector to next statement
	

	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//Bottom left corenr of the statement block.

public:
	Read(int id, Point Lcorner, string variable = "");

	bool IsClicked(Point);

	void SetOutConn(Connector* pConn);

	Connector* GetOutConn();

	Point GetInlet();

	Point GetOutlet();

	void operator=(Read C);

	void UpdatePoint(Point);

	void Draw(Output* pOut) const;

	void Save(ofstream& file);

	void Load(ifstream& Infile);

	void GenerateCode(ofstream& OutFile, string* Vars, int& nVar);

	bool Validate(string* vars, int& nVars, int& nConn, Output* pOut);

	Connector* Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut);
	
};