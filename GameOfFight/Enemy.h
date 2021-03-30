#pragma once

#include "Character.h"
#include "Player.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Character
{
public:
	Enemy();
	Enemy(string name, string title);
	
	void updateDamage();
	void updateDefense();

	void updateWallet(); // enemy money determined by powerlevel
	void payMoney(Player& p); // pay all money to player

};
#endif // !ENEMY_H
