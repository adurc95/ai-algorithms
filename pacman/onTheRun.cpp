#include "onTheRun.h"
#include "bustGhost.h"



onTheRun::onTheRun()
{
}


onTheRun::~onTheRun()
{
}

void onTheRun::MakeTransition(pacMan* owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	owner->setCurrentState(new bustGhost());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info 
}

void onTheRun::OnStateEnter(pacMan* owner)
{
	owner->setIsGettingWood(true);
	owner->setIsMoving(false);
}

void onTheRun::OnStateExit(pacMan* owner)
{
	owner->setIsGettingWood(false);

}
