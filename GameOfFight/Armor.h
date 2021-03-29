#pragma once

#include "Item.h" // Item includes string and namespace std

#ifndef ARMOR_H
#define ARMOR_H

class Armor : public Item
{
private:
	int defense;

public:
	Armor();
	Armor(string name, string description, int worth, int defense);

	void setDefense(int defense);
	int getDefense() const;

};
#endif // !ARMOR_H
