#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>
#include <functional>
#include "Vec.h"
#include <fstream>
#include <sstream>

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "doctest.h"
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


int main_011()
{

	Vec<int> IntVector;





	///////////////////
	// test 1 : reserve push/pop
	/*
	IntVector.reserve(100);
	std::cout << "pushing 119 elements" << std::endl;
	for (size_t i = 0; i < 119; i++)
	{
		IntVector.push_back(i);

	}
	std::cout << "popping 129 elements" << std::endl;
	for (size_t i = 0; i < 129; i++)
	{
		IntVector.pop_back();
	}
	*/







	///////////////////
	// test 2 : unreserved push/pop
	/*
	std::cout << "pushing 119 elements" << std::endl;
	for (size_t i = 0; i < 119; i++)
	{
		IntVector.push_back(i);

	}
	std::cout << "popping 129 elements" << std::endl;
	for (size_t i = 0; i < 129; i++)
	{
		IntVector.pop_back();
	}
	*/







	///////////////////
	// test 3 : unreserved push/pop at
	/*
	for (size_t i = 0; i < 4; i++)
	{
		IntVector.push_back(i);
		std::cout << i << std::endl;
	}
	for (size_t i = 1; i < 7; i++)
	{
		IntVector.push_at(2, i * 10);
		std::cout << i << std::endl;
	}
	std::cout << "------" << std::endl;
	for (auto it = IntVector.begin(); it < IntVector.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	std::cout << "------" << std::endl;
	IntVector.pop_at(2);
	IntVector.pop_at(2);
	for (auto it = IntVector.begin(); it < IntVector.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	*/









	///////////////////
	// test 4 : reserved push/pop at
	/*
	IntVector.reserve(100);
	for (size_t i = 0; i < 4; i++)
	{
		IntVector.push_back(i);
		std::cout << i << std::endl;
	}
	for (size_t i = 1; i < 7; i++)
	{
		IntVector.push_at(2, i * 10);
		std::cout << i << std::endl;
	}
	std::cout << "------" << std::endl;
	for (auto it = IntVector.begin(); it < IntVector.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	std::cout << "------" << std::endl;
	IntVector.pop_at(2);
	IntVector.pop_at(2);
	for (auto it = IntVector.begin(); it < IntVector.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	*/








	///////////////////
	// test 5 : unreserved clear 
	/*
	std::cout << "pushing 119 elements" << std::endl;
	for (size_t i = 0; i < 119; i++)
	{
		IntVector.push_back(i);

	}
	IntVector.clear();
	*/









	///////////////////
	// test 6 : reserved clear 
	/*
	IntVector.reserve(100);
	std::cout << "pushing 119 elements" << std::endl;
	for (size_t i = 0; i < 119; i++)
	{
		IntVector.push_back(i);

	}
	IntVector.clear();
	*/






	return 0;
}

/*

TEST_CASE("Vec Test")
{
	Vec<int> IntVector;

	SUBCASE("Checking push pop") {
		std::cout << "Checking push pop" << std::endl;
		IntVector.push_back(1);
		REQUIRE(IntVector.size() == 1);
		IntVector.pop_back();
		REQUIRE(IntVector.size() == 0);
	}

	SUBCASE("Checking push at") {

		SUBCASE("Natural Numbers Input Domain [0,inf) ")
		{
			SUBCASE("Natural Numbers outside vec length")
			{
				// REQUIRE(IntVector.size() == 0);
				// true because the subcases dont matter and each one runs separately

				/// <summary>
				///  found crash : using push at when the Vec is not that long
				/// like using push_at(10,1) on an emtpy vec
				/// </summary>
				// x IntVector.push_at(1, 1);
				IntVector.push_at(1, 1);
				REQUIRE(IntVector.size() == 0);

				IntVector.push_at(10, 1);
				REQUIRE(IntVector.size() == 0);

				IntVector.push_at(100, 1);
				REQUIRE(IntVector.size() == 0);
			}
			SUBCASE("Natural Numbers inside vec length")
			{

				for (size_t i = 0; i < 10; i++)
				{
					IntVector.push_back(10);
				}
				IntVector.push_at(0, 1);
				CHECK(IntVector.size() == 11);

				IntVector.push_at(1, 1);
				CHECK(IntVector.size() == 12);
				IntVector.push_at(5, 1);
				CHECK(IntVector.size() == 13);


				IntVector.push_at(IntVector.size(), 1);
				REQUIRE(IntVector.size() == 14);
			}
		}
		SUBCASE("Negative Numbers Input Domain (-inf,-1] ")
		{
			IntVector.push_at(-1, 1);
			REQUIRE(IntVector.size() == 0);
		}

	}

}*/






/// advent of code
void SortVector(const std::vector<int>& InVector, std::vector<int>& Result)
{
	for (auto It = InVector.begin(); It < InVector.end(); It++)
	{
		if (Result.size() == 0) {
			Result.push_back(*It);
			continue;
		}
		for (auto SecondIt = Result.begin(); SecondIt < Result.end();)
		{
			if (*It <= *SecondIt)
			{
				Result.insert(SecondIt, *It);
				break;
			}
			if (*It > *SecondIt)
			{
				SecondIt++;
				if (SecondIt == Result.end())
				{
					Result.push_back(*It);
					break;
				}
			}
		}
	}
}






/// advent of code #1
int main11()
{
	std::ifstream file("star1data.txt"); // Replace with actual file
	std::vector<int> LeftIntVector, RightIntVector;
	int Num1, Num2;

	while (file >> Num1 >> Num2) {
		LeftIntVector.push_back(Num1);
		RightIntVector.push_back(Num2);
	}

	std::vector<int> SortedLeftInt;
	std::vector<int> SortedRightInt;

	SortVector(LeftIntVector, SortedLeftInt);
	SortVector(RightIntVector, SortedRightInt);

	int Sum = 0;
	for (int i = 0; i < RightIntVector.size(); i++)
	{
		std::cout << SortedRightInt[i] << " , " << SortedLeftInt[i] << std::endl;
		Sum += std::abs(SortedRightInt[i] - SortedLeftInt[i]);
	}
	std::cout << "-----" << std::endl;

	std::cout << Sum << std::endl;
	std::cout << "-----" << std::endl;
	int SimilarityScore = 0;
	for (auto It : SortedLeftInt)
	{
		int RepeatCount = 0;
		for (auto SecondIt : SortedRightInt)
		{
			if (SecondIt == It)
			{
				RepeatCount++;
			}
		}
		SimilarityScore += RepeatCount * It;
	}
	std::cout << SimilarityScore << std::endl;
	return 0;
}

typedef std::ifstream ifstream;
typedef std::string string;

bool EvaluateReport(const string& InLine)
{
	std::stringstream Stream(InLine);
	int Num;
	int LastNum = 0;
	int UnsafeIndex = -1;
	int Direction = 0; // -1 0 1 
	while (Stream >> Num) {
		if (LastNum == 0)
		{
			LastNum = Num;
		}
		else
		{
			if (std::abs(Num - LastNum) >= 1 && std::abs(Num - LastNum) <= 3)
			{
				if (Direction == 0)
				{
					Direction = (Num - LastNum) > 0 ? 1 : -1;
				}
				else
				{
					if (Direction != ((Num - LastNum) > 0 ? 1 : -1))
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
			LastNum = Num;
		}
	}
	return true;
}
bool SafeEvaluateReport(const string& InLine)
{
	std::stringstream Stream(InLine);
	std::vector<int> Numbers;
	int Num;
	int LastNum = 0;
	int UnsafeIndex = -1;
	int Direction = 0; // -1 0 1 
	while (Stream >> Num)
	{
		Numbers.push_back(Num);
	}
	for (size_t i = 0; i < Numbers.size(); i++)
	{
		std::vector<int> TempNumbers = Numbers;
		TempNumbers.erase(TempNumbers.begin() + i);
		std::ostringstream oss;
		for (size_t i = 0; i < TempNumbers.size(); ++i) {
			if (i > 0) oss << " ";  // Add space before every element except the first
			oss << TempNumbers[i];
		}
		if (EvaluateReport(oss.str()))
			return true;
	}
	return false;
}

/// advent of code #2
int main_01()
{
	// Create an input file stream object named 'file' and
   // open the file "GFG.txt".
	ifstream File("star2data.txt");

	// String to store each line of the file.
	string Line;
	int SafeReports = 0;
	if (File.is_open()) {
		// Read each line from the file and store it in the
		// 'line' variable.
		while (getline(File, Line)) {
			if (EvaluateReport(Line))
			{
				SafeReports++;
			}
			else
			{
				if (SafeEvaluateReport(Line))
					SafeReports++;
			}
		}

		// Close the file stream once all lines have been
		// read.
		File.close();
	}
	else {
		// Print an error message to the standard error
		// stream if the file cannot be opened.
		std::cerr << "Unable to open file!" << std::endl;
	}
	std::cout << SafeReports;
	return 0;
}