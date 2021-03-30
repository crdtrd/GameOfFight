#include "Armor.h"

Armor::Armor()
{
	defense = 0;
}

Armor::Armor(string name, string description, int worth, int defense)
	:Item(name, description, worth)
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