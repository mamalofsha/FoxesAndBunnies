#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Rabbit.h"
#include "Fox.h"

enum WorldObjectType
{
	TypeOfRabbit,
	TypeOfGrass,
	TypeOfFox
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

	std::vector<std::shared_ptr<Rabbit>> Rabbits;
	std::vector<std::shared_ptr<Fox>> Foxes;
protected:
	void SpawnRabbit(int InCount = 1);
	void SpawnFox(int InCount = 1);
	std::shared_ptr<Rabbit> GetFirstMaleInList();
	std::shared_ptr<Rabbit> GetFirstNonRadioActive();
	int Average(RatioType InRatioType);
public:
	std::shared_ptr<Rabbit> BreedRabbit(const std::shared_ptr<Rabbit>& InMom);
	World(int InRabbitCount = 5, int InGrassCount = 500, int InFoxCount = 2);
	void Increase(WorldObjectType InWorldType,int InCount = 1);
	int GetGrassCount();
	bool GetWorldHeartBeat();
	std::vector<std::shared_ptr<Rabbit>> GetRabbits();
	std::vector<std::shared_ptr<Fox>> GetFoxes();
	void MoveCycleForward();
};