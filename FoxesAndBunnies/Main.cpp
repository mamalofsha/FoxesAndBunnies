#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib> 
#include "NameStorage.h"
#include "Rabbit.h"
#include "World.h"
#include "Tools.h"

bool SetupInput();
void WorldCycle(World* InWorld);
bool AutomaticWait;

int main()
{
	World* CurrentWorld = new World(5, 500, 5);
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