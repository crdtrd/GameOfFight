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

void Player::updateStats()
{
	updateDamage(); updateDefense(); 
	updateCurrentTopDef(); updateCurrentTopDmg(); 
	updatePowerLevel();
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
	damage = (static_cast<Weapon*>(equippedWeapon)->getDamage() + (round(static_cast<Weapon*>(equippedWeapon)->getDamage() / titleDmgMod)));
}

void Player::updateDefense()
{
	defense = (static_cast<Armor*>(equippedArmor)->getDefense() + (round(static_cast<Armor*>(equippedArmor)->getDefense() / titleDefMod)));
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

void Player::payMoney(int money) // need to adjust to prevent silliness
{
	wallet -= money;
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

void Character::setWallet(int money)
{

}

int Character::getWallet() const
{
	return wallet;
}

string Player::toString()
{
	string s = name
		+ "\nPower Level: " + to_string(powerLevel)
		+ "\nClass: " + title
		+ "\nWallet: $" + to_string(wallet)
		+ "\nHP: " + to_string(health)
		+ equippedWeapon->getName() + ": " + to_string(static_cast<Weapon*>(equippedWeapon)->getDamage()) + " damage\n"
		+ equippedArmor->getName() + ": " + to_string(static_cast<Armor*>(equippedArmor)->getDefense()) + " defense\n"
		+ "\nMax HP: " + to_string(maxHealth)
		+ "\nVictories: " + to_string(victories)
		+ "\nDefeats: " + to_string(defeats) + "\n";
	return s;
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
	for (int i = 0; i < items.size(); i++) // clean it up proper
	{
		delete items[i];
	}
	items.clear();
	items = p.items;
	delete equippedWeapon;
	equippedWeapon = p.equippedWeapon; 
	delete equippedArmor;
	equippedArmor = p.equippedArmor;
	return *this;
}