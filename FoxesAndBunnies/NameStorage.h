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

};

