#pragma once

#include <cstdlib> 
#include <random>

using u32 = uint_least32_t;
using engine = std::mt19937;

class Tools
{
public:
	static int RandomInRange(int InMaxNumber);
};

