#include "Rabbit.h"


Rabbit::Rabbit()
{


	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, 9999);


	std::string colorInfo;
	for (int i = 0; i < 3; i++)
	{
		int randomNumber = distribute(generator) % 256;
		Color.push_back(randomNumber);
		colorInfo.append(i > 0 ? "," + std::to_string(randomNumber) : std::to_string(randomNumber) );
	}


	Name = NameStorage::RandomName();

	HANDLE  hConsole{};
	int k =2 ;
	SetConsoleTextAttribute(hConsole, k);

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);

	std::cout << Name + " Was Born with Color of " + colorInfo;
	std::cout << "\n";

}


Rabbit::Rabbit(std::vector<int> InColor)
{
	Name = NameStorage::RandomName();

	Color = InColor;
	std::string colorInfo;
	for (int i = 0; i < 3; i++)
	{
		colorInfo.append(i > 0 ? "," + std::to_string(Color[i]) : std::to_string(Color[i]));
	}

	std::cout << Name + " Was Born with Color of " + colorInfo;
	std::cout << "\n";

}
bool Rabbit::EligibleForBreeding()
{
	return false;
}

std::vector<int> Rabbit::GetColor()
{
	return Color;
}
