#pragma once

#include "Item.h" // Item includes string and namespace std

#ifndef WEAPON_H
#define WEAPON_H

class Weapon : public Item
{
private:
	int damage;

public:
	Weapon();
	Weapon(string name, string description, int worth, int damage);

	void setDamage(int damage);
	int getDamage() const;

};
#endif // !WEAPON_H
