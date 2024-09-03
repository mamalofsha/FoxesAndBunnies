#include "World.h"
#include "Tools.h"
World::World(int InRabbitCount, int InGrassCount, int InFoxCount)
{
	EcosystemOnline = true;
	Rabbits.reserve(1999);
	Foxes.reserve(1999);
	Increase(WorldObjectType::TypeOfRabbit, InRabbitCount);
	Increase(WorldObjectType::TypeOfGrass, InGrassCount);
	Increase(WorldObjectType::TypeOfFox, InFoxCount);
}

void World::SpawnRabbit(std::vector<Rabbit>& InRabbits, int InCount)
{
	for (int i = 0; i < InCount; i++)
	{
		Rabbit NewTempRabbit;
		InRabbits.push_back(NewTempRabbit);
	}
}

void World::SpawnFox(std::vector<Fox>& InFoxes, int InCount)
{
	for (int i = 0; i < InCount; i++)
	{
		Fox NewTempFox;
		InFoxes.push_back(NewTempFox);
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
		if (!Rabbits[i].GetRadioactive())
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
	case TypeOfRabbit:
		SpawnRabbit(Rabbits, InCount);
		break;
	case TypeOfGrass:
		if (MaxGrassCount == 0)
		{
			MaxGrassCount = InCount;
			GrassCount = InCount;
		}
		else
			GrassCount += InCount % (MaxGrassCount - GrassCount + 1);
		break;
	case TypeOfFox:
		SpawnFox(Foxes, InCount);
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

std::vector<Fox>& World::GetFoxes()
{
	return Foxes;
}

void World::MoveCycleForward()
{
	std::vector<int> MaleFoxes;
	std::vector<int> FemaleFoxes;
	// fox mating 
	for (int i = 0; i < Foxes.size(); i++)
	{
		if (Foxes[i].GetIsMale() && Foxes[i].EligibleForBreeding())
			MaleFoxes.push_back(i);
		if (!Foxes[i].GetIsMale() && Foxes[i].EligibleForBreeding())
			FemaleFoxes.push_back(i);
	}
	if (MaleFoxes.size() > 0 && FemaleFoxes.size() > 0)
	{
		int FoxSpawnCount;
		if (MaleFoxes.size() > FemaleFoxes.size())
			FoxSpawnCount = FemaleFoxes.size();
		else
			FoxSpawnCount = MaleFoxes.size();
		Increase(WorldObjectType::TypeOfFox, FoxSpawnCount);
	}
	// foxes feeding
	for (int i = Foxes.size() - 1; i >= 0; i--)
	{
		if (Foxes[i].GetAge() < 2)
			continue;
		bool DoubleFeed = false;
		if (static_cast<float>(GrassCount) / static_cast<float>(MaxGrassCount) < 0.2)
			if (Tools::RandomInRange(10) > 5)
				DoubleFeed = true;
		for (int j = 0; j < (DoubleFeed ? 2 : 1); j++)
		{
			if (Rabbits.size() > 0)
			{
				int TargetRabbit = Tools::RandomInRange(Rabbits.size() - 1);
				if (j == 0)
					Tools::LogUI("A fox just ate: " + Rabbits[TargetRabbit].GetFullInfo(), ExampleColor::Red);
				else
					Tools::LogUI("A lucky fox just ate: " + Rabbits[TargetRabbit].GetFullInfo(), ExampleColor::Red);
				bool RadioActiveBite = Rabbits[TargetRabbit].GetRadioactive();
				if (RadioActiveBite)
				{
					if (Tools::RandomInRange(10) > 7)
					{
						Tools::LogUI("The rabbit was radioactive and it killed a fox ", ExampleColor::Red);
						Foxes.erase(Foxes.begin() + i);
						break;
					}
				}
				else
					Foxes[i].BecomeHaunted(Rabbits[TargetRabbit]);
				Rabbits.erase(Rabbits.begin() + TargetRabbit);
			}
			else
			{
				if (j == 0) {
					Tools::LogUI("A fox starved XP ", ExampleColor::Red);
					Foxes.erase(Foxes.begin() + i);
					break;
				}
				else
				{
					Tools::LogUI("Somewhere a fox is still hungry ", ExampleColor::Yellow);
				}
			}
		}
	}
	// age up foxes
	for (int i = Foxes.size() - 1; i >= 0; i--)
		if (Foxes[i].AgeUp())
			Foxes.erase(Foxes.begin() + i);
	// age up rabbits , remove them if dead
	for (int i = Rabbits.size() - 1; i >= 0; i--)
		if (Rabbits[i].AgeUp())
			Rabbits.erase(Rabbits.begin() + i);
	// rabbit infection
	std::vector<int> Infectors;
	for (int i = 0; i < Rabbits.size(); i++) 
		if (Rabbits[i].GetRadioactive())
			Infectors.push_back(i);
	for (int i = 0; i < Infectors.size(); i++)
		if (GetFirstNonRadioActive())
			GetFirstNonRadioActive()->TurnRadioActive(false);
	Infectors.clear();
	/// rabbit feed
	for (int i = Rabbits.size() - 1; i >= 0; i--) {
		int GrassCost = Rabbits[i].GetRadioactive() ? 4 : 2;
		if (GrassCount > GrassCost)
			GrassCount -= GrassCost;
		else {
			Rabbits[i].Starve();
			Rabbits.erase(Rabbits.begin() + i);
		}
	}
	// rabbit mate
	for (int i = 0; i < Rabbits.size(); i++)
	{
		if (!Rabbits[i].GetIsMale())
			if (Rabbits[i].EligibleForBreeding()) {
				if (GetFirstMaleInList()) {
					Rabbit TempRabbit(Rabbits[i].GetColor(), Rabbits[i]);
					Rabbits.push_back(TempRabbit);
				}
			}
	}
	Tools::LogUI("cycle passed ", ExampleColor::White);
	Tools::LogUI("Total Fox Population: " + std::to_string(Foxes.size()), ExampleColor::White);
	Tools::LogUI("Total Rabbit Population: " + std::to_string(Rabbits.size()), ExampleColor::White);
	Tools::LogUI("Total Grass Remaining : " + std::to_string(GrassCount), ExampleColor::White);
	Tools::LogUI("With Average age of: " + std::to_string(Average(RatioType::Age)), ExampleColor::White);
	Tools::LogUI(std::to_string(Average(RatioType::Radioactivity)) + "% Radioactive", ExampleColor::White);
	Increase(WorldObjectType::TypeOfGrass, 1);
	if (Rabbits.size() == 0)
		EcosystemOnline = false;
	if (Rabbits.size() > 1000)
	{
		Tools::LogUI("Rabbit overflow , \"snap\" ", ExampleColor::White);
		bool OddDelete = Rabbits.size() % 2 > 0;
		for (int i = Rabbits.size() - 1; i >= 0; i--)
		{
			if (OddDelete && (i % 2 == 1))
				Rabbits.erase(Rabbits.begin() + i);
			if (!OddDelete && (i % 2 == 0))
				Rabbits.erase(Rabbits.begin() + i);
		}
	}
	for (int i = Rabbits.size() - 1; i >= 0; i--) {
		std::string ColorInfo;
		for (int j = 0; j < 3; j++)
			ColorInfo.append(j > 0 ? "," + std::to_string(Rabbits[i].GetColor()[j]) : std::to_string(Rabbits[i].GetColor()[j]));
		if (Rabbits[i].GetMomPTR())
			Tools::LogUI(Rabbits[i].GetFirstName() + " " + Rabbits[i].GetLastName() + " " + std::to_string(Rabbits[i].GetAge()) + " With Color of :" + ColorInfo + (Rabbits[i].GetRadioactive() ? " RadioActive " : " Non RadioActive ") + " Child of: " + static_cast<Rabbit*>(Rabbits[i].GetMomPTR())->GetFirstName() + "  " + static_cast<Rabbit*>(Rabbits[i].GetMomPTR())->GetLastName() + " with Age of: " + std::to_string(static_cast<Rabbit*>(Rabbits[i].GetMomPTR())->GetAge()), ExampleColor::White);
		else
			Tools::LogUI(Rabbits[i].GetFirstName() + " " + Rabbits[i].GetLastName() + " " + std::to_string(Rabbits[i].GetAge()) + " With Color of :" + ColorInfo + (Rabbits[i].GetRadioactive() ? " RadioActive " : " Non RadioActive "), ExampleColor::White);
	}
}