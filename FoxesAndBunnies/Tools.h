#pragma once

#include <cstdlib> 
#include <random>
#include <iostream>
#include <windows.h> 
// k 2 born 
// k 3 boy 
// k 4 death 
// k 5 girlll

enum class ExampleColor : uint8_t
{
	Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
	Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	Magenta = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	White = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

};

using u32 = uint_least32_t;
using engine = std::mt19937;

class Tools
{
public:
	static int RandomInRange(int InMaxNumber);

	static void LogUI(std::string InString, ExampleColor InColor);
	static void LogUI(std::string InString, std::vector<int> InRGB) {};

};

