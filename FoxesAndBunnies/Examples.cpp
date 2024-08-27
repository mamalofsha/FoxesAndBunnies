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

int main_examples()
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