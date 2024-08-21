#include "NameStorage.h"



std::vector<std::string> NameStorage::FirstNames = {
    "Alice", "Bob", "Charlie", "David", "Emily", "Rez", "Darth", "JJ", "OG", "Purple",
    "Clementine", "Ezekiel", "Imogen", "Amaya", "Élodie", "Odette", "Kailani", "Evander", "Magnolia", "Andromeda",
    "Soren", "Hugo", "Julian", "Rhett", "Cedric", "Bastien", "Caspian", "Linus", "Ziggy", "Torin",
    "Gray", "Finnian", "Lazer", "Huck", "Kofi", "Barnaby", "Rivers", "Grover", "Josias", "Kit"
};

std::vector<std::string> NameStorage::LastNames = {
    "Smith", "Johnson", "Williams", "Brown", "Jones", "Jameson", "Rey", "Diesel", "Fury", "Skull",
    "Hawke", "Blaze", "Knight", "Storm", "Wolf", "Stone", "Phoenix", "Ryder", "Hunter", "Fox",
    "Wilde", "Black", "Silver", "Frost", "Steel", "Thorne", "Voss", "Drake", "Griffin", "Hale",
    "Knightley", "Lennox", "Maverick", "Quinn", "Raven", "Sable", "Talon", "Vega", "Wren", "Zephyr"
};


std::string NameStorage::RandomName()
{

    std::random_device os_seed;
    const u32 seed = os_seed();

    engine generator(seed);
    std::uniform_int_distribution< u32 > distribute(0, 9999);
	int FirstNameIndex = distribute(generator) % FirstNames.size();
	int LastNameIndex = distribute(generator) % LastNames.size();

	return FirstNames[FirstNameIndex] + " " + LastNames[LastNameIndex];


}
