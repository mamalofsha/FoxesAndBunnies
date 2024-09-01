#include "NameStorage.h"
#include "Tools.h"

std::vector<std::string> NameStorage::MaleFirstNames = {
    "Alice", "Bob", "Charlie", "David", "Emily", "Rez", "Darth", "JJ", "OG", "Purple",
    "Clementine", "Ezekiel", "Imogen", "Amaya", "Élodie", "Odette", "Kailani", "Evander", "Magnolia", "Andromeda",
    "Soren", "Hugo", "Julian", "Rhett", "Cedric", "Bastien", "Caspian", "Linus", "Ziggy", "Torin",
    "Gray", "Finnian", "Lazer", "Huck", "Kofi", "Barnaby", "Rivers", "Grover", "Josias", "Kit"
};
std::vector<std::string> NameStorage::FemaleFirstNames = {
    "Ottilie", "Imogen", "Beatrix", "Isolde", "Birdie", "Odette", "Ida", "Marigold", "Keziah", "Lavinia",
    "Ines", "Lavender", "Aoife", "Seraphina", "Elowen", "Tallulah", "Clio", "Harriet", "Arwen", "Fleur",
    "Lilac", "Posey", "Snow", "Blue", "Banks", "Eleven", "Venus", "Winslet", "Deren", "Nerea",
    "Sonali", "Darcy", "Juni", "Veronique", "Ariel", "Violet", "Lena", "Emaline", "Brielle", "Vera",
    "Adelaide", "Mirabel", "Danica", "Myla", "Trista", "Ruby", "Yuka", "Jobelle", "Ausha", "Vienna"
};
std::vector<std::string> NameStorage::LastNames = {
    "Smith", "Johnson", "Williams", "Brown", "Jones", "Jameson", "Rey", "Diesel", "Fury", "Skull",
    "Hawke", "Blaze", "Knight", "Storm", "Wolf", "Stone", "Phoenix", "Ryder", "Hunter", "Fox",
    "Wilde", "Black", "Silver", "Frost", "Steel", "Thorne", "Voss", "Drake", "Griffin", "Hale",
    "Knightley", "Lennox", "Maverick", "Quinn", "Raven", "Sable", "Talon", "Vega", "Wren", "Zephyr"
};

std::string NameStorage::RandomFullName(bool IsMale)
{
    int RandomNumber = Tools::RandomInRange(9999);
	int FirstNameIndex = RandomNumber % (IsMale ?  MaleFirstNames.size() : FemaleFirstNames.size());
	int LastNameIndex = RandomNumber % LastNames.size();
	return  (IsMale ? MaleFirstNames[FirstNameIndex] : FemaleFirstNames[FirstNameIndex]) + " " + LastNames[LastNameIndex];
}

std::string NameStorage::RandomFirstName(bool IsMale)
{
    int RandomNumber = Tools::RandomInRange(9999);
    int FirstNameIndex = RandomNumber % (IsMale ? MaleFirstNames.size() : FemaleFirstNames.size());
    return   IsMale ? MaleFirstNames[FirstNameIndex] : FemaleFirstNames[FirstNameIndex];
}

std::string NameStorage::RandomLastName()
{
    int RandomNumber = Tools::RandomInRange(9999);
    int LastNameIndex = RandomNumber % LastNames.size();
    return   LastNames[LastNameIndex];
}