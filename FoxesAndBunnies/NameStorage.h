#pragma once
#include <string>
#include <vector>
#include <cstdlib> 
#include <random>

using u32 = uint_least32_t;
using engine = std::mt19937;

class NameStorage
{
private :
	static std::vector<std::string> MaleFirstNames;
	static std::vector<std::string> FemaleFirstNames;
	static std::vector<std::string> LastNames;
public:
	static std::string RandomFullName(bool IsMale);
	static std::string RandomFirstName(bool IsMale);
	static std::string RandomLastName();
};












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


// Nikola: You don't need to use a ptr to the rabbits, can always pass the original vector
//std::vector<Rabbit>* RabbitsPTR = &Rabbits;
// init


// Nikola: To access the internal data with +
// This is commented because if you try to do it with an empty vector it will crash
//Rabbit* UnderlyingPtr = Rabbits.data();
//Rabbit* SecondElementPtr = (UnderlyingPtr + 1);

