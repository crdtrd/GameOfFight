// Christian Deardorff: This my own work.
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
	damage = static_cast<Weapon*>(equippedWeapon)->getDamage();
}

void Enemy::updateDefense()
{
	defense = static_cast<Armor*>(equippedArmor)->getDefense();
}
