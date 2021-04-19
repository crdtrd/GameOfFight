// Christian Deardorff: This my own work.
#include "Armor.h"

Armor::Armor()
{
	defense = 0;
}

Armor::Armor(string name, int worth, int defense)
	:Item(name, worth)
{
	this->defense = defense;
}

void Armor::setDefense(int defense)
{
	this->defense = defense;
}

int Armor::getDefense() const
{
	return defense;
}

string Armor::toString() const
{
	string s = name + "\nDefense: " + to_string(defense) + "\nWorth: " + to_string(worth) + "\n";
	return s;
}


const Armor& Armor::operator=(const Armor& a)
{
	name = a.name;
	worth = a.worth;
	defense = a.defense;
	return *this;
}