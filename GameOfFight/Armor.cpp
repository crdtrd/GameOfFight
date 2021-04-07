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