#include "Connector.h"
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include "Statements\Statement.h"


Connector::Connector(Statement* Src, Statement* Dst, int Outlet)
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{
	
	SrcStat = Src;
	DstStat = Dst;

	
	Selected = false;
	OutletBranch = Outlet;
}



void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

int Connector::GetOutletBranch()
{
	return OutletBranch;
}

void Connector::SetSelected(bool s)
{
	Selected = s;
}

void Connector::Save(ofstream& File)
{
	
	  
	File << SrcStat->GetID() << "       ";

	
	File << DstStat->GetID() << "       ";

	
	File << OutletBranch << "       ";

	File << endl;

}


bool Connector::IsSelected() const
{
	return Selected;
}

bool Connector::IsClicked(Point P)
{
	if (P.x >= Start.x - 5 && P.x <= Start.x + 5 && P.y >= Start.y + 10 && P.y <= Start.y + 20)
		return true;

	return false;
}

void Connector::Draw(Output* pOut) const
{
	string Text = "";

	//setting text in cae of conditional statement
	if (OutletBranch == 1)
		Text = "YES";
	else if (OutletBranch == 2)
		Text = "NO";

	pOut->DrawConnectors(Start, End, Selected, Text);
}


