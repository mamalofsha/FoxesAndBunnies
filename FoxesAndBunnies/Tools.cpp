#include "Tools.h"

int Tools::RandomInRange(int InMaxNumber)
{
	std::random_device os_seed;
	const u32 seed = os_seed();
	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, InMaxNumber);
	return distribute(generator);
}

void Tools::LogUI(std::string InString, ExampleColor InColor)
{
	HANDLE  hConsole{};
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, static_cast<int>(InColor));
	std::cout << InString;
	std::cout << std::endl;
}