#pragma once
#include "State.h"

const int SX = 30;
const int SY = 30;

class bustGhost :
	public State
{
public:
	bustGhost();
	~bustGhost();
	void MakeTransition(pacMan* owner);
	void OnStateEnter(pacMan* owner);
	void OnStateExit(pacMan* owner);

};

