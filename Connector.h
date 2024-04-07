#pragma once
//#ifndef CONNECTOR_H
//#define CONNECTOR_H

#include "GUI\UI_Info.h"
#include "GUI\output.h"
#include <fstream>

class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:

	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	bool Selected;
	int OutletBranch;   // 1->Yes branch   2->NO branch   0->otherwise
public:
	Connector(Statement* Src, Statement* Dst, int Outlet);

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void SetSelected(bool s);
	

	bool IsSelected() const;
	bool IsClicked(Point P);    //checks if the connector is clicked

	int GetOutletBranch();

	void Draw(Output* pOut) const;

	void Save(ofstream& File);

};

//#endif