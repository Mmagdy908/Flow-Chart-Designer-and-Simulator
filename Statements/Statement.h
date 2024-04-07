//#ifndef STATEMENT_H
//#define STATEMENT_H
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "..\defs.h"
#include "..\Connector.h"
//class Output;
#include "..\GUI\Output.h"
#include <sstream>
#include <fstream>


//Base class for all Statements
class Statement
{
protected:
	int ID;			//Each Statement has an ID --> must be unique
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart



public:
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;
	virtual bool IsClicked(Point) = 0;         //states if the point is inside the shape

	virtual bool IsStart();                   //checks if statement is start statement


	virtual bool IsCondition();                   //checks if statement is Conditional statement

	virtual bool IsEnd();                   //checks if statement is End statement

	virtual void SetOutConn(Connector* pConn) {}

	virtual Connector* GetOutConn() = 0;

	virtual Connector* GetNoOutConn();

	virtual void SetNoOutConn(Connector * pConn) {}

	virtual Point GetInlet();
	virtual Point GetInletLoop();

	virtual Point GetOutlet();

	virtual Point GetOutletL();

	void UpdateID(int);

	int GetID();

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement


	virtual void SetLooping(int l) {}

	virtual int GetLooping() { return 0; }


	virtual void Save(ofstream& OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file



	 // validate the statement
	 //it takes list of variable, no.of existing variables, no. of connectors,
	 //no. of start and end statements
	virtual bool Validate(string* vars, int& nVars, int& nConn, Output* pOut) = 0;  
	
	//Execute the statement in the simulation mode
	virtual Connector* Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut) = 0;	

	//virtual void Simulate();              	//Execute the statement in the simulation mode
	virtual void GenerateCode(ofstream& OutFile, string* Vars, int& nVar) = 0;	//write the statement code to a file


};

//#endif