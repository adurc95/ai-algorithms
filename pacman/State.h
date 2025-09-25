#pragma once
#include "pacMan.h"


// pure virtual class (interface)

class pacMan;
class State
{
public:
	State();
	~State();

	virtual void MakeTransition(pacMan* owner) = 0;
	virtual void OnStateEnter(pacMan* owner) = 0;
	virtual void OnStateExit(pacMan* owner) = 0;

};

