
#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

string Input::GetString(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		 if (pO)
			pO->PrintMessage(Label);
	}
}

string Input::GetVariable(Output* pO) const  // Reads a Variable name from the user 
{
	string Variable;

	pO->PrintMessage("Please enter a Variable name");

	while (1)
	{
		Variable = GetString(pO);
		if (IsVariable(Variable))   // checks if the entered string is a variable
		{
			return Variable;        // return variable if true
		}
		else                        // else ask user to enter a valid variable name
		{
			//Error message
			pO->PrintMessage("Invalid Variable name, Please enter a valid Variable name");
		}
	}// End of loop
}


double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{

	double D = 0;
		
	//This function should make any needed validations on the entered text 
	// to make sure it is a double value (e.g. 12.5, -12.5, -23, -23., -23.0 …etc.).

	
	//Read a double value from the user
	string input = GetString(pO);
	while (!IsValue(input))
	{
		pO->PrintMessage("Please enter a value");
		input = GetString(pO);
	}
	D = stod(input); //stringToDouble
	return D;
}

char Input::GetArithOperator(Output* pO) {
	string Label;

	pO->PrintMessage("Please Enter an arithmatic Operator(+,-,*,/)");
	while (1)
	{
		Label = GetString(pO);

		if ((Label == "+") || (Label == "-") || (Label == "*") || (Label == "/"))
			return Label[0];
		else
		{

			//Error message
			pO->PrintMessage("Invalid Operator Entered, Please Enter a valid Operator(+,-,*,/)");
		}

	} //End of while loop
}

string Input::GetCompOperator(Output* pO) {
	string Label;

	pO->PrintMessage("Please Enter an comparison Operator");
	while (1)
	{
		Label = GetString(pO);

		if ((Label == ">") || (Label == "<") || (Label == ">=") || (Label == "<=") || (Label == "==") || (Label == "!="))
			return Label;
		else
		{
			pO->PrintMessage("Invalid Comparison Operator Entered");
		}
	} //End of while loop
}


ActionType Input::GetUserAction() const
{	
	//This function reads the position where the user clicks to determine the desired action

	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	//Check whick Menu item was clicked
	//This assumes that menu items are lined up horizontally
	int ClickedItem = (x / UI.MenuItemWidth);
	//Divide x coord of the point clicked by the menu item width (int division)
	//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
	
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			if (UI.AppMode == DESIGN)	//application is in design mode
			{
				
				switch (ClickedItem)
				{
				case ITM_START: return ADD_START;
				case ITM_END: return ADD_END;
				case ITM_VALUE_ASSIGN: return ADD_VALUE_ASSIGN;
				case ITM_VARIABLE_ASSIGN: return ADD_VAR_ASSIGN;
				case ITM_OPER_ASSIGN: return ADD_OPER_ASSIGN;
				case ITM_COND: return ADD_CONDITION;
				case ITM_READ: return ADD_READ;
				case ITM_WRITE: return ADD_WRITE;
				case ITM_CONNECTOR: return ADD_CONNECTOR;
				case ITM_SELECT: return SELECT;
				case ITM_DELETE: return DEL;
				case ITM_COPY: return COPY;
				case ITM_PASTE: return PASTE;
				case ITM_SAVE: return SAVE;
				case ITM_LOAD: return LOAD;
				case ITM_SIM_SWITCH: return SWITCH_SIM_MODE;
				case ITM_D_EXIT: return EXIT;

				default: return DSN_TOOL;
				}
			}
			else	//Application is in Simulation mode
			{
				switch (ClickedItem)
				{
				case ITM_CPP: return Convert_CPP;            //convert to cpp file
				case ITM_VALIDATE: return VALIDATE;	         //Validate
				case ITM_RUN: return RUN;	                 //Run
				case ITM_DEBUG: return DEBUG;	                 //Run
				case ITM_DES_SWITCH: return SWITCH_DSN_MODE; //switch to design mode
				case ITM_S_EXIT: return EXIT;                //exit program from simulation mode

				default: return SIM_TOOL;
			    }
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;	
			else
				return OUTPUT_AREA;
		}
		
		//[3] User clicks on the status bar
		if (y >= UI.height - UI.StatusBarHeight && y < UI.height)
			return STATUS;
	
	

}


Input::~Input()
{
}
