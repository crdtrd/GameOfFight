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