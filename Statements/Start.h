#ifndef START_H
#define START_H

#include "Statement.h"

//Start statement class
//The Start statement is the begining statment of the flowchart  
class Start : public Statement
{
private:


	Connector* pOutConn;	//Start Stat. has one Connector to next statement
	//Each statement type in flowchart has a predefined number of (output) connectors
	//For example, conditional statement always has 2 output connectors

	//Note: We don't need to keep track with input connectors
	//      Whenever we want to iterate on all statements of the flowchart
	//      we will begin with start statement then its output connector
	//      then the connector's destination statement and so on (follow the connectors)

	
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector

	Point Center;	//Center of the statement block.


public:
	Start(int id, Point center);

	bool IsClicked(Point);

	bool IsStart();

	void SetOutConn(Connector* pConn);

	Connector* GetOutConn();

	Point GetOutlet();

	void operator=(Start C);

	void UpdatePoint(Point);

	void Save(ofstream& file);

	void Load(ifstream& Infile);

	virtual void Draw(Output* pOut) const;


	void GenerateCode(ofstream& OutFile, string* Vars, int& nVar);

	bool Validate(string* vars, int& nVars, int& nConn, Output* pOut);

	Connector* Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut);
};

#endif