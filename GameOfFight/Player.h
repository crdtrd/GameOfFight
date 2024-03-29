// Christian Deardorff: This my own work.
#pragma once

#include "Character.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character
{
private:
	int titleDmgMod; // damage modifier from player character title
	int titleDefMod; // defense modifier from player character title
	int powerLevel;
	int currentTopDmg;
	int currentTopDef;
	int victories;
	int defeats;

	/* extra stats im not worrying about right now
	int damageDealt;
	int damageRecieved;
	*/

public:
	Player();
	Player(int titleDmgMod, int titleDefMod, int powerLevel, int currentTopDmg, int currentTopDef,
		int victories, int defeats, int health, int maxHealth, int damage, int defense, int wallet,
		string name, string title);
	void updateStats();

	void setTitleDmgMod(int mod);
	int getTitleDmgMod() const;

	void setTitleDefMod(int mod);
	int getTitleDefMod() const;

	void updateDamage();
	void updateDefense();

	void updatePowerLevel();
	int getPowerLevel() const;

	void updateCurrentTopDmg();
	void updateCurrentTopDef();
	int getCurrentTopDmg() const;
	int getCurrentTopDef() const;

	void payMoney(int money);
	void recieveMoney(int money);

	void selectItem(int itemIndex) const;
	Item* sellItem(int itemIndex);

	int getVictories() const;
	int getDefeats() const;
	void addVictory();
	void addDefeat();

	string toString();

	const Player& operator=(const Player& p);
};

#endif // !PLAYER_H
