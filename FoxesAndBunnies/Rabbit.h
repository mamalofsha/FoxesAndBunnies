#pragma once

#include "Animal.h"
#include <cstdlib> 
#include "NameStorage.h"



class Rabbit :public Animal
{
private: 
	std::string Name;
	bool IsRadioactive;
	std::vector<int> Color;
protected:
	virtual void Die() override;
	Animal* Mom;
public:
	// normal constructor 
	Rabbit();
	// constructor for being born with parents 
	Rabbit(std::vector<int> MomColor , Rabbit& Animalptr);
	virtual bool EligibleForBreeding() override;
	std::vector<int> GetColor();
	std::string GetFirstName();
	std::string GetLastName();
	Animal* GetMomPTR();
	bool GetRadioactive();
	virtual void Starve() override;
	void TurnRadioActive(bool ByBirth = true);
	std::string GetFullInfo();
};