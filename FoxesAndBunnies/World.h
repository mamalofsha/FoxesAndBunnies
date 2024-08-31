#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Rabbit.h"

enum WorldObjectType
{
	Rabbyte,
	Grass,
	Foxes
};
enum RatioType
{
	Radioactivity,
	Age,
};

class World
{
private:
	bool EcosystemOnline = false;
	int MaxGrassCount = 500;
	int GrassCount = 500;
	std::vector<Rabbit> Rabbits;
protected:
	void SpawnRabbit(std::vector<Rabbit>& InRabbits,int InCount = 1);
	Rabbit* GetFirstMaleInList();
	Rabbit* GetFirstNonRadioActive();
	int Average(RatioType InRatioType);

public:
	World(int InRabbitCount = 5, int InGrassCount = 500, int InFoxCount = 5);

	void Increase(WorldObjectType InWorldType,int InCount = 1);
	int GetGrassCount();
	bool GetWorldHeartBeat();
	std::vector<Rabbit>& GetRabbits();
	void MoveCycleForward();
};

