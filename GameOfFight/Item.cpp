#include "Item.h"

Item::Item()
{
	name = ""; description = ""; worth = 0;
}

Item::Item(string name, string description, int worth)
{
	this->name = name; this->description = description; this->worth = worth;
}

void Item::setName(string name)
{
	this->name = name;
}

string Item::getName() const
{
	return name;
}

void Item::setDescription(string description)
{
	this->description = description;
}

string Item::getDescription() const
{
	return description;
}

void Item::setWorth(int worth)
{
	this->worth = worth;
}

int Item::getWorth() const
{
	return worth;
}