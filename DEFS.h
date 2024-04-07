#ifndef DEFS_H
#define DEFS_H

//This file contains some global constants and definitions to be used in the project.

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

// TODO: Add any action type here
enum ActionType // The actions supported
{
	ADD_START, //Add start statement
	ADD_END,   //Add end statement
	ADD_VALUE_ASSIGN, //Add value assignment statement
	ADD_VAR_ASSIGN,	  //Add variable assignment statement
	ADD_OPER_ASSIGN,  //Add operator assignment statement
	ADD_CONDITION,    //Add a conditional statement (for if and while-loop statements)
	ADD_READ,  //Add read statement
	ADD_WRITE, //Addd write statemetn

	ADD_CONNECTOR, //Add a connector between two statements
	
	SELECT,		//Select a statement, a connector

	DEL,   //Delete a figure
	COPY,  //Copy a figure
	PASTE, //Paste a figure

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file

	SWITCH_DSN_MODE,	//Switch to Design mode
	SWITCH_SIM_MODE,	//Switch to simulatiom mode

	EXIT,		//Exit the application


	//TODO: ADD THE ACTIONS OF SIMULATION MODE
	DEBUG,         //dubugging flow chart
	Convert_CPP,   //convert to cpp file
	VALIDATE,      //validate flowchart
	RUN,           //run flowchart
	

	DRAWING_AREA,  //A click on the drawing area
	OUTPUT_AREA,   //A click on the output area
	DSN_TOOL,	   //A click on an empty place in the design tool bar
	SIM_TOOL,      //A click on an empty place in the simulation tool bar
	STATUS 		   //A click on the status bar
};

// TODO: you should add more items
enum DesignMenuItem //The items of the design menu --> THE ORDER MATTERS
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too
	ITM_START,       //start 
	ITM_END,         //end statement
	ITM_VALUE_ASSIGN,//assignment to value statement
	ITM_VARIABLE_ASSIGN,//assignment to variable statement
	ITM_OPER_ASSIGN,//operator assignment statement
	ITM_COND,		 //conditional statement
	ITM_READ,          //read statement
	ITM_WRITE,          //read statement
	ITM_CONNECTOR,   //add a connector
	ITM_SELECT,      //select and unselect item
	ITM_DELETE,      //delete an item
	ITM_COPY,
	ITM_PASTE,       //copy and paste
	ITM_SAVE,        //saves the current flowchart
	ITM_LOAD,        //load the last saved flowchart
	ITM_SIM_SWITCH,      //switch to simulation mode
	ITM_D_EXIT,	  	 //Exit from design mode
	 
	//TODO: Add more items names here
	
	DSN_ITM_CNT		//no. of design menu items ==> This should be the last line in this enum
	
};

// TODO: you should add more items if needed
enum SimMenuItem //The items of the simulation menu
{
	//Note: Items are ordered here as they appear in menu
	ITM_VALIDATE,	//Validate
	ITM_DEBUG,      //Debug
	ITM_RUN,	    //Run
	ITM_CPP,        //convert to cpp file
	ITM_DES_SWITCH, //switch to design mode
	ITM_S_EXIT,     //Exit from simulation mode
		
	//TODO:Add more items names here
	
	SIM_ITM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
};




#ifndef NULL
#define NULL 0
#endif

#endif