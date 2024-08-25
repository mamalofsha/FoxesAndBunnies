#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <windows.h> 







class Animal
{

private : 

	int Age = 0;


protected:

	int AgeLimit;
	bool bIsMale;

	virtual bool EligibleForBreeding() ;

	virtual void Die();
	bool OverAgeLimit();

public:
	
	bool AgeUp();
	int GetAge();
	bool GetIsMale();
	virtual void Starve() {};


};

