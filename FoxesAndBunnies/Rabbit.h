#pragma once
#include "Animal.h"
#include <cstdlib> 
#include "NameStorage.h"




using u32 = uint_least32_t;
using engine = std::mt19937;

// k 2 born 
// k 3 boy 
// k 4 death 
// k 5 girlll


class Rabbit :public Animal
{

private : 



	std::string Name;
	bool bIsRadioactive;
	std::vector<int> Color;

protected:

	virtual void Die() override;

	Animal* Mom;


public:

	// normal constructor 
	Rabbit();
	// constructor for being born with parents 
	Rabbit(std::string FatherName ,std::vector<int> MomColor, Animal* InMom);
	virtual bool EligibleForBreeding() override;

	std::vector<int> GetColor();
	std::string GetFirstName();

	std::string GetLastName();

	Animal* GetMom();

	bool GetRadioactive();


	virtual void Starve() override;

	void TurnRadioActive(bool ByBirth = true);

};

