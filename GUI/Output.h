#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"
#include <sstream>

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();	

	window* CreateWind(int, int, int , int);
	Input* CreateInput(); //Creates a pointer to the Input object	

	void CreateStatusBar(); //Creates status bar


	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar(); //Tool bar of the simulation mode
	void ClearToolbar();

	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area
	void ClearOutputBar();  //Clears the Output bar
	void ClearDebugBar();   //Clears the Debug bar
	
	void PrintMessage(string msg);	//Prints a message on Status bar
	void DrawString(const int, const int, const string);  //Writes a string in the specified location
	void PrintOutput(string output);	//Prints output on Output bar
	void PrintDebug(string* Vars, double* Vals, int nVars);	//Prints Debug on Debug bar

	// -- Statements Drawing Functions
	void DrawAssign(Point Left, int width, int height, string Text, bool Selected=false);
	void DrawConditionalstat(Point Left, int width, int height, string Text, bool Selected=false);
	void DrawConnectors(Point A,Point B,  bool Selected = false, string text = "");
	void DrawStartEnd(Point cen, int width, int height, string Text, bool Selected = false);
	void DrawReadWrite(Point start, int width, int height, string text, bool Selected=false);
	
	
	~Output();
};

#endif