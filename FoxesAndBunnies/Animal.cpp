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
	return bIsMale;
}

bool Animal::OverAgeLimit()
{
	if (Age > AgeLimit) {
		Die();
		return true;
	}
	std::cout << Age;

	return false;
}

void Animal::Die()
{
	
}
