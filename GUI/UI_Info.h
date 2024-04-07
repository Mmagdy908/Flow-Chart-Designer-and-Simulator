#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\DEFS.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	
	int width, height;	//Window width and height
	int wx, wy;			//Window starting coordinates

	int StatusBarHeight;	//Status Bar Width
	int ToolBarHeight;		//Tool Bar Width
	int MenuItemWidth;		//Menu Item Width
	int DrawingAreaWidth;   //Drawing Area Width
	int OutputBarHeight;
	
	color DrawColor;		//Drawing color
	color HighlightColor;		//Highlighting color
	color MsgColor;		//Messages color

	int OVAL_WIDTH;     //Start end statement default width
	int OVAL_HI;        //Start end statement default height
	int ASSGN_WIDTH;		//Assignment statement default width
	int ASSGN_HI;		//Assignment statement default height
	int COND_WIDTH;     //Conditional statement default width
	int COND_HI;        //Conditional statement default height
	int IO_WIDTH;       //I/O statement default width
	int IO_HI;          //I/O statement default height

	int nOutputLines;    //number of printed lines of output
	int nDebugLines;    //number of printed lines of debugging
	
}UI;	//create a single global object UI

struct Point	
{
	int x,y;
	Point(int a=0, int b=0)	//constructor
	{ x=a;	y=b;	}
};

#endif