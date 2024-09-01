#include "Animal.h"

bool Animal::EligibleForBreeding()
{
	return false;
}

bool Animal::AgeUp()
{
	++Age;
	return OverAgeLimit();
}

int Animal::GetAge()
{
	return Age;
}

bool Animal::GetIsMale()
{
	return IsMale;
}

bool Animal::OverAgeLimit()
{
	if (Age > AgeLimit) {
		Die();
		return true;
	}
	return false;
}
