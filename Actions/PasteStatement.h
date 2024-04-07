#pragma once
#include"Action.h"

class PasteStatement : public Action {
	Point P;
	Point Position;   //centre of new statment
	int StatCount;
public:
	PasteStatement(ApplicationManager* pAppManager, int);
	void ReadActionParameters();
	void Execute();
};