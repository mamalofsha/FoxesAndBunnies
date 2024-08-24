#include "Rabbit.h"


Rabbit::Rabbit()
{


	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, 9999);

	// gender randomizer 
	bIsMale = true;//distribute(generator) % 10 > 4;
	Name = NameStorage::RandomFullName(bIsMale);
	AgeLimit = 10;

	// 2% chance for radio activity
	if (distribute(generator) % 100 > 97)
		TurnRadioActive();

	// colo randomizer + info for printing 
	std::string colorInfo;
	for (int i = 0; i < 3; i++)
	{
		int randomNumber = distribute(generator) % 256;
		Color.push_back(randomNumber);
		colorInfo.append(i > 0 ? "," + std::to_string(randomNumber) : std::to_string(randomNumber));
	}

	// gender based name color 
	HANDLE  hConsole{};
	int k = bIsMale ? 3 : 5;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	std::cout << Name;
	// green color for birth + yellow for radioactive
	k = bIsRadioactive ? 6 : 2;
	SetConsoleTextAttribute(hConsole, k);
	std::cout << " Was Born with Color of " + colorInfo << std::endl;

}


Rabbit::Rabbit(std::string FatherName, std::vector<int> InColor)
{

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, 9999);

	// gender randomizer 
	bIsMale = distribute(generator) % 10 > 4;
	AgeLimit = 10;

	// 2% chance for radio activity

	if (distribute(generator) % 100 > 97)
		TurnRadioActive();
	// get new name and have father's last name
	Name = NameStorage::RandomFirstName(bIsMale) + " " + FatherName;

	// mom's color  +  info for printing 
	Color = InColor;
	std::string colorInfo;
	for (int i = 0; i < 3; i++)
	{
		colorInfo.append(i > 0 ? "," + std::to_string(Color[i]) : std::to_string(Color[i]));
	}
	HANDLE  hConsole{};
	int k = bIsMale ? 3 : 5;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	std::cout << Name;
	// green color for birth + yellow for radioactive
	k = bIsRadioactive ? 6 : 2;
	SetConsoleTextAttribute(hConsole, k);

	std::cout << " Was Born with Color of " + colorInfo << std::endl;

}
bool Rabbit::EligibleForBreeding()
{
	return GetAge() > 1 && !bIsRadioactive;
}

std::vector<int> Rabbit::GetColor()
{
	return Color;
}

void Rabbit::Die()
{
	HANDLE  hConsole{};
	int k = 4;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	std::cout << Name + " Died :( " << std::endl;


}

void Rabbit::TurnRadioActive(bool ByBirth)
{


	if (!ByBirth) {
		HANDLE  hConsole{};
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout << std::endl;
		int k = bIsMale ? 3 : 5;
		SetConsoleTextAttribute(hConsole, k);
		std::cout << Name;

		 k =  4;
		SetConsoleTextAttribute(hConsole, k);
		std::cout << " .::. ";

		k = 6;
		SetConsoleTextAttribute(hConsole, k);

		std::cout << " Was bitten and turned radioactive" << std::endl;

	}
	bIsRadioactive = true;
	AgeLimit = 50;
}

bool Rabbit::GetRadioactive()
{
	return bIsRadioactive;
}


std::string Rabbit::GetFirstName()
{
	std::string delimiter = " ";
	return Name.substr(0,Name.find(delimiter));
}


std::string Rabbit::GetLastName()
{
	std::string delimiter = " ";
	return Name.substr(Name.find(delimiter) + 1, Name.size() - Name.find(delimiter));
}



