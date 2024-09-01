#include "World.h"
#include "Tools.h"
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
	return total / (Rabbits.size() > 0 ? Rabbits.size() : 1);
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
					Rabbit TempRabbit( Rabbits[i].GetColor(),Rabbits[i]);
					Rabbits.push_back(TempRabbit);
				}
			}
	}
	Tools::LogUI("cycle passed ", ExampleColor::White);
	Tools::LogUI("Total Rabbit Population: " + std::to_string(Rabbits.size()), ExampleColor::White);
	Tools::LogUI("Total Grass Remaining : " + std::to_string(GrassCount), ExampleColor::White);
	Tools::LogUI("With Average age of: " + std::to_string(Average(RatioType::Age)), ExampleColor::White);
	Tools::LogUI(std::to_string(Average(RatioType::Radioactivity)) + "% Radioactive", ExampleColor::White);
	Increase(WorldObjectType::Grass, 1);

	if (Rabbits.size() > 1000)
	{
		Tools::LogUI("Rabbit overflow , \"snap\" ", ExampleColor::White);
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
		if (Rabbits[i].GetMomPTR())
			Tools::LogUI(Rabbits[i].GetFirstName() + " " + Rabbits[i].GetLastName() + " " + std::to_string(Rabbits[i].GetAge()) + " Child of: " + static_cast<Rabbit*>(Rabbits[i].GetMomPTR())->GetFirstName() + "  " + static_cast<Rabbit*>(Rabbits[i].GetMomPTR())->GetLastName() + "-----------" + std::to_string(static_cast<Rabbit*>(Rabbits[i].GetMomPTR())->GetAge()), ExampleColor::White);
		else
			Tools::LogUI(Rabbits[i].GetFirstName() + " " + Rabbits[i].GetLastName() + " " + std::to_string(Rabbits[i].GetAge()), ExampleColor::White);
	}
}