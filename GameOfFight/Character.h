#pragma once

#include "Item.h"
#include <vector>

#ifndef CHARACTER_H
#define CHARACTER_H

class Character 
{
protected:
	string name;
	string title; // Player: fighter, assassin, tank. Enemy: anything I want
	int health;
	int maxHealth;
	int damage;
	int defense;
	vector<Item*> items;
	Item* equippedWeapon;
	Item* equippedArmor;
	int wallet;

public:
	Character();
	Character(string name, string title);

	void setName(string name);
	string getName() const;

	void setTitle(string title);
	string getTitle() const;

	void setHealth(int health);
	void heal(int healAmount);
	int getHealth() const;

	void setMaxHealth(int maxHealth);
	int getMaxHealth() const;

	void equipWeapon(int itemIndex);
	void equipArmor(int itemIndex);

	void addItem(Item*);

	int getDamage() const;
	int getDefense() const;
	void takeDamage();

	virtual void updateDamage() = 0;
	virtual void updateDefense() = 0;
	virtual void payMoney() = 0;

};
#endif // !CHARACTER_H

