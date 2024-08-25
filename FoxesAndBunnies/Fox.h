#pragma once
#include "Animal.h"





class Fox :public Animal
{


private :

	bool bIsHaunted = false;
	int HauntCounter = 0;

public:

	// normal constructor 
	Fox();

	virtual bool AgeUp() override;

	void GetHaunted();
	

	virtual bool EligibleForBreeding() override;


};

