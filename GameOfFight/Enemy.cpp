#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(int health, int maxHealth, int damage, int defense, int wallet,
	string name, string title)
	:Character(health, maxHealth, damage, defense, wallet,
		name, title)
{

}

void Enemy::updateDamage()
{

}

void Enemy::updateDefense()
{

}

void Enemy::updateWallet()
{

}

void Enemy::payMoney(Player& p)
{

}