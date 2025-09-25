#pragma once

#include "scaryGhost.h"

class scaryGhost;
class gStates
{
public:
	gStates();
	~gStates();

	virtual void MakeTransition(scaryGhost* owner) = 0;
	virtual void OnStateEnter(scaryGhost* owner) = 0;
	virtual void OnStateExit(scaryGhost* owner) = 0;

};



