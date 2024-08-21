#include "Animal.h"








bool Animal::EligibleForBreeding()
{
	return false;
}

void Animal::AgeUp()
{
	if (++Age> AgeLimit)
		// die

		return;
}
