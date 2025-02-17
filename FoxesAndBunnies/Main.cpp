#include <iostream>
#include <thread>
#include <chrono>
#include "Rabbit.h"
#include "World.h"
#include "Tools.h"
//#include "doctest.h"


bool SetupInput();
void WorldCycle(World* InWorld);
bool AutomaticWait;

int main01()
{
	World* CurrentWorld = new World(5, 500, 2);
	Tools::LogUI("World Started !", ExampleColor::White);
	AutomaticWait = SetupInput();
	while (CurrentWorld->GetWorldHeartBeat())
		WorldCycle(CurrentWorld);
	Tools::LogUI("World Ended!", ExampleColor::White);
	return 0;
}

bool SetupInput()
{
	Tools::LogUI("Automatic Cycle ? ", ExampleColor::White);
	char InputForCycle;
	std::cin >> InputForCycle;
	return (InputForCycle == 'y');
}

void WorldCycle(World* InWorld)
{
	InWorld->MoveCycleForward();
	if (AutomaticWait)
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	else {
		char tempVariableToMakeTheLoopWait = ' ';
		std::cin >> tempVariableToMakeTheLoopWait;
	}
}

/*
TEST_CASE("Rabbit Test")
{
	SUBCASE("auto test")
	{
		SUBCASE("World lives as long as there's a rabbit")
		{
			World* CurrentWorld = new World(5, 500, 2);
			Tools::LogUI("World Started !", ExampleColor::White);
			AutomaticWait = true;
			while (CurrentWorld->GetWorldHeartBeat())
			{
				CHECK(CurrentWorld->GetRabbits().size() > 0);
				WorldCycle(CurrentWorld);
			}
			Tools::LogUI("World Ended!", ExampleColor::White);
		}
		SUBCASE("RabbitMom-PTR should stay alive when it's not in the main rabbit list")
		{
			World* CurrentWorld = new World(5, 500, 2);
			Tools::LogUI("World Started !", ExampleColor::White);
			AutomaticWait = true;
			while (CurrentWorld->GetWorldHeartBeat())
			{
				for (auto Rabbit : CurrentWorld->GetRabbits())
				{
					if (Rabbit->GetMomPTR())
					{
						bool ValidRabbitMomPTR = false;
						for (auto PossibleRabbitMom : CurrentWorld->GetRabbits())
						{
							if (PossibleRabbitMom == Rabbit->GetMomPTR())
							{
								ValidRabbitMomPTR = true;
								break;
							}
						}
						if (!ValidRabbitMomPTR)
						{
							REQUIRE_FALSE(ValidRabbitMomPTR);
							REQUIRE(true);
						}
					}
				}
				WorldCycle(CurrentWorld);
			}
			Tools::LogUI("World Ended!", ExampleColor::White);
		}
		SUBCASE("are rabbits being fed right ?")
		{
			World* CurrentWorld = new World(5, 500, 0);
			Tools::LogUI("World Started !", ExampleColor::White);
			AutomaticWait = true;
			while (CurrentWorld->GetWorldHeartBeat())
			{
				CHECK(CurrentWorld->GetRabbits().size() > 0);
				int BeforeTickGrassCount = CurrentWorld->GetGrassCount();
				int RabbitFoodCount = 0;

				WorldCycle(CurrentWorld);
				for (auto Rabbit : CurrentWorld->GetRabbits())
				{
					if (Rabbit->GetAge() > 0)
						RabbitFoodCount += Rabbit->GetRadioactive() ? 4 : 2;
				}
				// -1 is because of grass regrowth
				CHECK(CurrentWorld->GetGrassCount() - 1 == BeforeTickGrassCount - RabbitFoodCount);
			}
			Tools::LogUI("World Ended!", ExampleColor::White);
		}
		SUBCASE("are rabbits dying of old age ?")
		{
			World* CurrentWorld = new World(5, 500, 0);
			Tools::LogUI("World Started !", ExampleColor::White);
			AutomaticWait = true;
			while (CurrentWorld->GetWorldHeartBeat())
			{
				CHECK(CurrentWorld->GetRabbits().size() > 0);
				for (auto Rabbit : CurrentWorld->GetRabbits())
				{
					if (!Rabbit->GetRadioactive())
						REQUIRE(Rabbit->GetAge() <= 10);
					else
						REQUIRE(Rabbit->GetAge() <= 50);

				}
				WorldCycle(CurrentWorld);

			}
			Tools::LogUI("World Ended!", ExampleColor::White);
		}
		SUBCASE("food shortage")
		{
			World* CurrentWorld = new World(1234, 50011100, 0);
			Tools::LogUI("World Started !", ExampleColor::White);
			AutomaticWait = true;
			bool ShortageOnTheWay = true;
			while (CurrentWorld->GetWorldHeartBeat())
			{
				CHECK(CurrentWorld->GetRabbits().size() > 0);
				int RabbitSize;
				if (ShortageOnTheWay)
					RabbitSize = CurrentWorld->GetRabbits().size();
			
				WorldCycle(CurrentWorld);
				if (ShortageOnTheWay)
				{
					REQUIRE(CurrentWorld->GetRabbits().size() < RabbitSize / 2);
					ShortageOnTheWay = false;
				}
			}
			Tools::LogUI("World Ended!", ExampleColor::White);
		}
		SUBCASE("child foxes can't hunt")
		{
			World* CurrentWorld = new World(0, 10000, 10);
			Tools::LogUI("World Started !", ExampleColor::White);
			AutomaticWait = true;
			while (CurrentWorld->GetWorldHeartBeat())
			{
				//CHECK(CurrentWorld->GetRabbits().size() > 0);
				int ChildFoxes = 0;
				for (auto Fox : CurrentWorld->GetFoxes())
				{
					ChildFoxes += Fox->GetAge() >=0 && Fox->GetAge() < 2? 1 : 0;
				}

				WorldCycle(CurrentWorld);
				int NewChildFoxes=0;
				for (auto Fox : CurrentWorld->GetFoxes())
				{
					NewChildFoxes += (Fox->GetAge() > 0 && Fox->GetAge() < 3)? 1 : 0;
				}
				REQUIRE(ChildFoxes == NewChildFoxes);
			}
			Tools::LogUI("World Ended!", ExampleColor::White);
		}
	}
}*/