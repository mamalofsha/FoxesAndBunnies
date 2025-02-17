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
#include <regex>

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




// algo sort \ accumulate

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
					// just get sign and use that for +-
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


std::string ReadFileConvertToString(const std::string& FileName)
{
	std::ifstream file(FileName); // Replace with actual file
	std::stringstream StringStream;
	StringStream << file.rdbuf(); // Read file content into buffer
	return StringStream.str();
}

std::vector<int> FindOccurances(const std::string& Data, const std::string& SearchCase)
{
	std::vector<int> Output;
	int res = -1;
	while ((res = Data.find(SearchCase, res + 1)) != string::npos)
	{
		Output.push_back(res);
	}
	return Output;
}

bool Is_Number(const std::string& s) {
	static const std::regex number_regex(
		R"(^[-+]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][-+]?\d+)?$)"
	);
	return std::regex_match(s, number_regex);
}


std::vector<std::pair<int, int>> ProcessOccurances(const std::string& Data, const std::vector<int>& Occurances)
{
	std::vector<std::pair<int, int>> Output;

	for (const auto& Num : Occurances)
	{
		std::string TempStr;
		TempStr.push_back(Data[Num + 4]);
		std::string TempStr2;
		int Ints = 0;
		if (!Is_Number(TempStr))
		{
			continue;
		}
		while (Is_Number(TempStr))
		{
			Ints++;
			TempStr.push_back(Data[Num + 4 + Ints]);
		}
		if (Data[Num + 4 + Ints] == ',')
		{
			Ints++;
			TempStr2.push_back(Data[Num + 4 + Ints]);
			if (!Is_Number(TempStr2))
			{
				continue;
			}
			while (Is_Number(TempStr2))
			{
				Ints++;
				TempStr2.push_back(Data[Num + 4 + Ints]);
			}
			if (Data[Num + 4 + Ints] == ')')
			{
				std::cout << "numsec" << TempStr2 << std::endl;
				Output.emplace_back(stoi(TempStr), stoi(TempStr2));
			}

		}
		else
		{
			continue;
		}
		std::cout << "num" << TempStr << std::endl;
		std::cout << "sepa " << Data[Num + 4 + Ints] << std::endl;
	}
	return Output;
}

/// advent of code #3
int main0111()
{
	std::string Text = ReadFileConvertToString("star3data.txt");
	std::vector<int> Occurances = FindOccurances(Text, "mul(");
	for (const auto& Num : Occurances)
	{
		std::cout << Num << ",";
	}
	std::vector<std::pair<int, int>> ProcessedData = ProcessOccurances(Text, Occurances);
	std::cout << "------------------";
	std::cout << std::endl;
	for (const auto& Num : ProcessedData)
	{
		std::cout << std::get<0>(Num) << ",";
		std::cout << std::get<1>(Num);
		std::cout << std::endl;
	}


	// Using std::accumulate with a lambda function
	int result = std::accumulate(ProcessedData.begin(), ProcessedData.end(), 0,
		[](int sum, const std::pair<int, int>& p) {
			return sum + (p.first * p.second); // Multiply each tuple and accumulate
		});

	std::cout << "Result: " << result << std::endl; // Output: 138
	std::cout << "------------------" << std::endl;



	std::vector<int> DontOccurances = FindOccurances(Text, "don't()");
	std::vector<int> DoOccurances = FindOccurances(Text, "do()");
	std::vector<std::pair<int, int>> AcceptableRange;
	AcceptableRange.emplace_back(0, DontOccurances[0] + 1);
	for (const auto& Num : DontOccurances)
	{
		std::cout << (Num) << ",";
	}
	std::cout << std::endl;
	for (const auto& Num : DoOccurances)
	{
		std::cout << (Num) << ",";
	}
	std::cout << "------------------" << std::endl;
	for (const auto& Num : DoOccurances)
	{
		std::cout << (Num) << ",";
		if (Num < AcceptableRange[0].second) continue;
		bool HasMatch = false;
		for (const auto& Num2 : DontOccurances)
		{
			if (Num2 > Num)
			{
				bool Break = false;
				for (const auto& Range : AcceptableRange)
				{
					if (Range.second == Num2)
					{
						Break = true;
						break;
					}
				}
				if (!Break)
				{
					HasMatch = true;
					AcceptableRange.emplace_back(Num + 1, Num2 + 1);
				}
				break;
			}
		}
		if (HasMatch) continue;
		AcceptableRange.emplace_back(Num + 1, Text.size());

	}
	std::cout << std::endl;
	std::cout << "------------------" << std::endl;
	for (const auto& pair : AcceptableRange)
	{
		std::cout << pair.first << "," << pair.second << std::endl;
	}
	std::vector<int> SecondPartOccurances = FindOccurances(Text, "mul(");
	std::vector<int> FinalOccurances;

	for (const auto& Num : SecondPartOccurances)
	{
		for (const auto& pair : AcceptableRange)
		{
			if (Num > pair.first && Num < pair.second)
			{
				FinalOccurances.push_back(Num);
				std::cout << " + " << pair.first << ", " << Num << " ," << pair.second << std::endl;
				break;
			}
		}
	}
	std::cout << SecondPartOccurances.size() << ".," << FinalOccurances.size();

	std::vector<std::pair<int, int>> Part2ProcessedData = ProcessOccurances(Text, FinalOccurances);
	std::cout << "------------------";
	std::cout << std::endl;


	// Using std::accumulate with a lambda function
	int part2result = std::accumulate(Part2ProcessedData.begin(), Part2ProcessedData.end(), 0,
		[](int sum, const std::pair<int, int>& p) {
			return sum + (p.first * p.second); // Multiply each tuple and accumulate
		});

	std::cout << "Result: " << part2result << std::endl; // Output: 138
	std::cout << "------------------" << std::endl;

	return 0;
}















/// advent of code #4
struct XData
{
	int Line=0;
	int Index=0;
	bool CanGrowRight=false;
	bool CanGrowUp=false;
	bool CanGrowLeft=false;
	bool CanGrowDown=false;
};


int ProcessXmasOccurances(const std::vector<string>& InLines, const std::vector<XData>& InputXData, const string& SearchCase)
{
	int XMasOccurances = 0;
	string Remaining = SearchCase;

	for (const auto& CurrentXData : InputXData)
	{
		if (CurrentXData.CanGrowRight)
		{
			bool FoundCase = true;
			for (int i = 0; i < 3; i++)
			{
				//std::cout << Remaining[i] << "," << InLines[CurrentXData.Line][CurrentXData.Index + i ] << std::endl;
				//std::cout << Remaining[i] << ","; 
				//std::cout << InLines[CurrentXData.Line][CurrentXData.Index + i + 1] << ",";

				if (InLines[CurrentXData.Line][CurrentXData.Index + i + 1] != Remaining[i])
				{
					FoundCase = false;
					break;
				}
			}
			if (FoundCase)
			{
				XMasOccurances++;
			}
		}
		if (CurrentXData.CanGrowLeft)
		{
			bool FoundCase = true;
			for (int i = 0; i < 3; i++)
			{
				//std::cout << Remaining[i] << "," << InLines[CurrentXData.Line][CurrentXData.Index + i ] << std::endl;
				//std::cout << Remaining[i] << ","; 
				//std::cout << InLines[CurrentXData.Line][CurrentXData.Index + i + 1] << ",";
				if (InLines[CurrentXData.Line][CurrentXData.Index - i - 1] != Remaining[i])
				{
					FoundCase = false;
					break;
				}
			}
			if (FoundCase)
			{
				XMasOccurances++;
			}
		}
		if (CurrentXData.CanGrowUp)
		{
			bool FoundCase = true;
			for (int i = 0; i < 3; i++)
			{
				//std::cout << Remaining[i] << "," << InLines[CurrentXData.Line][CurrentXData.Index + i ] << std::endl;
				//std::cout << Remaining[i] << ","; 
				//std::cout << InLines[CurrentXData.Line][CurrentXData.Index + i + 1] << ",";
				if (InLines[CurrentXData.Line - i - 1][CurrentXData.Index] != Remaining[i])
				{
					FoundCase = false;
					break;
				}
			}
			if (FoundCase)
			{
				XMasOccurances++;
			}
		}
		if (CurrentXData.CanGrowDown)
		{
			bool FoundCase = true;
			for (int i = 0; i < 3; i++)
			{
				//std::cout << Remaining[i] << "," << InLines[CurrentXData.Line][CurrentXData.Index + i ] << std::endl;
				//std::cout << Remaining[i] << ","; 
				//std::cout << InLines[CurrentXData.Line][CurrentXData.Index + i + 1] << ",";
				if (InLines[CurrentXData.Line + i + 1][CurrentXData.Index] != Remaining[i])
				{
					FoundCase = false;
					break;
				}
			}
			if (FoundCase)
			{
				XMasOccurances++;
			}
		}
		if (CurrentXData.CanGrowRight && CurrentXData.CanGrowUp)
		{
			bool FoundCase = true;
			for (int i = 0; i < 3; i++)
			{
				//std::cout << Remaining[i] << "," << InLines[CurrentXData.Line][CurrentXData.Index + i ] << std::endl;
				//std::cout << Remaining[i] << ","; 
				//std::cout << InLines[CurrentXData.Line][CurrentXData.Index + i + 1] << ",";
				if (InLines[CurrentXData.Line - i - 1][CurrentXData.Index + i + 1] != Remaining[i])
				{
					FoundCase = false;
					break;
				}
			}
			if (FoundCase)
			{
				XMasOccurances++;
			}
		}
		if (CurrentXData.CanGrowRight && CurrentXData.CanGrowDown)
		{
			bool FoundCase = true;
			for (int i = 0; i < 3; i++)
			{
				//std::cout << Remaining[i] << "," << InLines[CurrentXData.Line][CurrentXData.Index + i ] << std::endl;
				//std::cout << Remaining[i] << ","; 
				//std::cout << InLines[CurrentXData.Line][CurrentXData.Index + i + 1] << ",";
				if (InLines[CurrentXData.Line + i + 1][CurrentXData.Index + i + 1] != Remaining[i])
				{
					FoundCase = false;
					break;
				}
			}
			if (FoundCase)
			{
				XMasOccurances++;
			}
		}
		if (CurrentXData.CanGrowLeft && CurrentXData.CanGrowUp)
		{
			bool FoundCase = true;
			for (int i = 0; i < 3; i++)
			{
				//std::cout << Remaining[i] << "," << InLines[CurrentXData.Line][CurrentXData.Index + i ] << std::endl;
				//std::cout << Remaining[i] << ","; 
				//std::cout << InLines[CurrentXData.Line][CurrentXData.Index + i + 1] << ",";
				if (InLines[CurrentXData.Line - i - 1][CurrentXData.Index - i - 1] != Remaining[i])
				{
					FoundCase = false;
					break;
				}
			}
			if (FoundCase)
			{
				XMasOccurances++;
			}
		}
		if (CurrentXData.CanGrowLeft && CurrentXData.CanGrowDown)
		{
			bool FoundCase = true;
			for (int i = 0; i < 3; i++)
			{
				//std::cout << Remaining[i] << "," << InLines[CurrentXData.Line][CurrentXData.Index + i ] << std::endl;
				//std::cout << Remaining[i] << ","; 
				//std::cout << InLines[CurrentXData.Line][CurrentXData.Index + i + 1] << ",";
				if (InLines[CurrentXData.Line + i + 1][CurrentXData.Index - i - 1] != Remaining[i])
				{
					FoundCase = false;
					break;
				}
			}
			if (FoundCase)
			{
				XMasOccurances++;
			}
		}
	}

	return XMasOccurances;
}


int ProcessXXmasOccurances(const std::vector<string>& InLines, const std::vector<XData>& InputXData)
{
	int XMasOccurances = 0;
	for (const auto& CurrentXData : InputXData)
	{
		if (!CurrentXData.CanGrowDown || !CurrentXData.CanGrowLeft || !CurrentXData.CanGrowRight || !CurrentXData.CanGrowUp)
		{
			continue;
		}
		bool FoundCase = true;
		std::vector<char> Chars = { 'M','S' };
		std::vector<char> FirstSetChars;
		std::vector<char> SecondSetChars;
		for (int i = -1; i < 2; i++)
		{
			if (i == 0 )continue;
			for (int j = -1; j < 2; j++)
			{
				if (j == 0)continue;
				if (i+j != 0)
				{
					FirstSetChars.push_back(InLines[CurrentXData.Line +i][CurrentXData.Index + j]);
				}
				else
				{
					SecondSetChars.push_back(InLines[CurrentXData.Line + i][CurrentXData.Index + j]);
				}
			}
		}
		if (FirstSetChars[1] == Chars[0] || FirstSetChars[0] == Chars[0])
		{
			Chars.erase(Chars.begin());
		}
		if (FirstSetChars[1] == Chars[0] || FirstSetChars[0] == Chars[0])
		{
			Chars.erase(Chars.begin());
		}
		if (Chars.size() > 0)
		{
			continue;
		}
		Chars = { 'M','S' };
		if (SecondSetChars[1] == Chars[0] || SecondSetChars[0] == Chars[0])
		{
			Chars.erase(Chars.begin());
		}
		if (SecondSetChars[1] == Chars[0] || SecondSetChars[0] == Chars[0])
		{
			Chars.erase(Chars.begin());
		}
		if (Chars.size() > 0)
		{
			continue;
		}
		XMasOccurances++;
	}
	return XMasOccurances;
}

int main()
{
	ifstream File("star4data.txt");
	string FullFileText = ReadFileConvertToString("star4data.txt");
	// String to store each line of the file.
	string Line;
	int LineCount=0;
	int LineLength = 0;
	std::vector<string> Lines;
	if (File.is_open()) {
		// Read each line from the file and store it in the
		// 'line' variable.
		
		while (getline(File, Line)) {
			LineCount++;
			Lines.push_back(Line);
			if(LineLength ==0)
			{ 
				LineLength = Line.length();
			}
		}
		// Close the file stream once all lines have been
		// read.
		File.close();
	}
	std::cout << LineCount << "," << LineLength << std::endl;

	for (const auto& Line :Lines)
	{
		std::vector<int> Occurances = FindOccurances(Line, "X");
		for (const auto& Occur : Occurances)
		{
			std::cout << Occur << ",";

		}
	}
	std::vector<XData> XDatas;
	for (size_t i = 0; i < Lines.size(); i++)
	{
		std::vector<int> Occurances = FindOccurances(Lines[i], "X");
		std::cout << std::endl;
		for (const auto& LineOccur : Occurances)
		{
			std::cout << "Line: " << i << ",Index= " << LineOccur << "||";
			XData Data;
			Data.Line = i;
			Data.Index = LineOccur;
			if (i > 2)
			{
				Data.CanGrowUp = true;
			}
			if (i < LineLength - 3)
			{
				Data.CanGrowDown = true;
			}
			if (LineOccur > 2)
			{
				Data.CanGrowLeft = true;
			}
			if (LineOccur < LineLength - 3)
			{
				Data.CanGrowRight = true;
			}
			XDatas.push_back(Data);
		}
	}

	int FinalAnswer = ProcessXmasOccurances(Lines, XDatas,"MAS");

	std::vector<XData> SecondXDatas;
	for (size_t i = 0; i < Lines.size(); i++)
	{
		std::vector<int> Occurances = FindOccurances(Lines[i], "A");
		std::cout << std::endl;
		for (const auto& LineOccur : Occurances)
		{
			std::cout << "Line: " << i << ",Index= " << LineOccur << "||";
			XData Data;
			Data.Line = i;
			Data.Index = LineOccur;
			if (i > 0)
			{
				Data.CanGrowUp = true;
			}
			if (i < LineLength - 1)
			{
				Data.CanGrowDown = true;
			}
			if (LineOccur > 0)
			{
				Data.CanGrowLeft = true;
			}
			if (LineOccur < LineLength - 1)
			{
				Data.CanGrowRight = true;
			}
			SecondXDatas.push_back(Data);
		}
	}
	int SecFinalAnswer = ProcessXXmasOccurances(Lines, SecondXDatas);

	std::cout << std::endl << "sec Final Answer : " << SecFinalAnswer;
	return 0;
}