// Christian Deardorff: This my own work.
#pragma once

#include "Weapon.h"
#include "Armor.h"
#include <vector>
#include <stdexcept>

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
	Item* equippedWeapon; // item pointer to weapon object
	Item* equippedArmor; // item pointer to armor object
	int wallet;

public:
	Character();
	Character(int health, int maxHealth, int damage, int defense, int wallet,
		string name, string title);

	void setName(string name);
	string getName() const;

	void setTitle(string title);
	string getTitle() const;

	void setHealth(int health);
	void heal(int healAmount);
	int getHealth() const;

	void setMaxHealth(int maxHealth);
	int getMaxHealth() const;

	void equipWeapon(Item* w);
	void equipArmor(Item* w);
	Item* getEquippedWeapon() const;
	Item* getEquippedArmor() const;

	void addItem(Item* i);
	vector<Item*> getItems() const;
	void dropItem(int itemIndex);

	int getDamage() const;
	int getDefense() const;
	void takeDamage();

	void setWallet(int money);
	int getWallet() const;

	virtual void updateDamage() = 0;
	virtual void updateDefense() = 0;

	// attack operator
	int operator-(const Character& c);

};
#endif // !CHARACTER_H

