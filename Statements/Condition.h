#pragma once

#include "Statement.h"

class Condition : public Statement
{
	string FirstOperand;              //represents the first operand of comparison
	string SecondOperand;             //represents the second operand of comparison

	string Operator;         //represents the comparison operator

	//Conditional Stat. has two Connector to next statements
	Connector* pOutConn1;	//this is yes conncector
	Connector* pOutConn2;   //this is no conncector


	Point Inlet;	 //A point where connections enters this statement 
	                 //It's used as the (End) point of the (Input) connectors
	Point InletLoop; //bottom inlet in case of loop
	//This stat. has two outlets
	Point OutletR;	        //right outlet
	Point OutletL;          //left outlet

	Point LeftCorner;	//left corenr of the statement block.

	int Looping;       //indicates if condition is looping
	                   //0->not looping   1->looping in yes direction   2->looping in no direction

	int nIterations;

	int MaxIterations = 10000;
public:

	Condition(int id, Point LCorner, string operand1 = "", string Op = "", string operand2 = "");

	bool IsClicked(Point);

	bool IsCondition();

	void SetOutConn(Connector* pConn);

	Connector* GetOutConn();

	Connector* GetNoOutConn();

	void SetNoOutConn(Connector* pConn);
	
	Point GetInlet();

	Point GetInletLoop();

	Point GetOutlet();

	Point GetOutletL();

	void operator=(Condition C);

	void UpdatePoint(Point);

	void SetLooping(int l);

	int GetLooping();

	int GetnIterations();

	void Save(ofstream& file);

	void Load(ifstream& Infile);

	void Draw(Output* pOut) const;


	void GenerateCode(ofstream& OutFile, string* Vars, int& nVar);

	bool Validate(string* vars, int& nVars, int& nConn, Output* pOut);

	Connector* Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut);

};