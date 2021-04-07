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
	int currentTopDamage;
	int currentTopDefense;
	int victories;
	int defeats;
	int damageDealt;
	int damageRecieved;

public:
	Player();
	Player(string name, string title);

	void updateDamage();
	void updateDefense();

	void updatePowerLevel();
	int getPowerLevel() const;

	int getWallet() const;
	void payMoney(int money);
	void recieveMoney(int money);

	void selectItem(int itemIndex) const;
	Item* sellItem(int itemIndex);

};

#endif // !PLAYER_H
