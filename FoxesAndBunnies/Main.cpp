#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib> 
#include "NameStorage.h"
#include "Rabbit.h"


struct Info {
	int Age;
};


int main()
{

	std::string myString = "Hello, world!";
	std::cout << myString;
	std::cout << "\n";
	std::cout << myString.length();


	
	std::vector<int> myList = { 2, 3 };
	myList.push_back(5); // 2 3 5
	myList.push_back(42); // 2 3 5 42
	myList.pop_back(); // 2 3 5
	myList.size(); // 3
	myList[2]; // 5

	myList.insert(myList.begin() + 1, 32); // 2 32 3 5
	myList.erase(myList.begin() + 1); // 2 3 5

	// init

	while (true)//ecosystemAlive)
	{
		std::cout << "\n";
		Rabbit x;

		Rabbit y;
		Rabbit z(y.GetColor());
		//std::cout << NameStorage::RandomName();

		// input break
		char tempVariableToMakeTheLoopWait = ' ';
		std::cin >> tempVariableToMakeTheLoopWait;

		// automatic wait
		std::this_thread::sleep_for(std::chrono::milliseconds(100));  
	}


	// end 
	// 
	//std::cout << "Hello, world!";
	return 0;
}