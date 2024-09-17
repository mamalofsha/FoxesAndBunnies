#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>
#include <functional>

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

// DELEGATES AND EVENTS -- 17.09.2024 -----------------------------

// NIKOLA FIX LATER
template<typename SourceType>
void transform_if(
	typename std::vector<SourceType>::iterator begin,
	typename std::vector<SourceType>::iterator end
	//std::back_insert_iterator<std::vector<TransformedType>> output,
	//Predicate predicate,
	//Transformer transformer
	)
{
	//for (; begin != end; begin++)
	//{
	//	if (predicate(*begin))
	//		output = transformer(*begin); // no need to call output++ because back insert iterators auto-increment
	//}
}

class Button
{
public:
	void Click()
	{
		// 42  | 2 | 55 | 123
		OnClickHandler();
	}
	void (*OnClickHandler)() = nullptr;
};

// The "using" keyword allows you to give a new name to an existing type
using Integer = int;
Integer number = 42;

using RabbitVec = std::vector<Rabbit>;
RabbitVec vec = { {false, 1, true} };

class Character
{
public:
	// It's very ugly to always spell out the full func name...so alias it!
	using FDamageTakenHandler = void (*)(int);
	void TakeDamage()
	{
		// note: since all delegates are equal, if they were to return a value
		// we wouldn't know which one to use
		// so multicast delegates aren't allowed to return a value at all
		for (FDamageTakenHandler handler : OnDamageTakenHandlers)
		{
			handler(1);
		}
	}
	std::vector<FDamageTakenHandler> OnDamageTakenHandlers;
};

void StartGame() { std::cout << "Start game \n"; }
void SaveSettings() { std::cout << "Saving settings \n"; }

int ComputeSquare(int num) { return num * num; }

void UpdateHealthbar(int damageAmount) { std::cout << "Updating hp...\n"; }
void PlayBloodVFX(int damageAmount) { std::cout << "Blood splatter...\n"; }


struct AutogeneratedLambda_65326715673
{
	Button& saveButton;
	void operator()(int damage)
	{
		saveButton.Click();
	}
};

// With std::function
class OnlineService
{
public:
	using FriendOnlineDelegate = std::function<void(const std::string&)>;
	void UpdateData()
	{
		for (const FriendOnlineDelegate& handler : Handlers)
		{
			handler("Nikola");
		}
	}
	std::vector<FriendOnlineDelegate> Handlers;
};

// DECLARE...DELEGATE
struct OnFriendStatusChanged
{
	using FriendOnlineDelegate = std::function<void(const std::string&)>;
	std::vector<FriendOnlineDelegate> Handlers;
};

OnFriendStatusChanged NewFriendOnlineEvent;
OnFriendStatusChanged FriendDisconnectedEvent;
OnFriendStatusChanged FriendGoingInGameEvent;

// this is wrong
struct DelegateGoldTeam1Changed {};
struct DelegateGoldTeam2Changed {};

DelegateGoldTeam1Changed Team1GoldChanged;
DelegateGoldTeam2Changed Team2GoldChanged;
// this is better
struct DelegateGoldTeamChanged {};
DelegateGoldTeamChanged CorrectTeam1GoldChanged;
DelegateGoldTeamChanged CorrectTeam2GoldChanged;


int main_examples_170924()
{
	//std::vector<Rabbit> rabbits = { { false, 5, true } };
	//std::vector<int> ages;
	//auto IsOldEnough = [](const Rabbit& r) { return r.Age >= 1; };
	//auto GetAge = [](const Rabbit& r) { return r.Age; };
	//transform_if(rabbits.begin(), rabbits.end());//, std::back_inserter(ages), IsOldEnough, GetAge);


	void (*MyFunctionPtr)() = &StartGame;
	MyFunctionPtr(); // this is the same as StartGame();
	// MyFunctionPtr = &ComputeSquare; won't work, different function types
	int (*AnotherFuncPtr)(int) = &ComputeSquare;

	// A button has a SINGLECAST delegate
	Button b;
	b.OnClickHandler = &StartGame;
	b.Click();

	Button saveButton;
	saveButton.OnClickHandler = &SaveSettings;
	saveButton.Click();

	// The character has a MULTICAST delegate
	Character hero;
	hero.OnDamageTakenHandlers.push_back(&UpdateHealthbar);
	Character::FDamageTakenHandler myDelegate = &PlayBloodVFX;
	// Similar to how you sometimes in Unreal need to create a new delegate
	// FSomeRandomDelegate Delegate = FSomeRandomDelegate::Create(this, &FuncName);
	hero.OnDamageTakenHandlers.push_back(myDelegate);
	// without capture
	Character::FDamageTakenHandler lambdaDamageHandler = [](int damage) { std::cout << "DamageLambda\n"; };
	// When you have a lambda with no capture, compiler creates a normal function\
	// [](int damage) { std::cout << "DamageLambda\n"; }; -> gets converted to
	// void Autogenerated_123712421768(int damage)
	// { std::cout << "DamageLambda\n"; };
	hero.OnDamageTakenHandlers.push_back(lambdaDamageHandler);
	// with capture - wont be allowed to be pushed back
	auto lambdaWithCapture = [&saveButton](int damage) { saveButton.Click(); };
	// instead of function, it generates a struct, see struct above
	// Example of struct as func
	AutogeneratedLambda_65326715673 lambda = { saveButton };
	lambda(5);

	hero.OnDamageTakenHandlers.push_back(lambdaDamageHandler);
	hero.TakeDamage();


	// Because of the differences between lambdas and function ptrs, introduce std::function
	std::function<void(int)> myGenericFunction; // in unreal, this is TFunction
	myGenericFunction = lambdaWithCapture;
	myGenericFunction = lambdaDamageHandler;
	myGenericFunction = &PlayBloodVFX;

	// online service
	OnlineService service;
	service.Handlers.push_back([&saveButton](const std::string& friendName)
		{
			std::cout << "Friend just got online " << friendName << "\n";
		});
	int onlineFriends = 10;
	auto updateOnlineFriendCount = [&onlineFriends](const std::string& friendName) { onlineFriends++; };
	service.Handlers.push_back(updateOnlineFriendCount);
	service.UpdateData();

	// DECLARE_<>_DELEGATE
	// singlecast -> just 1 handler
	// multicast -> as many handlers as you  need; cannot return value
	// dynamic -> can be bound to Blueprint functions

	return 0;
}