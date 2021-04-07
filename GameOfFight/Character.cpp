#include "Character.h"

Character::Character()
{
	name = ""; title = ""; health = 0;
	maxHealth = 0; damage = 0; defense = 0; wallet = 0;
	// still need to initialize items, should contain fist and shirt
}

Character::Character(string name, string title)
{
	this->name = name; this->title = title;
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

void Character::equipWeapon(int itemIndex)
{

}

void Character::equipArmor(int itemIndex)
{
	
}

void Character::addItem(Item*)
{

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
