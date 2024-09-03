#include <iostream>
#include <string>
#include <vector>

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