// Christian Deardorff: This my own work.
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
	Weapon(string name, int worth, int damage);

	void setDamage(int damage);
	int getDamage() const;

	string toString() const;

	const Weapon& operator=(const Weapon& w);

};
#endif // !WEAPON_H
