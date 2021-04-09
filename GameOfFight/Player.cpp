#include "Player.h"

Player::Player()
{

}

Player::Player(string name, string title)
	:Character(name, title)
{

}

void Player::setTitleDmgMod(int mod) 
{
	titleDmgMod = mod;
}

int Player::getTitleDmgMod() const
{
	return titleDmgMod;
}

void Player::setTitleDefMod(int mod)
{
	titleDefMod = mod;
}

int Player::getTitleDefMod() const
{
	return titleDefMod;
}

void Player::updateDamage()
{
	damage = (round(equippedWeapon->getDamage() + (equippedWeapon->getDamage() / double(titleDmgMod))));
}

void Player::updateDefense()
{
	defense = (round(equippedArmor->getDefense() + (equippedArmor->getDefense() / double(titleDefMod))));
}

void Player::updatePowerLevel()
{
	powerLevel = currentTopDamage + currentTopDefense + victories + defeats;
}

int Player::getPowerLevel() const
{
	return powerLevel;
}

void Player::updateCurrentTopDamage()
{
	if (damage > currentTopDamage) 
	{
		currentTopDamage = damage;
	}
}

void Player::updateCurrentTopDefense()
{
	if (defense > currentTopDefense)
	{
		currentTopDefense = defense;
	}
}

int Player::getWallet() const
{
	return wallet;
}

void Player::payMoney(int money)
{
	return;
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