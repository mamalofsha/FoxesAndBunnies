#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib> 
#include "NameStorage.h"
#include "Rabbit.h"
#include "World.h"

bool SetupInput();
void WorldCycle(World* InWorld);
bool AutomaticWait;

int main()
{
	World* CurrentWorld = new World(5, 500, 5);
	std::cout << "World started!";
	AutomaticWait = SetupInput();
	while (CurrentWorld->GetWorldHeartBeat())
		WorldCycle(CurrentWorld);
	std::cout << "World Ended!";
	return 0;
}

bool SetupInput()
{
	std::cout << "Automatic Cycle ? ";
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