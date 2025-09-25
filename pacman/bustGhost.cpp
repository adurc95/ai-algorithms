#include "bustGhost.h"
//#include "DropWoodState.h"



bustGhost::bustGhost()
{
}


bustGhost::~bustGhost()
{
}

void bustGhost::MakeTransition(pacMan* owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	//owner->setCurrentState(new DropWoodState());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info

}

void bustGhost::OnStateEnter(pacMan* owner)
{
	owner->setIsMoving(true);
	owner->setDirection(SX, SY);
}

void bustGhost::OnStateExit(pacMan* owner)
{
	owner->setIsMoving(false);

}
