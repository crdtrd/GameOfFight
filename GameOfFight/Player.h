#pragma once

#include "Character.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character
{
private:
	int titleDmgMod; // damage modifier from player character title
	int titleDefMod; // defense modifier from player character title
	
	// Historic variables for stats that are built up between saves.
	// When there is a save, these are added to stored values and then reset.
	int victories;
	int defeats;
	int damageDealt;
	int damageRecieved;

public:
	Player();
	Player(string name, string title);

	void updateDamage();
	void updateDefense();

	int getWallet() const;
	void payMoney(int money);
	void recieveMoney(int money);

	void selectItem(int itemIndex) const;
	Item* sellItem(int itemIndex);

};

#endif // !PLAYER_H
