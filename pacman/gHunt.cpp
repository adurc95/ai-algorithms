#include "gHunt.h"
gHunt::gHunt()
{
}


gHunt::~gHunt()
{
}

void gHunt::MakeTransition(scaryGhost* owner)
{
	/*owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	owner->setCurrentState(new onTheRun());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info*/

}

void gHunt::OnStateEnter(scaryGhost* owner)
{
	owner->setIsMoving(true);
	Cell* target = owner->getCurrntTarget();
	owner->setDirection(target->getRow(), target->getCol());
}

void gHunt::OnStateExit(scaryGhost* owner)
{
	owner->setIsMoving(false);

}
