#pragma once

#include "Weapon.h"
#include "Armor.h"
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
	Weapon* equippedWeapon;
	Armor* equippedArmor;
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

	void equipWeapon(Weapon* w);
	void equipArmor(Armor* a);
	Weapon* getEquippedWeapon();
	Armor* getEquippedArmor();

	void addItem(Item* i);
	vector<Item*> getItems() const;

	int getDamage() const;
	int getDefense() const;
	void takeDamage();

	virtual void updateDamage() = 0;
	virtual void updateDefense() = 0;

};
#endif // !CHARACTER_H

