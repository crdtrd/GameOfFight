// Christian Deardorff: This my own work.
#pragma once
// this is for Sleep()
#ifdef _WIN32 
#include <Windows.h>
#else
#include <unistd.h>
#endif	

#include <iostream>
#include <fstream>
#include "nlohmann\json.hpp" // json library for my convenience
using json = nlohmann::json;
#include <filesystem> // directory access

namespace fs = std::filesystem;
#include <ctime> // to help keep track of saves


#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Enemy.h"
#include "Player.h"


class Game
{
private:
	// data members
	Player player;
	Enemy enemy;
	fstream playerDataFile; // for accessing files
	const fs::path playerDataFolderPath = "./player_data"; // path to player data folder 
	json selectedPlayerFile; //json data that has all selected player saves
	json selectedPlayerSave; // json data that has a specific save. used primarily for loading saves.
	bool quit; // controls whether we quittin or not and is actually a bit buggy atm
	vector<Item*> shop; // the shop. making it a member cuz its persistent.
	bool restockShop; // whether or not to restock. should be set to true after a fight
	// should have all menus returning booleans or somehting i need ta figure that

	// data and file functions
	
	// menu functions. they should be able to do their thing, but
	// must return to the function called by them to avoid recursion. 
	// input handling must be with a while loop, or a try catch, or some combination of those.
	void playerSelect() throw (invalid_argument);
	void playerSelectConfirmation();
	void playerCreationName();
	void playerCreationClass(string& newName);
	void playerCreationConfirmation(string& newName, string newTitle);

	// fight, items, shop. stats, saves, character select, quit game
	void decisionMenu();
	void decisionQuitGame();
	void decisionCharacterSelect();
	void decisionSaves();
	void decisionStats();
	void decisionShop();
	void decisionItems() throw (invalid_argument);
	void decisionFight();

	// decision sub-menus
	void buyItemFocusMenu(int itemIndex);
	void sellItemsMenu();
	void sellItemFocusMenu(int itemIndex);
	void equippedItemFocusMenu(Item* i);
	void itemFocusMenu(int itemIndex);
	void saveFocusMenu(char slot);
	void newSaveMenu();
	void overwriteMenu(char slot);
	void nameSaveMenu(char slot);

	// file functions
	void printSaves(int min, int max); // dependent on selectedPlayerFile. takes in save print range 65 = A, 90 = Z

	void newSave(char slot, string saveName); // the act of creating/overwriting a save

	void autoSave(); // autosaving

	void loadSave(); // load save data to player object. dependent on the selected playerSave

	json constructNewSaveJson(char slot, string saveName, string filePathName); // the act of loading player data into a json to be saved in a save slot
	json newPlayerFile(string& newName, string& newTitle); // used in creating a new player file
	json getMostRecentSave(json& playerInfo); // gets most recent save from a file

	// shop functions
	vector<Item*> stockShop();

	// FIGHT FUNCTIONS
	void loadNewEnemy();
	
	bool fight();

	bool fightWin();

	void fightLose();

	bool runAway();

	// some other functions
	void badInput(string& ui); // bad input message and procedure
	void clearScreen(); // clears screen

public:
	Game();
	void play();
};