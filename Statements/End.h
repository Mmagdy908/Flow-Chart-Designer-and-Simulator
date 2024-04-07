#ifndef END_H
#define END_H

#include "Statement.h"

//End statement class
//The End statement is the begining statment of the flowchart  
class End : public Statement
{
private:


	//End Stat. has no Connector to next statement as there is no statements after it


	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	
	//Note that End statement has no outlet point for connectors as it is the last statement

	Point Center;	//Center of the statement block.


public:
	End(int id, Point center);

	bool IsClicked(Point);

	bool IsEnd();

	Connector* GetOutConn();

	Point GetInlet();

	void operator=(End C);

	void Save(ofstream& file);

	void Load(ifstream& Infile);


	void UpdatePoint(Point);


	virtual void Draw(Output* pOut) const;

	void GenerateCode(ofstream& OutFile, string* Vars, int& nVar);

	bool Validate(string* vars, int& nVars, int& nConn, Output* pOut);

	Connector* End::Simulate(string* Vars, double* Vals, int& nVars, Input* pIn, Output* pOut) { return NULL; }

};

#endif
