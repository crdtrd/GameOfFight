#include "Player.h"

Player::Player()
{

}

Player::Player(string name, string title)
	:Character(name, title)
{

}

void Player::updateDamage()
{
	this->damage = equippedWeapon.
}

void Player::updateDefense()
{

}

void Player::updatePowerLevel()
{

}

int Player::getPowerLevel() const
{
	return powerLevel;
}

int Player::getWallet() const
{
	return wallet;
}

void Player::payMoney(int money)
{
	
}

void Player::recieveMoney(int money)
{
	wallet += money;
}

void Player::selectItem(int itemIndex) const
{

}

Item* Player::sellItem(int itemIndex)
{
	return nullptr;
}