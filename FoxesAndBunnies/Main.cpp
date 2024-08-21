#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib> 
#include "NameStorage.h"
#include "Rabbit.h"




enum RatioType
{
	Radioactivity,
	Age,
};

std::vector<Rabbit> Rabbits;

void InitWorld()
{
	std::cout << "\n";
	for (int i = 0; i < 5; i++)
	{
		Rabbit x;
		Rabbits.push_back(x);
	}
}

int GetFirstMaleInList()
{
	for (int i = 0; i < Rabbits.size(); i++)
	{

		if (Rabbits[i].GetIsMale())
			return i;

		// return Rabbits[i] and check for if it's valid 

	}

	return -1;
}


int Average(RatioType InRatioType)
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


	return total / Rabbits.size();
}

int GetFirstNonRadioActive()
{
	for (int i = 0; i < Rabbits.size(); i++)
	{

		if (!Rabbits[i].GetRadioactive())
			return i;

		// return Rabbits[i] and check for if it's valid 

	}

	return -1;
}

int main()
{

	// init
	std::cout << "World started!";
	InitWorld();
	bool bEcosystemAlive = true;

	std::cout << "Automatic Cycle ? ";
	char InputForCycle;
	std::cin >> InputForCycle;
	bool AutomaticWait = (InputForCycle == 'y');

	while (bEcosystemAlive)//ecosystemAlive)
	{

		// age up rabbits , remove them if dead
		for (int i = 0; i < Rabbits.size(); i++) {
			if (Rabbits[i].AgeUp())
				Rabbits.erase(Rabbits.begin() + i);
		}


		std::vector<int> infectors;
		for (int i = 0; i < Rabbits.size(); i++) {

			if (Rabbits[i].GetRadioactive())
			{
				infectors.push_back(i);

			}
		}
		for (int i = 0; i < infectors.size(); i++)
		{
			if (GetFirstNonRadioActive() > -1)
				Rabbits[GetFirstNonRadioActive()].TurnRadioActive(false);
		}
		infectors.clear();

		// mate
		for (int i = 0; i < Rabbits.size(); i++)
		{
			if (!Rabbits[i].GetIsMale())
				if (Rabbits[i].EligibleForBreeding()) {
					if (GetFirstMaleInList() > -1) {
						Rabbit x(Rabbits[GetFirstMaleInList()].GetLastName(), Rabbits[i].GetColor());
						Rabbits.push_back(x);
					}
				}

		}





		if (Rabbits.size() == 0) {
			bEcosystemAlive = false;
		}
		else
		{
			std::cout << "cycle passed ";
			std::cout << "\n";

			std::cout << "Total Rabbit Population: " + std::to_string(Rabbits.size());
			std::cout << "\n";

			std::cout << "With Average age of: " + std::to_string(Average(RatioType::Age));
			std::cout << "\n";

			std::cout << std::to_string(Average(RatioType::Radioactivity)) + "% Radioactive";
			std::cout << "\n";
		}


		//Rabbit z(x.GetLastName(), y.GetColor());
		//std::cout << NameStorage::RandomName();

		if (AutomaticWait)
		{
			// automatic wait
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else
		{
			// input break
			char tempVariableToMakeTheLoopWait = ' ';
			std::cin >> tempVariableToMakeTheLoopWait;
		}



	}

	std::cout << "World Ended!";


	return 0;
}















/*
*
	std::string myString = "Hello, world!";
	//std::cout << myString;
	std::cout << "\n";
	//std::cout << myString.length();



	std::vector<int> myList = { 2, 3 };
	myList.push_back(5); // 2 3 5
	myList.push_back(42); // 2 3 5 42
	myList.pop_back(); // 2 3 5
	myList.size(); // 3
	myList[2]; // 5

	myList.insert(myList.begin() + 1, 32); // 2 32 3 5
	myList.erase(myList.begin() + 1); // 2 3 5
*/