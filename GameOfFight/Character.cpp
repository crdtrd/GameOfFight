#include "Character.h"

Character::Character()
{
	name = ""; title = ""; health = 0;
	maxHealth = 0; damage = 0; defense = 0; wallet = 0;
}

Character::Character(int health, int maxHealth, int damage, int defense, int wallet,
	string name, string title)
{
	this->health = health; this->maxHealth = maxHealth; this->damage = damage;
	this->defense = defense; this->wallet = wallet; this->name = name; this->title = title;
}

void Character::setName(string name)
{
	this->name = name;
}

string Character::getName() const
{
	return name;
}

void Character::setTitle(string title)
{
	this->title = title;
}

string Character::getTitle() const
{
	return title;
}

void Character::setHealth(int health)
{
	this->health = health;
}

void Character::heal(int healAmount)
{

}

int Character::getHealth() const
{
	return health;
}

void Character::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

int Character::getMaxHealth() const
{
	return maxHealth;
}

void Character::equipWeapon(Weapon w)
{
	equippedWeapon = w;
}

void Character::equipArmor(Armor a)
{
	equippedArmor = a;
}

Weapon Character::getEquippedWeapon() const
{
	return equippedWeapon;
}

Armor Character::getEquippedArmor() const
{
	return equippedArmor;
}

void Character::addItem(Item i)
{
	items.push_back(i);
}

vector<Item> Character::getItems() const // keep an eye on this
{
	return items;
}

int Character::getDamage() const
{
	return damage;
}

int Character::getDefense() const
{
	return defense;
}

void Character::takeDamage()
{

}