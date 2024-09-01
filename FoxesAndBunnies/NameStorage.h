#pragma once
#include <string>
#include <vector>
#include <cstdlib> 
#include <random>

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