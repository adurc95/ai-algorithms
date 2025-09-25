#include "huntPscManm.h"
#include "onTheRun.h"


huntPscManm::huntPscManm()
{
}


huntPscManm::~huntPscManm()
{
}

void eatingCoins::MakeTransition(pacMan* owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	owner->setCurrentState(new onTheRun());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info

}

void eatingCoins::OnStateEnter(pacMan* owner)
{
	owner->setIsMoving(true);
	Cell* target = owner->getCurrntTarget();
	owner->setDirection(target->getRow(), target->getCol());
}

void eatingCoins::OnStateExit(pacMan* owner)
{
	owner->setIsMoving(false);

}
