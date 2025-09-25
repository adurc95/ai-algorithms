#pragma once
#include "State.h"
class onTheRun :
	public State
{
public:
	onTheRun();
	~onTheRun();
	void MakeTransition(pacMan* owner);
	void OnStateEnter(pacMan* owner);
	void OnStateExit(pacMan* owner);

};

