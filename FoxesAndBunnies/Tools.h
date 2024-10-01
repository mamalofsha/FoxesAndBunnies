#pragma once

#include <cstdlib> 
#include <random>
#include <iostream>
#include <windows.h> 

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
	using FFoxEatenHandler = void (*)(std::string,bool);
	void FoxEatRabbitCall(std::string InName, bool IsLucky)
	{
		OnFoxEaten(InName, IsLucky);
	}
	FFoxEatenHandler OnFoxEaten;
	using FFoxGotPoisoned = void (*)();
	void FoxGotPoisoned()
	{
		OnFoxPoisoned();
	}
	FFoxGotPoisoned OnFoxPoisoned;
	using FFoxStillHungry = void (*)(bool);
	void FoxStillHungry(bool Starved)
	{
		OnFoxStillHungry(Starved);
	}
	FFoxStillHungry OnFoxStillHungry;

};