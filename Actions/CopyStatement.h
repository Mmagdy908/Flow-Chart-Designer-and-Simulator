#pragma once
#include"Action.h"

class CopyStatement : public Action {
private:


public:
	CopyStatement(ApplicationManager* pAppManager);


	void Execute();
};