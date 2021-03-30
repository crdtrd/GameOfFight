#include "Weapon.h"

Weapon::Weapon()
{
	damage = 0;
}

Weapon::Weapon(string name, string description, int worth, int damage)
	: Item(name, description, worth)
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