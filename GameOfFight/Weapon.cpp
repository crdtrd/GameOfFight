// Christian Deardorff: This my own work.
#include "Weapon.h"

Weapon::Weapon()
{
	name = "Fist";
	worth = 0;
	damage = 10;
}

Weapon::Weapon(string name, int worth, int damage)
	: Item(name, worth)
{
	this->damage = damage;
}

void Weapon::setDamage(int damage)
{
	this->damage = damage;
}

int Weapon::getDamage() const
{
	return damage;
}

string Weapon::toString() const
{
	string s = name + "\nDamage: " + to_string(damage) + "\nWorth: " + to_string(worth) + "\n";
	return s;
}

const Weapon& Weapon::operator=(const Weapon& w)
{
	name = w.name;
	worth = w.worth;
	damage = w.damage;
	return *this;
}