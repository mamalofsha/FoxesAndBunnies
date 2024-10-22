#include "Rabbit.h"
#include "Tools.h"

Rabbit::Rabbit()
{
	int RandomNumber = Tools::RandomInRange(9999);
	// gender randomizer 
	IsMale = RandomNumber % 10 > 4;
	Name = NameStorage::RandomFullName(IsMale);
	AgeLimit = 10;
	IsRadioactive = false;
	// 2% chance for radio activity
	if (RandomNumber % 100 > 97)
		TurnRadioActive();
	// colo randomizer + info for printing 
	std::string ColorInfo;
	for (int i = 0; i < 3; i++)
	{
		RandomNumber = Tools::RandomInRange(9999);
		int randomNumber = RandomNumber % 256;
		Color.push_back(randomNumber);
		ColorInfo.append(i > 0 ? "," + std::to_string(randomNumber) : std::to_string(randomNumber));
	}
	Tools::LogUI(Name, IsMale ? ExampleColor::Blue : ExampleColor::Magenta);
	Tools::LogUI(" Was Born with Color of " + ColorInfo, IsRadioactive ? ExampleColor::Yellow : ExampleColor::Green);
}

Rabbit::Rabbit( std::vector<int> InColor , std::shared_ptr<Rabbit> InMomPTR)
{
	MomPTR = InMomPTR;
	int RandomNumber = Tools::RandomInRange(9999);
	// gender randomizer 
	IsMale = RandomNumber % 10 > 4;
	AgeLimit = 10;
	IsRadioactive = false;
	// 2% chance for radio activity
	if (RandomNumber % 100 > 97)
		TurnRadioActive();
	// get new name and have father's last name
	Name = NameStorage::RandomFirstName(IsMale) + " " + NameStorage::RandomLastName();
	// mom's color  +  info for printing 
	Color = InColor;
	std::string ColorInfo;
	for (int i = 0; i < 3; i++)
		ColorInfo.append(i > 0 ? "," + std::to_string(Color[i]) : std::to_string(Color[i]));
	Tools::LogUI(Name, IsMale ? ExampleColor::Blue : ExampleColor::Magenta);
	Tools::LogUI(" Was Born with Color of " + ColorInfo, IsRadioactive ? ExampleColor::Yellow : ExampleColor::Green);
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
	Tools::LogUI(Name + " Died :(", ExampleColor::Red);
}

std::string Rabbit::GetFullInfo()
{
	return GetFirstName()+" "+GetLastName();
}

void Rabbit::TurnRadioActive(bool ByBirth)
{
	if (!ByBirth) {
		Tools::LogUI(Name, IsMale ? ExampleColor::Blue : ExampleColor::Magenta);
		Tools::LogUI(" .::. ", ExampleColor::Red);
		Tools::LogUI(" Was bitten and turned radioactive", ExampleColor::Yellow);
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
	Tools::LogUI(Name + " Starved  xP  ", ExampleColor::Red);
}

std::shared_ptr<Rabbit> Rabbit::GetMomPTR()
{
	return MomPTR;
}