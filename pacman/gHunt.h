#pragma once
#include "gStates.h"

class gHunt :
	public gStates
{
public:
	gHunt();
	~gHunt();
	void MakeTransition(scaryGhost* owner);
	void OnStateEnter(scaryGhost* owner);
	void OnStateExit(scaryGhost* owner);
};

