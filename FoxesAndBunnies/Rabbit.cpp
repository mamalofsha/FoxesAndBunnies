#include "Rabbit.h"
#include "Tools.h"

Rabbit::Rabbit()
{
	int RandomNumber = Tools::RandomInRange(9999);
	// gender randomizer 
	IsMale = RandomNumber % 10 > 4;
	Name = NameStorage::RandomFullName(IsMale);
	AgeLimit = 10;
	// 2% chance for radio activity
	if (RandomNumber % 100 > 97)
		TurnRadioActive();
	// colo randomizer + info for printing 
	std::string colorInfo;
	for (int i = 0; i < 3; i++)
	{
		int randomNumber = RandomNumber % 256;
		Color.push_back(randomNumber);
		colorInfo.append(i > 0 ? "," + std::to_string(randomNumber) : std::to_string(randomNumber));
	}
	// gender based name color 
	HANDLE  hConsole{};
	int k = IsMale ? 3 : 5;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	std::cout << Name;
	// green color for birth + yellow for radioactive
	k = IsRadioactive ? 6 : 2;
	SetConsoleTextAttribute(hConsole, k);
	std::cout << " Was Born with Color of " + colorInfo << std::endl;
}

Rabbit::Rabbit( std::vector<int> InColor , Rabbit& Animalptr)
{
	std::cout << "";
	Mom = &Animalptr;
	int RandomNumber = Tools::RandomInRange(9999);
	// gender randomizer 
	IsMale = RandomNumber % 10 > 4;
	AgeLimit = 10;
	// 2% chance for radio activity
	if (RandomNumber % 100 > 97)
		TurnRadioActive();
	// get new name and have father's last name
	Name = NameStorage::RandomFirstName(IsMale) + " " + NameStorage::RandomLastName();
	// mom's color  +  info for printing 
	Color = InColor;
	std::string colorInfo;
	for (int i = 0; i < 3; i++)
	{
		colorInfo.append(i > 0 ? "," + std::to_string(Color[i]) : std::to_string(Color[i]));
	}
	HANDLE  hConsole{};
	int k = IsMale ? 3 : 5;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	std::cout << Name;
	// green color for birth + yellow for radioactive
	k = IsRadioactive ? 6 : 2;
	SetConsoleTextAttribute(hConsole, k);
	std::cout << " Was Born with Color of " + colorInfo << std::endl;
}

bool Rabbit::EligibleForBreeding()
{
	return GetAge() > 1 && !IsRadioactive;
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

enum class ExampleColor : uint8_t
{
	Red = FOREGROUND_RED
};

void Rabbit::TurnRadioActive(bool ByBirth)
{
	// Nikola: Avoid mixing code with different goals
	// e.g. UI and gameplay should be separate
	// Option 1: Move the UI / logging code to a separate function
	// Option 2: Use events/delegates, which is much more difficult to do right now, so let's leave for the future
	if (!ByBirth) {
		HANDLE  hConsole{};
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout << std::endl;
		// Nikola: Don't use magic numbers
		int k = IsMale ? (FOREGROUND_BLUE | FOREGROUND_GREEN) : 5;
		SetConsoleTextAttribute(hConsole, k);
		std::cout << Name;
		k = static_cast<int>(ExampleColor::Red);
		SetConsoleTextAttribute(hConsole, k);
		std::cout << " .::. ";
		k = 6;
		SetConsoleTextAttribute(hConsole, k);
		std::cout << " Was bitten and turned radioactive" << std::endl;
	}
	IsRadioactive = true;
	AgeLimit = 50;
}

bool Rabbit::GetRadioactive()
{
	return IsRadioactive;
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

void Rabbit::Starve()
{
	HANDLE  hConsole{};
	int k = 4;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	std::cout << Name + " Starved  xP  " << std::endl;
}

Animal* Rabbit::GetMomPTR()
{
	return Mom;
}