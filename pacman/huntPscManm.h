#pragma once
#include "State.h"
class huntPscManm :
	public State
{
public:
	huntPscManm();
	~huntPscManm();
	void MakeTransition(pacMan* owner);
	void OnStateEnter(pacMan* owner);
	void OnStateExit(pacMan* owner);

};

