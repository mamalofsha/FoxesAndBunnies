#include "World.h"
#include "Tools.h"
#include <algorithm>
#include <numeric>
#include <assert.h>

std::shared_ptr<Rabbit> World::BreedRabbit(const std::shared_ptr<Rabbit>& InMom)
{
	std::shared_ptr<Rabbit> TempRabbit = std::make_shared<Rabbit>();
	return TempRabbit;
}

World::World(int InRabbitCount, int InGrassCount, int InFoxCount)
{
	EcosystemOnline = true;
	//Rabbits.reserve(1999);
	//Foxes.reserve(1999);
	Increase(WorldObjectType::TypeOfRabbit, InRabbitCount);
	Increase(WorldObjectType::TypeOfGrass, InGrassCount);
	Increase(WorldObjectType::TypeOfFox, InFoxCount);
	//
	Tools Tool;
	Tools::FFoxEatenHandler lambdaDamageHandler = [](std::string InName) {					
		Tools::LogUI("A fox just ate: " + InName, ExampleColor::Red);
		};
	Tool.OnFoxEaten = lambdaDamageHandler;
	//
	ToolRef = Tool;
}

void World::SpawnRabbit(int InCount)
{
	for (int i = 0; i < InCount; i++)
	{
		std::shared_ptr<Rabbit> NewTempRabbit = std::make_shared<Rabbit>();
		Rabbits.push_back(NewTempRabbit);
	}// NewTempRabbit out of scope , but pointer stays alive because it's referenced by the Rabbits
}

void World::SpawnFox(int InCount)
{
	for (int i = 0; i < InCount; i++)
	{
		std::shared_ptr<Fox> NewTempFox = std::make_shared<Fox>();
		Foxes.push_back(NewTempFox);
	}
}

std::shared_ptr<Rabbit> World::GetFirstMaleInList()
{
	// Nikola: Algo
	for (int i = 0; i < Rabbits.size(); i++)
	{
		if (Rabbits[i]->GetIsMale())
			return Rabbits[i];
	}
	return nullptr;
}

std::shared_ptr<Rabbit> World::GetFirstNonRadioActive()
{
	// Nikola: Algo
	for (int i = 0; i < Rabbits.size(); i++)
	{
		if (!Rabbits[i]->GetRadioactive())
			return Rabbits[i];
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
			total += (Rabbits[i]->GetRadioactive() ? 1 : 0) * 100;
			break;
		case Age:
			total += Rabbits[i]->GetAge();
			break;
		default:
			break;
		}
	}
	return total / (Rabbits.size() > 0 ? Rabbits.size() : 1);
}

void World::FoxEatRabbit(std::string x)
{
}



// Nikola: Type erasure/templates
void World::Increase(WorldObjectType InWorldType, int InCount)
{
	switch (InWorldType)
	{
	case TypeOfRabbit:
		SpawnRabbit(InCount);
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
		SpawnFox(InCount);
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

std::vector<std::shared_ptr<Rabbit>> World::GetRabbits()
{
	return Rabbits;
}

std::vector<std::shared_ptr<Fox>> World::GetFoxes()
{
	return Foxes;
}

void World::MoveCycleForward()
{
	// Nikola: Algo::partition
	// fox mating 
	/// new way
	auto IsFoxMale = [](const std::shared_ptr<Fox>& InFox)
		{
			return InFox->GetIsMale() && InFox->EligibleForBreeding();
		};
	auto IsFoxFemale = [](const std::shared_ptr<Fox>& InFox)
		{
			return !InFox->GetIsMale() && InFox->EligibleForBreeding();
		};
	int FoxMaleCount = std::count_if(Foxes.begin(), Foxes.end(), IsFoxMale);
	int FoxFemaleCount = std::count_if(Foxes.begin(), Foxes.end(), IsFoxFemale);
	// then spawn with the lower value
	//new way using partition
	int EligibleFoxesCount_Partition = count_if(Foxes.begin(), Foxes.end(), [](const std::shared_ptr<Fox>& InFox)
		{
			return InFox->EligibleForBreeding();
		});
	partition(Foxes.begin(), Foxes.end(), [](const std::shared_ptr<Fox>& InFox)
		{
			// first partition the eligible ones for breeding
			return InFox->EligibleForBreeding();
		});
	// smaller number (male / all - male = female ) is the final spawn count  
	int MaleFoxes_Partition = count_if(Foxes.begin(), Foxes.begin() + EligibleFoxesCount_Partition , [](const std::shared_ptr<Fox>& InFox)
		{
			return InFox->GetIsMale();
		});
	// determining spawn count using partition
	int FoxSpawnCount_UsingPartition = ((EligibleFoxesCount_Partition - MaleFoxes_Partition) < MaleFoxes_Partition) ? EligibleFoxesCount_Partition - MaleFoxes_Partition : MaleFoxes_Partition;
	Increase(WorldObjectType::TypeOfFox, FoxSpawnCount_UsingPartition);
	// getting male and female count old way
	/*
	std::vector<int> MaleFoxes;
	std::vector<int> FemaleFoxes;
	for (int i = 0; i < Foxes.size(); i++)
	{
		if (Foxes[i]->GetIsMale() && Foxes[i]->EligibleForBreeding())
			MaleFoxes.push_back(i);
		if (!Foxes[i]->GetIsMale() && Foxes[i]->EligibleForBreeding())
			FemaleFoxes.push_back(i);
	}
	// determining spawn count old way 
	if (MaleFoxes.size() > 0 && FemaleFoxes.size() > 0)
	{
		int FoxSpawnCount;
		if (MaleFoxes.size() > FemaleFoxes.size())
			FoxSpawnCount = FemaleFoxes.size();
		else
			FoxSpawnCount = MaleFoxes.size();
		Increase(WorldObjectType::TypeOfFox, FoxSpawnCount);
	}
	*/
	// foxes feeding
	for (int i = Foxes.size() - 1; i >= 0; i--)
	{
		if (Foxes[i]->GetAge() <= 2)
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
					ToolRef.FoxEatRabbitCall(Rabbits[TargetRabbit]->GetFullInfo());
				else
					ToolRef.FoxEatRabbitCall(Rabbits[TargetRabbit]->GetFullInfo()); //Tools::LogUI("A lucky fox just ate: " + Rabbits[TargetRabbit]->GetFullInfo(), ExampleColor::Red);
				bool RadioActiveBite = Rabbits[TargetRabbit]->GetRadioactive();
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
					Foxes[i]->BecomeHaunted(Rabbits[TargetRabbit]);
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
	// new way
	auto IsFoxOld = [](const std::shared_ptr<Fox>& InFox)
		{
			return InFox->AgeUp();
		};
	Foxes.erase(std::remove_if(Foxes.begin(), Foxes.end(), IsFoxOld), Foxes.end());
	// old way
	/*
	for (int i = Foxes.size() - 1; i >= 0; i--)
		if (Foxes[i]->AgeUp())
			Foxes.erase(Foxes.begin() + i);
			*/
	// age up rabbits , remove them if dead
	//new way
	auto IsRabbitOld = [](const std::shared_ptr<Rabbit>& InRabbit)
		{
			return InRabbit->AgeUp();
		};
	Rabbits.erase(std::remove_if(Rabbits.begin(), Rabbits.end(), IsRabbitOld), Rabbits.end());
	// old way 
	/*
	for (int i = Rabbits.size() - 1; i >= 0; i--)
		if (Rabbits[i]->AgeUp())
			Rabbits.erase(Rabbits.begin() + i);
	*/
	// rabbit infection
	// new way
	auto IsRadioActive = [](const std::shared_ptr<Rabbit>& InRabbit)
		{
			return InRabbit->GetRadioactive();
		};
	int NumRadioActive = std::count_if(Rabbits.begin(), Rabbits.end(), IsRadioActive);
	for (int i = 0; i < NumRadioActive; i++)
	{
		if (GetFirstNonRadioActive())
			GetFirstNonRadioActive()->TurnRadioActive(false);
		else
			continue;
	}
	/// how to use conditional transform so we turn the non radio active radioactive?
		//old way 
		/*
		std::vector<int> Infectors;
		for (int i = 0; i < Rabbits.size(); i++)
			if (Rabbits[i]->GetRadioactive())
				Infectors.push_back(i);
		for (int i = 0; i < Infectors.size(); i++)
			if (GetFirstNonRadioActive())
				GetFirstNonRadioActive()->TurnRadioActive(false);
		Infectors.clear();
		*/
	/// rabbit feed
	// new way
	auto IsShortOnFood = [this](const std::shared_ptr<Rabbit>& InRabbit)
		{
			int GrassCost = InRabbit->GetRadioactive() ? 4 : 2;
			if (GrassCount > GrassCost) 
			{
				GrassCount -= GrassCost;
				return false;
			}
			else {
				InRabbit->Starve();
				return true;
			}
		};
	Rabbits.erase(std::remove_if(Rabbits.begin(), Rabbits.end(), IsShortOnFood), Rabbits.end());
	//old way
	/*
	for (int i = Rabbits.size() - 1; i >= 0; i--) {
		int GrassCost = Rabbits[i]->GetRadioactive() ? 4 : 2;
		if (GrassCount > GrassCost)
			GrassCount -= GrassCost;
		else {
			Rabbits[i]->Starve();
			Rabbits.erase(Rabbits.begin() + i);
		}
	}
	*/
	// rabbit mate new way
	auto IsRabbitMale = [](const std::shared_ptr<Rabbit>& InRabbit)
		{
			return InRabbit->GetIsMale() && InRabbit->EligibleForBreeding();
		};
	bool IsThereAMaleRabbit = std::any_of(Rabbits.begin(), Rabbits.end(), IsRabbitMale);
	if (IsThereAMaleRabbit)
	{
		for (int i = 0; i < Rabbits.size(); i++)
		{
			if (!Rabbits[i]->GetIsMale())
				if (Rabbits[i]->EligibleForBreeding()) {
						std::shared_ptr<Rabbit> TempRabbit = std::make_shared<Rabbit>(Rabbits[i]->GetColor(), Rabbits[i]);
						Rabbits.push_back(TempRabbit);
				}
		}
		// how to do this
		//std::transform(Rabbits.begin(), Rabbits.begin() + Rabbits.size() - 1, back_inserter(Rabbits), BreedRabbit);
	}
	// rabbit mate old way 
	/*
	for (int i = 0; i < Rabbits.size(); i++)
	{
		if (!Rabbits[i]->GetIsMale())
			if (Rabbits[i]->EligibleForBreeding()) {
				if (GetFirstMaleInList()) {
					std::shared_ptr<Rabbit> TempRabbit = std::make_shared<Rabbit>(Rabbits[i]->GetColor(), Rabbits[i]);
					Rabbits.push_back(TempRabbit);
				}
			}
	}
	*/
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
		// Nikola: Avoid having non-loop dependent variables in the loop
		// Nikola: std::remove_if
		//if (OddDelete)
		//{
		//	for (int i = Rabbits.size() - 1; i >= 0; i--)
		//	{
		//		if (i % 2 == 1)
		//			Rabbits.erase(Rabbits.begin() + i);
		//	}
		//}
		//else
		//{
		//	for (int i = Rabbits.size() - 1; i >= 0; i--)
		//	{
		//		if (i % 2 == 0)
		//			Rabbits.erase(Rabbits.begin() + i);
		//	}
		//}

	}
	for (int i = Rabbits.size() - 1; i >= 0; i--) {
		std::string ColorInfo;
		for (int j = 0; j < 3; j++)
			ColorInfo.append(j > 0 ? "," + std::to_string(Rabbits[i]->GetColor()[j]) : std::to_string(Rabbits[i]->GetColor()[j]));
		if (Rabbits[i]->GetMomPTR())
			Tools::LogUI(Rabbits[i]->GetFirstName() + " " + Rabbits[i]->GetLastName() + " " + std::to_string(Rabbits[i]->GetAge()) + " With Color of :" + ColorInfo + (Rabbits[i]->GetRadioactive() ? " RadioActive " : " Non RadioActive ") + " Child of: " + Rabbits[i]->GetMomPTR()->GetFirstName() + "  " + (Rabbits[i]->GetMomPTR())->GetLastName() + " with Age of: " + std::to_string(Rabbits[i]->GetMomPTR()->GetAge()), ExampleColor::White);
		else
			Tools::LogUI(Rabbits[i]->GetFirstName() + " " + Rabbits[i]->GetLastName() + " " + std::to_string(Rabbits[i]->GetAge()) + " With Color of :" + ColorInfo + (Rabbits[i]->GetRadioactive() ? " RadioActive " : " Non RadioActive "), ExampleColor::White);
	}
}