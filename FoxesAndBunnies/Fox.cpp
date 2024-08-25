#include "Fox.h"

Fox::Fox()
{

	AgeLimit = 20;

}

bool Fox::AgeUp()
{
	if (bIsHaunted)
	{
		HauntCounter--;
		if (HauntCounter == 0)
			bIsHaunted = false;
	}
	return Animal::AgeUp();
}

void Fox::GetHaunted()
{
	bIsHaunted = true;
	HauntCounter = 5;
}

bool Fox::EligibleForBreeding()
{
	return GetAge() > 1 && !bIsHaunted;
}
