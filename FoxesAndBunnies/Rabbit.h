#pragma once
#include "Animal.h"
#include <cstdlib> 
#include "NameStorage.h"




using u32 = uint_least32_t;
using engine = std::mt19937;




class Rabbit :public Animal
{

private : 



	std::string Name;
	bool bIsRadioactive;
	std::vector<int> Color;

public:
	Rabbit();
	Rabbit(std::vector<int> InColor);
	bool EligibleForBreeding();

	std::vector<int> GetColor();

};

