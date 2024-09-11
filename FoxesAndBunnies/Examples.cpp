#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>

int Sum(int& v1, int& v2)
{
	return v1 + v2;
}

class TArrayOfInts
{
	int* arrPtr;
	int size;
};

int main_example_2708()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	int* arrPtr = arr;
	std::cout << *arrPtr; // 1
	std::cout << *(arrPtr + 1); // 2;
	std::cout << *(arrPtr + 2); // 3;
	std::cout << arrPtr[2]; // is exactly the same as *(arrPtr + 2)
	std::cout << *(2 + arrPtr); // 3
	std::cout << 2[arrPtr]; // 3

	int n;
	std::cin >> n;
	int* newArr = new int[n];

	delete newArr;

	int num = 3;
	int another = 42;
	int* ptr = &num;
	int& ref = num;

	int result = Sum(num, another);


	return 0;
}


// Nikola: Avoid mixing code with different goals
// e.g. UI and gameplay should be separate
// Option 1: Move the UI / logging code to a separate function
// Option 2: Use events/delegates, which is much more difficult to do right now, so let's leave for the future


// Nikola: Don't use magic numbers
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
//std::vector<RabbitExample>* RabbitsPTR = &Rabbits;
// init


// Nikola: To access the internal data with +
// This is commented because if you try to do it with an empty vector it will crash
//RabbitExample* UnderlyingPtr = Rabbits.data();
//RabbitExample* SecondElementPtr = (UnderlyingPtr + 1);

int MomReferences = 0;

struct SharedPtrHelper
{
	class RabbitExample* RabbitExample = nullptr;
	bool IsValid;

	SharedPtrHelper()
	{
		MomReferences++;
	}

	~SharedPtrHelper()
	{
		MomReferences--;
		if (MomReferences == 0)
		{
			delete RabbitExample;
			IsValid = false;
		}
	}
};

struct Necklace {};

struct RabbitExample
{
	const char* Name = "Anna";
	std::unique_ptr<Necklace> Jewelery;
	std::shared_ptr<RabbitExample> Mom;
	std::weak_ptr<RabbitExample> MomButForgotten;
};



int main_examples_0309()
{
	std::vector<std::shared_ptr<RabbitExample>> rabbits;
	rabbits.push_back(std::make_shared<RabbitExample>());
	rabbits.push_back(std::make_shared<RabbitExample>());
	rabbits.push_back(std::make_shared<RabbitExample>());

	std::shared_ptr<RabbitExample> keepForgottenMotherAlive;
	{
		std::shared_ptr<RabbitExample> m = std::make_shared<RabbitExample>();
		rabbits[0]->Mom = m;
		rabbits[1]->Mom = m;
		rabbits[2]->Mom = m;

		std::shared_ptr<RabbitExample> forgottenM = std::make_shared<RabbitExample>();
		rabbits[0]->MomButForgotten = forgottenM;
		rabbits[1]->MomButForgotten = forgottenM;
		rabbits[2]->MomButForgotten = forgottenM;
		keepForgottenMotherAlive = forgottenM;
	}
	if (rabbits[0]->Mom) // r.Mom == 0x420
	{
		std::cout << rabbits[0]->Mom->Name;
	}
	if (std::shared_ptr<RabbitExample> m = rabbits[0]->MomButForgotten.lock()) // r.Mom == 0x420
	{
		std::cout << "Forgotten mom is still valid: " << m->Name;
	}
	else
	{
		std::cout << "Forgotten mom is no longer valid";
	}
	
	return 0;
}

struct Rabbit
{
	bool IsRadioactive;
	int Age;
	bool IsMale;
};

int SquareInteger(int num)
{
	return num * num;
}

bool IsOld(const Rabbit& rabbit)
{
	return rabbit.Age > 10;
}
bool IsRabbitMale(const Rabbit& rabbit)
{
	return rabbit.IsMale;
}
bool CanRabbitBeMother(const Rabbit& rabbit)
{
	return !rabbit.IsMale && rabbit.Age >= 10 && !rabbit.IsRadioactive;
}



Rabbit BreedRabbit(const Rabbit& mother)
{
	//assert(!mother.IsMale);
	Rabbit r;
	r.Age = 0;
	r.IsMale = rand() % 2;
	r.IsRadioactive = false;
	return r;
}

int main_examples_110924()
{
	// Old way
	// 0 load 0x567 42
	// 1 add 0x123 0x567
	// 2 cmp 0x567 42 
	// 3 jmp 10
	// 	...
	// 10 ...

	// 2 New ways
	// OOP: Rabbit { age, food, isRadioactive }; vector<Rabbit> list
	// Functional / data programming: vector<int> listOfAges; vector<food> listOfHunger; vector<bool> listOfRadioactivity

	std::vector<int> values = { 4, 5, 10, 15, 600 };
	int sum = 0;
	for (int& v : values)
	{
		sum += v;
	}
	std::cout << sum << "\n";

	int functionalSum = std::accumulate(values.begin(), values.end(), 0);

	std::sort(values.begin(), values.end());

	std::random_shuffle(values.begin(), values.end());

	std::vector<int> squaredValues;
	std::transform(values.begin(), values.end(), std::back_inserter(squaredValues), SquareInteger);
	for (int& num : squaredValues)
	{
		std::cout << num << " ";
	}
	std::cout << "\n";

	std::vector<Rabbit> rabbits = {
		{ true, 10, false },
		{ false, 15, false },
		{ false, 25, true },
		{ true, 17, true },
	};

	auto IsRabbitRadioactive = [](const Rabbit& rabbit)
		{
			return rabbit.IsRadioactive;
		};

	int numRadioactive = std::count_if(rabbits.begin(), rabbits.end(), IsRabbitRadioactive);
	std::cout << "Radioactive: " << numRadioactive << "\n";

	int numOld = std::count_if(rabbits.begin(), rabbits.end(), IsOld);
	std::cout << "Old: " << numOld << "\n";

	bool isThereAMale = std::any_of(rabbits.begin(), rabbits.end(), IsRabbitMale);
	bool AreAllRadioactive = std::all_of(rabbits.begin(), rabbits.end(), IsRabbitRadioactive);

	std::transform(rabbits.begin(), rabbits.begin() + rabbits.size() - 1, std::back_inserter(rabbits), BreedRabbit);

	rabbits.erase(std::remove_if(rabbits.begin(), rabbits.end(), IsOld), rabbits.end());

	for (const Rabbit& r : rabbits)
	{
		std::cout << r.Age << " ";
	}
	std::cout << "\n";

	auto SquareNum = [](int num) { return num * num; };
	std::transform(values.begin(), values.end(), std::back_inserter(squaredValues), SquareNum);

	return 0;
}