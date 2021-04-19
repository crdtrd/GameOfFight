#pragma once

#include "Character.h"
#include "Player.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Character
{
public:
	Enemy();
	Enemy(int health, int maxHealth, int damage, int defense, int wallet,
		string name, string title);
	
	void updateDamage();
	void updateDefense();

};
#endif // !ENEMY_H
