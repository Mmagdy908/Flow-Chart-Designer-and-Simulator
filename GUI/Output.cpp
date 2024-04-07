#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1250;
	UI.height = 850;
	UI.wx = 15;
	UI.wy =15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 60;
	UI.DrawingAreaWidth = 0.75 * UI.width;
	UI.OutputBarHeight = 0.5 * (UI.height - UI.StatusBarHeight - UI.ToolBarHeight);

	UI.DrawColor = BLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = RED;

	UI.OVAL_WIDTH = 100;
	UI.OVAL_HI = 60;
	UI.ASSGN_WIDTH = 220;
	UI.ASSGN_HI = 50;
	UI.COND_WIDTH = 220;
	UI.COND_HI = 80;
	UI.IO_WIDTH = 180;
	UI.IO_HI = 60;

	UI.nOutputLines = 0;
	UI.nDebugLines = 0;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");
	
	pWind->SetPen(RED,3);
	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
	ClearDebugBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode

	//fill the tool bar 

	
	string MenuItemImages[DSN_ITM_CNT];
	MenuItemImages[ITM_START] = "images\\start.jpg";
	MenuItemImages[ITM_END] = "images\\end.jpg";
	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\val.jpg";
	MenuItemImages[ITM_VARIABLE_ASSIGN] = "images\\var.jpg";
	MenuItemImages[ITM_OPER_ASSIGN] = "images\\op.jpg";
	MenuItemImages[ITM_COND] = "images\\Condition.jpg";
	MenuItemImages[ITM_READ] = "images\\read.jpg";
	MenuItemImages[ITM_WRITE] = "images\\write.jpg";
	MenuItemImages[ITM_CONNECTOR] = "images\\connector.jpg";
	MenuItemImages[ITM_SELECT] = "images\\select.jpg";
	MenuItemImages[ITM_DELETE] = "images\\delete.jpg";
	MenuItemImages[ITM_COPY] = "images\\copy.jpg";
	MenuItemImages[ITM_PASTE] = "images\\paste.jpg";
	MenuItemImages[ITM_SAVE] = "images\\save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\load.jpg";
	MenuItemImages[ITM_SIM_SWITCH] = "images\\switch.jpg";
	MenuItemImages[ITM_D_EXIT] = "images\\exit.jpg";


	//Draw menu item one image at a time
	pWind->SetPen(RED, 4);
	for (int i = 0; i < DSN_ITM_CNT; i++)
	{
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
		pWind->DrawLine((i+1) * UI.MenuItemWidth, 0, (i + 1) * UI.MenuItemWidth, UI.ToolBarHeight);
	}

	//Draw a line above the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, 0, UI.width, 0);
	//Draw a line under the toolbar
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	string MenuItemImages[SIM_ITM_CNT];
	MenuItemImages[ITM_DEBUG] = "images\\Debug.jpg";
	MenuItemImages[ITM_CPP] = "images\\cpp.jpg";
	MenuItemImages[ITM_VALIDATE] = "images\\validate.jpg";
	MenuItemImages[ITM_RUN] = "images\\run.jpg";
	MenuItemImages[ITM_DES_SWITCH] = "images\\switch.jpg";
	MenuItemImages[ITM_S_EXIT] = "images\\exit.jpg";

	//Draw the simulation toolbar
	pWind->SetPen(RED, 4);
	for (int i = 0; i < SIM_ITM_CNT; i++)
	{
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
		pWind->DrawLine((i + 1) * UI.MenuItemWidth, 0, (i + 1) * UI.MenuItemWidth, UI.ToolBarHeight);
	}
	//Draw a line above the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, 0, UI.width, 0);
	//Draw a line under the toolbar
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearToolbar()   //clears the toolbar
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
/// ///////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	UI.nOutputLines = 0;
	pWind->SetPen(RED, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.ToolBarHeight + UI.OutputBarHeight);
	pWind->SetPen(BLUE, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(0.5 * UI.DrawingAreaWidth + 0.5 * UI.width - 40, UI.ToolBarHeight + 10, "OutPut");
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDebugBar()
{
	//Create debug bar by drawing a filled rectangle
	UI.nDebugLines = 0;
	pWind->SetPen(RED, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight + UI.OutputBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	pWind->SetPen(BLUE, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(0.5 * UI.DrawingAreaWidth + 0.5 * UI.width - 40, UI.ToolBarHeight + UI.OutputBarHeight + 10, "Debug");
}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int) (UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintOutput(string output)	//Prints output on Output bar
{
	
	pWind->SetPen(BLACK, 50);
	pWind->SetFont(15, BOLD, BY_NAME, "Arial");
	pWind->DrawString(UI.DrawingAreaWidth + 10, UI.ToolBarHeight + 30 + 20 * UI.nOutputLines, output);
	++UI.nOutputLines;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintDebug(string* Vars,double* Vals, int nVars)	//Prints Debug on Debug bar
{
	stringstream s;
	string line;
	ClearDebugBar();
	pWind->SetPen(BLACK, 50);
	pWind->SetFont(15, BOLD, BY_NAME, "Arial");
	for (int i = 0; i < nVars; ++i)
	{
		s.str("");
		s << Vals[i];
		line = Vars[i] + " = " + s.str();
		pWind->DrawString(UI.DrawingAreaWidth + 10, UI.ToolBarHeight+ UI.OutputBarHeight + 30 + 20 * UI.nDebugLines, line);
		++UI.nDebugLines;
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height ,string Text, bool Selected)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(Left.x+ width /2 - Text.size() * 4, Left.y + height /4, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawStartEnd(Point cen, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the statement block Oval
	pWind->DrawEllipse(cen.x - width / 2, cen.y - height / 2, cen.x + width / 2, cen.y + height / 2);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(cen.x -17, cen.y-10 , Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawReadWrite(Point start, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the statement block //gram
	int x[4], y[4];
	x[0] = start.x;
	y[0] = start.y;
	x[1] = x[0] + 0.75 * width;
	x[2] = x[0] + width;
	x[3] = x[0] + 0.25 * width;
	y[1] = y[0];
	y[2] = y[0] - height;
	y[3] = y[2];

	pWind->DrawPolygon(x,y,4);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString((x[0] + 0.5 * width - Text.size() * 4), (y[0] - 0.7 * height), Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawConditionalstat(Point Left, int width, int height, string Text, bool Selected)
{
	// array of points for the diamond shape
	int x[4] = { Left.x, Left.x + width/2, Left.x + width,Left.x + width/2};
	int y[4] = { Left.y,Left.y + height / 2, Left.y, Left.y - height / 2 };

	if (Selected)    //if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);     //use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);       //use normal color

	// Draw the diamond shape
	pWind->DrawPolygon(x, y, 4);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString((x[0] + 0.5 * width - Text.size() * 4), (y[0] - 0.1 * height), Text);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawConnectors(Point A, Point B, bool Selected, string Text)
{
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(BLACK, 3);
															  //      "Yes/No"
	if (Text != "")										      //  A ______________
	{														  //                 |
		pWind->DrawLine(A.x, A.y, B.x, A.y);			      //                 |
		pWind->DrawLine(B.x, A.y, B.x, B.y);				  //                 |
															  //                 B  
	}


	else                                                      // else it draws a regular connector
	{                                                         //                                      A     
		if (B.y > A.y+20)                                     //here it draws the connector like this |_______  as long as y2 > y1 + 20    
		{                                                     //                                             |
			pWind->DrawLine(A.x, A.y, A.x, (A.y + B.y) / 2);  //                                             B
			pWind->DrawLine(A.x, (A.y + B.y) / 2, B.x, (A.y + B.y) / 2);  // the + 20 is there to avoid this :  A_____  
			pWind->DrawLine(B.x, (A.y + B.y) / 2, B.x, B.y);              //                                          B

		}  
		                                                      //                                             |-----|
		else if (B.y > A.y)                                   //                                       A     |     |                          
		{                                                     // here it draws the connector like this |     |     B as long as y1 + 20 >= y2    
			pWind->DrawLine(A.x, A.y, A.x, A.y + 15);         //                                       |_____|
			pWind->DrawLine(A.x, A.y + 15, (A.x + B.x) / 2, A.y + 15);
			pWind->DrawLine((A.x + B.x) / 2, A.y + 15, (A.x + B.x) / 2, B.y - 15);
			pWind->DrawLine((A.x + B.x) / 2, B.y - 15, B.x, B.y - 15);
			pWind->DrawLine(B.x, B.y - 15, B.x, B.y);
		}
		else
		{
			pWind->DrawLine(A.x, A.y, A.x, A.y + 15);         //                B                            
			pWind->DrawLine(A.x, A.y + 15, B.x, A.y + 15);    //          A     | 
			pWind->DrawLine(B.x, A.y + 15, B.x, B.y);         //          |_____|
		}
	}


	//Draw Down Arrow Tip
	if (B.y > A.y)
	{
		pWind->DrawLine(B.x, B.y, B.x - 5, B.y - 5);
		pWind->DrawLine(B.x, B.y, B.x + 5, B.y - 5);
	}
	//Draw Up Arrow Tip
	else
	{
		pWind->DrawLine(B.x, B.y, B.x - 5, B.y + 5);
		pWind->DrawLine(B.x, B.y, B.x + 5, B.y + 5);
	}


	//Write connector text
	pWind->SetPen(BLACK, 2);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(A.x + (B.x - A.x) / 2 - 10, A.y - 20, Text);


	//drawing selection box
	if (Text == "")
		pWind->DrawRectangle(A.x - 5, A.y + 10, A.x + 5, A.y + 20);
	else if (B.x > A.x)
		pWind->DrawRectangle(A.x + 10, A.y - 5, A.x + 20, A.y + 5);
	else 
		pWind->DrawRectangle(A.x - 10, A.y - 5, A.x - 20, A.y + 5);

}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}
