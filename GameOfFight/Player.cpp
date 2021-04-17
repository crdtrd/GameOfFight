#include "Player.h"

Player::Player()
{
	titleDmgMod = 0; titleDefMod = 0; powerLevel = 0; currentTopDmg = 0; currentTopDef = 0;
	victories = 0; defeats = 0; health = 0; maxHealth = 0; damage = 0; defense = 0; wallet = 0;
	name = ""; title = ""; 
}

Player::Player(int titleDmgMod, int titleDefMod, int powerLevel, int currentTopDmg, int currentTopDef, 
	int victories, int defeats, int health, int maxHealth, int damage, int defense, int wallet,
	string name, string title)
	: Character(health, maxHealth, damage, defense, wallet, name, title)
{
	this->titleDmgMod = titleDmgMod; this->titleDefMod = titleDefMod; this->powerLevel = powerLevel;
	this->currentTopDmg = currentTopDmg; this->currentTopDef = currentTopDef; this->victories = victories;
	this->defeats = defeats;
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
	damage = (round(equippedWeapon.getDamage() + (equippedWeapon.getDamage() / double(titleDmgMod))));
}

void Player::updateDefense()
{
	defense = (round(equippedArmor.getDefense() + (equippedArmor.getDefense() / double(titleDefMod))));
}

void Player::updatePowerLevel()
{
	powerLevel = currentTopDmg + currentTopDef + victories + defeats;
}

int Player::getPowerLevel() const
{
	return powerLevel;
}

void Player::updateCurrentTopDmg()
{
	if (damage > currentTopDmg) 
	{
		currentTopDmg = damage;
	}
}

void Player::updateCurrentTopDef()
{
	if (defense > currentTopDef)
	{
		currentTopDef = defense;
	}
}

int Player::getCurrentTopDmg() const
{
	return currentTopDmg;
}

int Player::getCurrentTopDef() const
{
	return currentTopDef;
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

int Player::getVictories() const
{
	return victories;
}

int Player::getDefeats() const
{
	return defeats;
}

void Player::addVictory()
{
	victories++;
}

void Player::addDefeat()
{
	defeats++;
}

// deep copy via operator =
const Player& Player::operator=(const Player& p)
{
	titleDmgMod = p.titleDmgMod; 
	titleDefMod = p.titleDefMod; 
	powerLevel = p.powerLevel;
	currentTopDmg = p.currentTopDmg;
	currentTopDef = p.currentTopDef;
	victories = p.victories;
	defeats = p.defeats;
	health = p.health;
	maxHealth = p.maxHealth;
	damage = p.damage;
	defense = p.defense;
	wallet = p.wallet;
	name = p.name;
	title = p.title;
	items = p.items;
	equippedWeapon = p.equippedWeapon; 
	equippedArmor = p.equippedArmor;
	return *this;
}