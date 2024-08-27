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


void InitWorld(std::vector<Rabbit>& InArray)
{
	std::cout << std::endl;
	for (int i = 0; i < 5; i++)
	{
		Rabbit x;
		InArray.push_back(x);
	}
}

Rabbit* GetFirstMaleInList(std::vector<Rabbit>& InArray)
{

	for (int i = 0; i < InArray.size(); i++)
	{

		if (InArray[i].GetIsMale())
			return &InArray[i];

		// return Rabbits[i] and check for if it's valid 

	}

	return nullptr;
}


int Average(RatioType InRatioType, std::vector<Rabbit>& InArray)
{
	int total = 0;
	for (int i = 0; i < InArray.size(); i++)
	{
		switch (InRatioType)
		{
		case Radioactivity:
			total += (InArray[i].GetRadioactive() ? 1 : 0) * 100;
			break;
		case Age:
			total += InArray[i].GetAge();
			break;
		default:
			break;
		}
	}


	return total / InArray.size();
}

int GetFirstNonRadioActive(std::vector<Rabbit>& InArray)
{
	for (int i = 0; i < InArray.size(); i++)
	{

		if (!InArray[i].GetRadioactive())
			return i;

		// return Rabbits[i] and check for if it's valid 

	}

	return -1;
}

int main()
{
	std::vector<Rabbit> Rabbits;
	std::vector<Rabbit>* RabbitsPTR = &Rabbits;
	// init
	std::cout << "World started!" << "\b";
	InitWorld(Rabbits);
	bool bEcosystemAlive = true;

	std::cout << "Automatic Cycle ? ";
	char InputForCycle;
	std::cin >> InputForCycle;
	bool AutomaticWait = (InputForCycle == 'y');

	int grassCount = 500;
	int grassMax = 500;
	int lastSize = 5;
	while (bEcosystemAlive)//ecosystemAlive)
	{

		int erased = 0;

		// age up rabbits , remove them if dead
		for (int i = Rabbits.size() - 1; i >= 0; i--)
			if (Rabbits[i].AgeUp()) {
				Rabbits.erase(Rabbits.begin() + i);
				erased++;
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
			if (GetFirstNonRadioActive(Rabbits) > -1)
				Rabbits[GetFirstNonRadioActive(Rabbits)].TurnRadioActive(false);
		}
		infectors.clear();




		/// feed 
		for (int i = Rabbits.size() - 1; i >= 0; i--) {

			int grassCost = Rabbits[i].GetRadioactive() ? 4 : 2;

			if (grassCount > grassCost)
				grassCount -= grassCost;
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
						Rabbit x(GetFirstMaleInList(Rabbits)->GetLastName(), Rabbits[i].GetColor(),i , Rabbits[i]);
						Rabbits.push_back(x);
					}
				}

		}





		if (Rabbits.size() == 0) {
			bEcosystemAlive = false;
		}
		else
		{
			HANDLE  hConsole{};
			int k = 15;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, k);

			std::cout << "cycle passed " << std::endl << std::endl;

			std::cout << "Total Rabbit Population: " + std::to_string(Rabbits.size()) << std::endl;

			std::cout << "Total Grass Remaining : " + std::to_string(grassCount) << std::endl;
			grassCount++;

			std::cout << "With Average age of: " + std::to_string(Average(RatioType::Age,Rabbits)) << std::endl;

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
				if (Rabbits[i].GetMomIndex()>-1)
				{
					Rabbits[i].ShiftIndex(erased);
					if (Rabbits[i].GetMomIndex() > -1)
					{
						int index = Rabbits[i].GetMomIndex();
						std::cout << Rabbits[i].GetMomPTR()->GetAge()<< "-.-";
						std::cout << Rabbits[i].GetFirstName() << " " << Rabbits[i].GetLastName() << " " << Rabbits[i].GetAge() << " Child of: " << Rabbits[index].GetFirstName() << "  " << Rabbits[index].GetLastName() <<"-----------" << Rabbits[index].GetAge() << std::endl;
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