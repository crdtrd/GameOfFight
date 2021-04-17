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
	Armor(string name, int worth, int defense);

	void setDefense(int defense);
	int getDefense() const;

	string toString() const;

	const Armor& operator=(const Armor& a);

};
#endif // !ARMOR_H
