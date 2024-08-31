#include "World.h"

World::World(int InRabbitCount, int InGrassCount, int InFoxCount)
{
	EcosystemOnline = true;
	Rabbits.reserve(1999);
	Increase(WorldObjectType::Rabbyte, InRabbitCount);
	MaxGrassCount = InGrassCount;
	GrassCount = MaxGrassCount;
}

void World::SpawnRabbit(std::vector<Rabbit>& InRabbits, int InCount)
{
	for (int i = 0; i < InCount; i++)
	{
		Rabbit NewTempRabbit;
		InRabbits.insert(InRabbits.end(), NewTempRabbit);
	}
}

Rabbit* World::GetFirstMaleInList()
{
	for (int i = 0; i < Rabbits.size(); i++)
	{
		if (Rabbits[i].GetIsMale())
			return &Rabbits[i];
	}
	return nullptr;
}

Rabbit* World::GetFirstNonRadioActive()
{
	for (int i = 0; i < Rabbits.size(); i++)
	{
		if (Rabbits[i].GetRadioactive())
			return &Rabbits[i];
	}
	return nullptr;
}

int World::Average(RatioType InRatioType)
{
	int total = 0;
	for (int i = 0; i < Rabbits.size(); i++)
	{
		switch (InRatioType)
		{
		case Radioactivity:
			total += (Rabbits[i].GetRadioactive() ? 1 : 0) * 100;
			break;
		case Age:
			total += Rabbits[i].GetAge();
			break;
		default:
			break;
		}
	}
	return total / (Rabbits.size() > 0 ? Rabbits.size(): 1);
}

void World::Increase(WorldObjectType InWorldType, int InCount)
{
	switch (InWorldType)
	{
	case Rabbyte:
		SpawnRabbit(Rabbits, InCount);
		break;
	case Grass:
		GrassCount += InCount % (MaxGrassCount - GrassCount + 1);
		break;
	case Foxes:
		break;
	default:
		break;
	}
}

int World::GetGrassCount()
{
	return GrassCount;
}

bool World::GetWorldHeartBeat()
{
	return EcosystemOnline;
}

std::vector<Rabbit>& World::GetRabbits()
{
	return Rabbits;
}

void World::MoveCycleForward()
{
	int erased = 0;
	// age up rabbits , remove them if dead
	for (int i = Rabbits.size() - 1; i >= 0; i--)
		if (Rabbits[i].AgeUp()) {
			Rabbits.erase(Rabbits.begin() + i);
			erased++;
		}
	// rabbit infection
	std::vector<int> Infectors;
	for (int i = 0; i < Rabbits.size(); i++) {
		if (Rabbits[i].GetRadioactive())
		{
			Infectors.push_back(i);
		}
	}
	for (int i = 0; i < Infectors.size(); i++)
	{
		if (GetFirstNonRadioActive())
			GetFirstNonRadioActive()->TurnRadioActive(false);
	}
	Infectors.clear();
	/// rabbit feed
	for (int i = Rabbits.size() - 1; i >= 0; i--) {
		int GrassCost = Rabbits[i].GetRadioactive() ? 4 : 2;
		if (GrassCount > GrassCost)
			GrassCount -= GrassCost;
		else {
			Rabbits[i].Starve();
			Rabbits.erase(Rabbits.begin() + i);
			erased++;
		}
	}
	// rabbit mate
	for (int i = 0; i < Rabbits.size(); i++)
	{
		if (!Rabbits[i].GetIsMale())
			if (Rabbits[i].EligibleForBreeding()) {
				if (GetFirstMaleInList()) {
					Rabbit x(GetFirstMaleInList()->GetLastName(), Rabbits[i].GetColor(), i, Rabbits[i]);
					std::cout << x.GetMomPTR()->GetAge();
					std::cout << std::endl << x.GetMomPTR() << std::endl;
					Rabbits.push_back(x);
					std::cout << x.GetMomPTR()->GetAge();
				}
			}
	}
	HANDLE  hConsole{};
	int k = 15;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	std::cout << "cycle passed " << std::endl << std::endl;
	std::cout << "Total Rabbit Population: " + std::to_string(Rabbits.size()) << std::endl;
	std::cout << "Total Grass Remaining : " + std::to_string(GrassCount) << std::endl;
	Increase(WorldObjectType::Grass, 1);
	std::cout << "With Average age of: " + std::to_string(Average(RatioType::Age)) << std::endl;
	std::cout << std::to_string(Average(RatioType::Radioactivity)) + "% Radioactive" << std::endl << std::endl;
	if (Rabbits.size() > 1000)
	{
		std::cout << "Rabbit overflow , \"snap\" " << std::endl;
		bool oddDelete = Rabbits.size() % 2 > 0;
		for (int i = Rabbits.size() - 1; i >= 0; i--)
		{

			if (oddDelete && (i % 2 == 1))
				Rabbits.erase(Rabbits.begin() + i);
			if (!oddDelete && (i % 2 == 0))
				Rabbits.erase(Rabbits.begin() + i);

		}
	}
	for (int i = Rabbits.size() - 1; i >= 0; i--) {
		if (Rabbits[i].GetMomIndex() > -1)
		{
			Rabbits[i].ShiftIndex(erased);
			if (Rabbits[i].GetMomIndex() > -1)
			{
				int index = Rabbits[i].GetMomIndex();
				std::cout << Rabbits[i].GetMomPTR()->GetAge() << "-.-";

				std::cout << Rabbits[i].GetFirstName() << " " << Rabbits[i].GetLastName() << " " << Rabbits[i].GetAge() << " Child of: " << Rabbits[index].GetFirstName() << "  " << Rabbits[index].GetLastName() << "-----------" << Rabbits[index].GetAge() << std::endl;
			}
			else
			{
				std::cout << Rabbits[i].GetFirstName() << " " << Rabbits[i].GetLastName() << " " << Rabbits[i].GetAge() << std::endl;
			}

		}
		else
			std::cout << Rabbits[i].GetFirstName() << " " << Rabbits[i].GetLastName() << " " << Rabbits[i].GetAge() << std::endl;

		std::cout << std::endl;
	}
}


/*
int erased = 0;
// age up rabbits , remove them if dead
for (int i = Rabbits.size() - 1; i >= 0; i--)
	if (Rabbits[i].AgeUp()) {
		Rabbits.erase(Rabbits.begin() + i);
		erased++;
	}





std::vector<int> Infectors;
for (int i = 0; i < Rabbits.size(); i++) {

	if (Rabbits[i].GetRadioactive())
	{
		Infectors.push_back(i);

	}
}
for (int i = 0; i < Infectors.size(); i++)
{
	if (GetFirstNonRadioActive(Rabbits) > -1)
		Rabbits[GetFirstNonRadioActive(Rabbits)].TurnRadioActive(false);
}
Infectors.clear();




/// feed
for (int i = Rabbits.size() - 1; i >= 0; i--) {

	int GrassCost = Rabbits[i].GetRadioactive() ? 4 : 2;

	if (GrassCount > GrassCost)
		GrassCount -= GrassCost;
	else {
		Rabbits[i].Starve();
		Rabbits.erase(Rabbits.begin() + i);
		erased++;
	}

}



// mate
for (int i = 0; i < Rabbits.size(); i++)
{
	if (!Rabbits[i].GetIsMale())
		if (Rabbits[i].EligibleForBreeding()) {
			if (GetFirstMaleInList(Rabbits)) {
				Rabbit x(GetFirstMaleInList(Rabbits)->GetLastName(), Rabbits[i].GetColor(), i, Rabbits[i]);
				std::cout << x.GetMomPTR()->GetAge();
				std::cout << std::endl << x.GetMomPTR() << std::endl;

				Rabbits.push_back(x);
				std::cout << x.GetMomPTR()->GetAge();

			}
		}

}





if (Rabbits.size() == 0) {
	EcosystemAlive = false;
}
else
{
	HANDLE  hConsole{};
	int k = 15;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);

	std::cout << "cycle passed " << std::endl << std::endl;

	std::cout << "Total Rabbit Population: " + std::to_string(Rabbits.size()) << std::endl;

	std::cout << "Total Grass Remaining : " + std::to_string(GrassCount) << std::endl;
	GrassCount++;

	std::cout << "With Average age of: " + std::to_string(Average(RatioType::Age, Rabbits)) << std::endl;

	std::cout << std::to_string(Average(RatioType::Radioactivity, Rabbits)) + "% Radioactive" << std::endl << std::endl;

	if (Rabbits.size() > 1000)
	{
		std::cout << "Rabbit overflow , \"snap\" " << std::endl;
		bool oddDelete = Rabbits.size() % 2 > 0;
		for (int i = Rabbits.size() - 1; i >= 0; i--)
		{

			if (oddDelete && (i % 2 == 1))
				Rabbits.erase(Rabbits.begin() + i);
			if (!oddDelete && (i % 2 == 0))
				Rabbits.erase(Rabbits.begin() + i);

		}
	}

	for (int i = Rabbits.size() - 1; i >= 0; i--) {
		if (Rabbits[i].GetMomIndex() > -1)
		{
			Rabbits[i].ShiftIndex(erased);
			if (Rabbits[i].GetMomIndex() > -1)
			{
				int index = Rabbits[i].GetMomIndex();
				std::cout << Rabbits[i].GetMomPTR()->GetAge() << "-.-";

				std::cout << Rabbits[i].GetFirstName() << " " << Rabbits[i].GetLastName() << " " << Rabbits[i].GetAge() << " Child of: " << Rabbits[index].GetFirstName() << "  " << Rabbits[index].GetLastName() << "-----------" << Rabbits[index].GetAge() << std::endl;
			}
			else
			{
				std::cout << Rabbits[i].GetFirstName() << " " << Rabbits[i].GetLastName() << " " << Rabbits[i].GetAge() << std::endl;
			}

		}
		else
			std::cout << Rabbits[i].GetFirstName() << " " << Rabbits[i].GetLastName() << " " << Rabbits[i].GetAge() << std::endl;
	}
	std::cout << std::endl;

}*/