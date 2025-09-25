#pragma once
#include "State.h"
class eatingCoins :
	public State
{
public:
	eatingCoins();
	~eatingCoins();
	void MakeTransition(pacMan* owner);
	void OnStateEnter(pacMan* owner);
	void OnStateExit(pacMan* owner);

};

