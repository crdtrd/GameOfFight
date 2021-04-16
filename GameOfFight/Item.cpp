#include "Item.h"

// CONSTRUCTORS
Item::Item()
{
	name = ""; worth = 0;
}

Item::Item(string name, int worth)
{
	this->name = name; this->worth = worth;
}

//DESTRUCTOR
Item::~Item()
{

}

void Item::setName(string name)
{
	this->name = name;
}

string Item::getName() const
{
	return name;
}

void Item::setWorth(int worth)
{
	this->worth = worth;
}

int Item::getWorth() const
{
	return worth;
}