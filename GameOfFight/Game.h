#pragma once

#include <iostream>
#include <fstream>

#include "Weapon.h"
#include "Armor.h"
#include "Shop.h"
#include "Enemy.h"
#include "Player.h"

class Game
{
private:
	// data members
	Player player;

	// data and file functions
	
	// menu functions. they should be able to do their thing, but
	// must return to the function called by them to avoid recursion. 
	// input handling must be with a while loop, or a try catch, or some combination of those.
	void playerSelect(); 
	void playerSelectConfirmation();

	void playerCreationName();
	void playerCreationClass();
	void playerCreationConfirmation();

	// fight, items, shop. stats, saves, character select, quit game
	void decisionMenu();
	void decisionQuitGame();
	void decisionCharacterSelect();
	void decisionSaves();
	void decisionStats();
	void decisionShop();
	void decisionItems();
	void decisionFight();

	// save menu functions
	// i may create a save class to handle the detailed save and load implementation.
	void newSave(); // the new save sequence. appears a few times in different menus.
	void loadSave(); // likely will just replace the data loaded and return to decision menu.

	// enemy creation
	
	// some other functions
	void clearScreen();

public:
	Game();
	void play();
};