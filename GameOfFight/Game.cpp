// Christian Deardorff: This my own work.

#include "Game.h"

// CONSTRUCTOR
Game::Game()
{
}

// PLAY
void Game::play()
{
	playerSelect();
	return;
}

// DATA FUNCTIONS


// MAIN MENU FUNCTIONS
void Game::playerSelect() throw (invalid_argument)
{
	quit = false;
	while (!quit)
	{
		// title
		cout << "Game Of Fight\n\n";

		// check for player_data folder
		fs::directory_entry playerDataFolder(playerDataFolderPath);
		if (!playerDataFolder.exists())
		{
			fs::create_directory(playerDataFolderPath);
		}

		// get player info
		vector<json> playerFiles;
		for (fs::path p : fs::directory_iterator(playerDataFolderPath)) // baby's first iterator
		{
			string playerData;
			json j;
			playerDataFile.open(p, ios::in);
			playerDataFile >> j;
			playerDataFile.close();
			playerFiles.push_back(j);
		}

		// get player character names and display them as options
		for (int i = 0; i < playerFiles.size(); i++)
		{ // playerFiles[file][save][datamember]
			cout << "[" << i + 1 << "] " << playerFiles[i][0]["name"].get<string>() << endl;
		}

		// display other options
		cout << "[0] Create Character\n[-] Quit Game\n";

		// user input
		string ui; cin >> ui;
		if (ui == "0") { playerFiles.clear(); clearScreen(); playerCreationName(); }
		else if (ui == "-") { clearScreen(); quit = true; }
		else
		{
			try
			{
				int ui2 = 0;
				ui2 = stoi(ui) - 1;
				if (ui2 < playerFiles.size() && ui2 >= 0)
				{
					clearScreen();
					selectedPlayerFile = playerFiles[ui2];
					selectedPlayerSave = getMostRecentSave(selectedPlayerFile); // get most recent save from selected player file
					playerFiles.clear();
					playerSelectConfirmation();

				}
				else { playerFiles.clear(); badInput(ui); }
			}
			catch (invalid_argument& e) { playerFiles.clear(); badInput(ui); }
		}
	}
	cout << "Game Of Fight\n\nGoodbye\n";
	return;
}

void Game::playerSelectConfirmation()
{
	bool cancel = false;
	while (!cancel) {
		// display some player stats
		cout << selectedPlayerSave["name"].get<string>() << ": " << selectedPlayerSave["title"].get<string>() << endl;
		cout << "Power Level: " << selectedPlayerSave["powerLevel"].get<int>() << endl;
		cout << "Wallet: " << selectedPlayerSave["wallet"].get<int>() << endl;
		cout << "HP: " << selectedPlayerSave["health"].get<int>() << endl;
		cout << selectedPlayerSave["equippedWeapon"]["name"].get<string>() << ": "
			<< selectedPlayerSave["equippedWeapon"]["damage"].get<int>() << endl;
		cout << selectedPlayerSave["equippedArmor"]["name"].get<string>() << ": "
			<< selectedPlayerSave["equippedArmor"]["defense"].get<int>() << endl;

		// display options
		cout << "[1] Play\n[-] Cancel\n";

		// user input
		string ui; cin >> ui;
		if (ui == "1")
		{
			cancel = true;
			loadSave();
			clearScreen();
			decisionMenu();
		}
		else if ("-") { cancel = true; clearScreen(); }
		else { badInput(ui); }
	}
	return;
}

void Game::playerCreationName()
{
	// ask for name and make a name
	cout << "Create Character\n\nName: ";
	string newName; cin >> newName;
	playerCreationClass(newName);
	clearScreen();
	return;
}

void Game::playerCreationClass(string& newName)
{
	// select class or cancel
	bool cancel = false;
	while (!cancel)
	{
		cout << "Class:\n[3] Fighter\n[2] Assassin\n[1] Tank\n[-] Cancel\n";
		string ui; cin >> ui;
		if (ui == "3") { playerCreationConfirmation(newName, "Fighter"); cancel = true; }
		else if (ui == "2") { playerCreationConfirmation(newName, "Assassin"); cancel = true; }
		else if (ui == "1") { playerCreationConfirmation(newName, "Tank"); cancel = true; }
		else if (ui == "-") { cancel = true; }
		else { badInput(ui); }
	}
	return;
}

void Game::playerCreationConfirmation(string& newName, string newTitle)
{
	// confirm player creation or cancel
	bool cancel = false;
	while (!cancel)
	{
		cout << "[2] Create Character\n[1] Create Character And Play\n[-] Cancel\n";
		string ui; cin >> ui;
		if (ui == "2") { newPlayerFile(newName, newTitle); cancel = true; }
		else if (ui == "1") 
		{ 
			selectedPlayerFile = newPlayerFile(newName, newTitle); 
			selectedPlayerSave = getMostRecentSave(selectedPlayerFile);
			cancel = true; 
			loadSave();
			clearScreen(); 
			decisionMenu(); 
		}
		else if (ui == "-") { cancel = true; }
		else { badInput(ui); }
	}
	return;
}

// DECISION MENU FUNCTIONS
void Game::decisionMenu()
{
	bool cancel = false;
	while (!cancel)
		{
			// player operations for debuggin or something
			player.updateStats();
			player.setHealth(player.getMaxHealth());
			// print decision menu
			cout << player.getName() << " - $" << player.getWallet() << " - HP: " << player.getHealth() << endl
				<< "[4] Fight\n[3] Items\n[2] Shop\n[1] Stats\n[0] Saves\n[-] Character Select\n[=] Quit Game\n";

			string ui; std::cin >> ui;
			if (ui == "4") 
			{
				clearScreen();
				decisionFight();
			}
			else if (ui == "3") 
			{
				clearScreen();
				decisionItems();
			}
			else if (ui == "2") 
			{
				clearScreen();
				decisionShop();
			}
			else if (ui == "1") 
			{
				clearScreen();
				decisionStats();
			}
			else if (ui == "0") 
			{
				clearScreen();
				decisionSaves();
			}
			else if (ui == "-") 
			{
				clearScreen();
				decisionCharacterSelect();
				cancel = true;
			}
			else if (ui == "=") 
			{ 
				clearScreen(); 
				decisionQuitGame(); 
				if (quit) cancel = true;
			}
			else { badInput(ui); }
		}
	return;
}

void Game::decisionQuitGame()
{
	bool cancel = false;
	while (!cancel)
	{
		// print quit game menu
		cout << player.getName() << " - Quit Game\n[2] Save and quit\n[1] Autosave and quit\n[0] Quit without saving\n[-] Cancel\n";
		string ui; std::cin >> ui;
		if (ui == "2") 
		{ 
			clearScreen();	
			newSaveMenu();	
			quit = true; 
			cancel = true; 
		}
		else if (ui == "1") 
		{ 
			clearScreen(); 
			autoSave(); 
			quit = true;  
			cancel = true; 
		}
		else if (ui == "0") 
		{ 
			clearScreen(); 
			quit = true; 
			cancel = true; 
		}
		else if (ui == "-") 
		{ 
			cancel = true; 
		}
		else { badInput(ui); }
	}
	return;
}

void Game::decisionCharacterSelect()
{
	bool cancel = false;
	while (!cancel)
	{
		cout << "Go to character select\n[2] Save and go\n[1] Autosave and go\n[0] Go without saving\n[-] Cancel\n";

		string ui; std::cin >> ui;

		if (ui == "2") 
		{
			clearScreen();
			newSaveMenu();
			cancel = true;
		}
		else if (ui == "1") 
		{
			clearScreen();
			autoSave();
			cancel = true;
		}
		else if (ui == "0") 
		{
			clearScreen();
			cancel = true;
		}
		else if (ui == "-") 
		{
			clearScreen();
			cancel = true;
		}
		else { badInput(ui); }
	}
	return;
}

void Game::decisionSaves()
{
	bool cancel = false;
	while (!cancel)
	{
		cout << "Saves - " << player.getName() << endl
			<< "[1] New Save\n[-] Cancel\n";
		printSaves(65, 90);

		// input
		string ui; std::cin >> ui;
		if (ui == "1")
		{
			clearScreen();
			newSaveMenu();
		}
		else if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else if (65 <= ui[0] && ui[0] <= 90)
		{
			clearScreen();
			saveFocusMenu(ui[0]);
			cancel = true;
		}
		else
		{
			badInput(ui);
		}
	}
	return;
}

void Game::decisionStats()
{
	bool cancel = false;
	while (!cancel)
	{
		cout << player.toString();
		cout << "\n[-] Cancel\n";

		string ui; cin >> ui;
		if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else
		{ badInput(ui); }
	}
}

void Game::decisionShop() //TODO save shop to player save file
{
	// restockShop = true; // testing 
	bool cancel = false;
	while (!cancel)
	{
		// print menu
		cout << "Shop - " << player.getName() << " - $" << player.getWallet()
			<< "\n[-] Cancel\n[0] Sell Items\n";
		// check for restock
		if (restockShop == true)
		{
			shop = stockShop();
			restockShop = false;
		}
		// print stock
		for (int i = 0; i < shop.size(); i++)
		{
			cout << "[" << i + 1 << "] " << shop[i]->getName() << endl;
		}
		// input
		string ui; std::cin >> ui;
		if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else if (ui == "0")
		{
			clearScreen();
			sellItemsMenu();
		}
		else
		{
			try
			{
				int index = stoi(ui) - 1;
				if (index >= 0 && index < shop.size())
				{
					clearScreen();
					buyItemFocusMenu(index);
				}
				else { badInput(ui); }
			}
			catch (invalid_argument& e) { badInput(ui); }
			}
	}
	return;
}

void Game::decisionItems() throw (invalid_argument)
{
	// Item* wep = new Weapon("test", 10, 10); player.addItem(wep);
	bool cancel = false;
	while (!cancel)
	{
		// print menu
		cout << "Items - " << player.getName() << "\n[-] Cancel\n[1] " 
			<< player.getEquippedWeapon()->getName() << " (Equipped)\n[2] "
			<< player.getEquippedArmor()->getName() << " (Equipped)\n";
		vector<Item*> items = player.getItems();
		for (int i = 0, j = 3; i < items.size(); i++, j++)
		{
			cout << "[" << j << "] " << items[i]->getName() << endl;
		}
		
		// input
		string ui; std::cin >> ui;
		if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else if (ui == "1")
		{
			clearScreen();
			Item* w = player.getEquippedWeapon();
			equippedItemFocusMenu(w);
		}
		else if (ui == "2")
		{
			clearScreen();
			Item* a = player.getEquippedArmor();
			equippedItemFocusMenu(a);
		}
		else
		{
			try
			{
				int ui2 = 0;
				ui2 = stoi(ui);
				if (ui2 >= 3 && ui2 < items.size()+3)
				{
					clearScreen();
					itemFocusMenu(ui2-3);
				}
				else { badInput(ui); }
			}
			catch (invalid_argument& e) { badInput(ui); }
		}
	}
	return;
}

void Game::decisionFight()
{
	bool fightAgain = true;
	bool run = false;
	bool newEnemy = true;
	while (!run && fightAgain)
	{
		if (newEnemy) 
		{ 
			loadNewEnemy(); 
			newEnemy = false;
		}
		cout << enemy.getTitle() << " " << enemy.getName() << " approaches!"
			<< "\n[1] Fight " << enemy.getName()
			<< "\n[-] Run Away\n";
		//input
		string ui; std::cin >> ui;
		if (ui == "-")
		{
			clearScreen();
			cout << "Lame...";
			Sleep(1000);
			clearScreen();
			run = true;
		}
		else if (ui == "1")
		{
			autoSave();
			fightAgain = fight(); // find a new fight or not
			newEnemy = fightAgain;
		}
		else { badInput(ui); }
	}
	if (!fightAgain) { restockShop = true; }
	autoSave();
	return;
}

// DECISION SUBMENU FUNCTIONS

void Game::buyItemFocusMenu(int itemIndex)
{
	bool cancel = false;
	while (!cancel)
	{
		// print menu
		Item* t = shop[itemIndex];
		std::cout << "Shop - Buy Item - " << player.getName() << " - $"
			<< player.getWallet() << endl << t->toString() << "[1] Buy\n[-] Cancel\n";
		//inout
		string ui; std::cin >> ui;
		if (ui == "1")
		{
			if (player.getWallet() - t->getWorth() > -1)
			{
				player.payMoney(t->getWorth());
				player.addItem(t);
				shop.erase(shop.begin() + itemIndex);
				clearScreen();
				cancel = true;
			}
			else
			{
				cout << "Not Enough Funds";
				Sleep(1000);
				clearScreen();
			}
		}
		else if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else { badInput(ui); }
	}
}

void Game::sellItemsMenu()
{
	// sadly very copy paste. I have deadlines
	bool cancel = false;
	while (!cancel)
	{
		// print menu
		std::cout << "Shop - Sell Items - " << player.getName() << " - $"
			<< player.getWallet() << "\n[-] Cancel\n";
		vector<Item*> items = player.getItems();
		for (int i = 0, j = 1; i < items.size(); i++, j++)
		{
			std::cout << "[" << j << "] " << items[i]->getName() << endl;
		}

		// input
		string ui; std::cin >> ui;
		if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else
		{
			try
			{
				int ui2 = 0;
				ui2 = stoi(ui);
				if (ui2 >= 1 && ui2 <= items.size())
				{
					clearScreen();
					sellItemFocusMenu(ui2-1);
				}
				else { badInput(ui); }
			}
			catch (invalid_argument& e) { badInput(ui); }
		}
	}
	return;
}

void Game::sellItemFocusMenu(int itemIndex)
{
	bool cancel = false;
	while (!cancel)
	{
		// print menu
		Item* t = player.getItems()[itemIndex];
		std::cout << "Shop - Sell Items - " << player.getName() << " - $" 
			<< player.getWallet() << endl << t->toString() << "[1] Sell\n[-] Cancel\n";
		//input
		string ui; std::cin >> ui;
		if (ui == "1")
		{
			shop.push_back(t);
			player.dropItem(itemIndex);
			player.recieveMoney(t->getWorth());
			clearScreen();
			cancel = true;
		}
		else if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else { badInput(ui); }
	}
	return;
}

void Game::equippedItemFocusMenu(Item* i)
{
	bool cancel = false;
	while (!cancel)
	{
		cout << i->toString() << "[-] Cancel\n";
		string ui; std::cin >> ui;
		switch (ui[0])
		{
		case '-': clearScreen(); cancel = true; break;
		default: badInput(ui);
		}
	}
	return;
}

void Game::itemFocusMenu(int itemIndex)
{
	bool cancel = false;
	while (!cancel)
	{
		Item* t = player.getItems()[itemIndex];
		cout << t->toString() << "[1] Equip\n[-] Cancel\n";
		string ui; std::cin >> ui;
		if (ui == "1")
		{
			Weapon* w = dynamic_cast<Weapon*>(t);
			Armor* a = dynamic_cast<Armor*>(t);
				if (w != NULL)
				{
					player.addItem(player.getEquippedWeapon());
					player.equipWeapon(w);
					player.dropItem(itemIndex);
					player.updateStats();
				}
				else if (a != NULL)
				{
					player.addItem(player.getEquippedArmor());
					player.equipArmor(a);
					player.dropItem(itemIndex);
				}
			clearScreen();
			cancel = true;
		}
		else if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else { badInput(ui); }
	}
	return;
}

void Game::saveFocusMenu(char slot)
{
	string s; s += slot;
	int index = -1;
	for (int i = 0; i < selectedPlayerFile.size(); i++)
	{
		string saveSlot = selectedPlayerFile[i]["saveSlot"].get<string>();
		string saveName = selectedPlayerFile[i]["saveName"].get<string>();
		int saveTime = selectedPlayerFile[i]["saveTime"].get<int>();
		if (s == saveSlot)
		{
			index = i;
			cout << saveName << " " << saveTime << endl;
			break;
		}
	}

	cout << "[2] Load and save\n[1] Load and autosave\n[0] Load without saving\n[-] Cancel\n";

	bool cancel = false;
	while (!cancel)
	{
		// input 
		string ui; cin >> ui;

		switch (ui[0])
		{
		case '2':
			clearScreen();
			selectedPlayerSave = selectedPlayerFile[index];
			newSaveMenu();
			loadSave();
			cancel = true;
			break;
		case '1':
			clearScreen();
			selectedPlayerSave = selectedPlayerFile[index];
			autoSave();
			loadSave();
			cancel = true;
			break;
		case '0':
			clearScreen();
			selectedPlayerSave = selectedPlayerFile[index];
			loadSave();
			cancel = true;
			break;
		case '-':
			clearScreen();
			cancel = true;
			break;
		default:
			badInput(ui);
		}
	}
	return;
}

void Game::newSaveMenu()
{
	bool cancel = false;
	while (!cancel) 
	{
		//print new save menu
		cout << "New Save - " << player.getName() << endl
			<< "Choose Save Slot\n[-] Cancel\n";

		printSaves(66, 90);

		// user input 
		string ui; cin >> ui;
		if (ui == "-") { cancel = true; }
		else if (int(ui[0]) >= 66 && int(ui[0]) <= 90)
		{
			clearScreen();
			overwriteMenu(ui[0]);
			cancel = true;
		}
		else { badInput(ui); }
	}
	return;
}

void Game::overwriteMenu(char slot)
{
	// check if the player wwants to overwrite a save
	bool cancel = false;
	while (!cancel)
	{
		// print menu
		cout << "Overwrite Slot " << slot << "?\n[1] Overwrite\n[-] Cancel\n";

		// user input
		string ui;  cin >> ui; 
		switch (ui[0])
		{
		case '-': cancel = true; clearScreen(); break;
		case '1': cancel = true; clearScreen(); nameSaveMenu(slot); break;
		default: badInput(ui);
		}
	}
	return;
}

void Game::nameSaveMenu(char slot)
{
	cout << "Name New Save: ";
	string ui; std::cin >> ui;
	clearScreen();
	newSave(slot, ui);
	return;
}

// FILE FUNCTIONS
void Game::printSaves(int min, int max)
{
	for (int i = min; i <= max; i++)
	{
		// print save slot letter, save name, time and date (converted to human readable from time int)
		// can't print the autosave slot, must print all save slots, regardless of it being filled or not
		int index = (i - 65) % selectedPlayerFile.size();
		time_t chungus = selectedPlayerFile[index]["saveTime"].get<int>();
		string saveSlot = selectedPlayerFile[index]["saveSlot"].get<string>();
		string saveName = selectedPlayerFile[index]["saveName"].get<string>();

		if (i == int(saveSlot[0]))
		{
			cout << "[" << saveSlot << "] "
				<< saveName << " ("
				<< localtime(&chungus) << ")\n"; // need to figure this out
		}
		else
		{
			cout << "[" << char(i) << "] -\n";
		}
	}
}

void Game::newSave(char slot, string saveName)
{
	// let it be known that this file pathname shiz cost me an hour of being confused
	fs::path filePathName = playerDataFolderPath;
	string fileName = selectedPlayerFile[0]["fileName"].get<string>();
	filePathName /= fileName;

	// get the newSave
	json newSave = constructNewSaveJson(slot, saveName, fileName);

	// search for save with this slot. if none then make one. 
	// if there is one then overwrite it. then write json to file
	// selectedPlayerFile is technically a json object, not a file

	for (int i = 1; i < selectedPlayerFile.size(); i++)
	{
		char saveSlot = selectedPlayerFile[i]["saveSlot"].get<string>()[0];
		if (saveSlot == slot)
		{
			selectedPlayerFile[i] = newSave;
			playerDataFile.open(filePathName, ios::out); 
			playerDataFile << selectedPlayerFile.dump(2);
			playerDataFile.close();
			return;
		} 
	}
	selectedPlayerFile.push_back(newSave);
	playerDataFile.open(filePathName, ios::out); 
	playerDataFile << selectedPlayerFile.dump(2);
	playerDataFile.close();
	return;
}

void Game::autoSave()
{
	cout << "Autosaving " << player.getName() << "...";
	Sleep(1000);
	fs::path filePathName = playerDataFolderPath;
	string fileName = selectedPlayerFile[0]["fileName"].get<string>();
	filePathName /= fileName;
	json autoSave = constructNewSaveJson('A', "Autosave", fileName);

	// this is assuming the first save is the autosave. im doing this for time. otherwise would have to loop and find
	// could make a findSaveIndex function
	selectedPlayerFile[0] = autoSave;
	playerDataFile.open(filePathName, ios::out);
	playerDataFile << selectedPlayerFile.dump(2);
	playerDataFile.close();

	clearScreen();

	return;
}

void Game::loadSave()
{
	Player p(
		selectedPlayerSave["titleDmgMod"].get<int>(),
		selectedPlayerSave["titleDefMod"].get<int>(),
		selectedPlayerSave["powerLevel"].get<int>(),
		selectedPlayerSave["currentTopDmg"].get<int>(),
		selectedPlayerSave["currentTopDef"].get<int>(),
		selectedPlayerSave["victories"].get<int>(),
		selectedPlayerSave["defeats"].get<int>(),
		selectedPlayerSave["health"].get<int>(),
		selectedPlayerSave["maxHealth"].get<int>(),
		selectedPlayerSave["damage"].get<int>(),
		selectedPlayerSave["defense"].get<int>(),
		selectedPlayerSave["wallet"].get<int>(),
		selectedPlayerSave["name"].get<string>(),
		selectedPlayerSave["title"].get<string>()
		);
	
	// load weapon items
	for (int i = 0; i < selectedPlayerSave["weapons"].size(); i++)
	{
		string name = selectedPlayerSave["weapons"][i]["name"].get<string>();
		int worth = selectedPlayerSave["weapons"][i]["worth"].get<int>();
		int damage = selectedPlayerSave["weapons"][i]["damage"].get<int>();
		Item* item = new Weapon(name, worth, damage);
		p.addItem(item);
	}

	// load armor items
	for (int i = 0; i < selectedPlayerSave["armors"].size(); i++)
	{
		string name = selectedPlayerSave["armors"][i]["name"];
		int worth = selectedPlayerSave["armors"][i]["worth"];
		int defense = selectedPlayerSave["armors"][i]["defense"];
		Item* item = new Armor(name, worth, defense);
		p.addItem(item);
	}

	// load equipped weapon
	string wName = selectedPlayerSave["equippedWeapon"]["name"].get<string>();
	int wWorth = selectedPlayerSave["equippedWeapon"]["worth"].get<int>();
	int wDamage = selectedPlayerSave["equippedWeapon"]["damage"].get<int>();
	Item* w = new Weapon(wName, wWorth, wDamage);
	p.equipWeapon(w);

	//load equipped armor
	string aName = selectedPlayerSave["equippedArmor"]["name"].get<string>();
	int aWorth = selectedPlayerSave["equippedArmor"]["worth"].get<int>();
	int aDefense = selectedPlayerSave["equippedArmor"]["defense"].get<int>();
	Item* a = new Armor(aName, aWorth, aDefense);
	p.equipArmor(a);

	// deep copy p to player
	player = p;
	return;
}

json Game::constructNewSaveJson(char slot, string saveName, string fileName)
{
	// get items and sort them as weapons and armor and 
	// put them into respective containers for saving
	vector <Item*> items = player.getItems();

	json weapons = json::array();
	json armors = json::array();

	for (int i = 0; i < items.size(); i++)
	{
		Item* t = items[i];
		// dynamic casting. fun
		Weapon* w = dynamic_cast<Weapon*>(t);
		Armor* a = dynamic_cast<Armor*>(t);
		if (w != NULL)
		{
			json j = {
				{"name", w->getName()},
				{"worth", w->getWorth()},
				{"damage", w->getDamage()}
			};
			weapons.push_back(j);
		}
		if (a != NULL)
		{
			json j = {
				{"name", a->getName()},
				{"worth", a->getWorth()},
				{"defense", a->getDefense()}
			};
			armors.push_back(j);
		}
	}

	// get equipped weapon and its data members
	Weapon* equippedWeapon = static_cast<Weapon*>(player.getEquippedWeapon()); // using static_cast because I expect a weapon pointer
	json eW = {
		{"name", equippedWeapon->getName()}, // throws error reading characters of string: bad_alloc
		{"worth", equippedWeapon->getWorth()},
		{"damage", equippedWeapon->getDamage()}
	};

	// get equipped armor and its data members
	Armor* equippedArmor = static_cast<Armor*>(player.getEquippedArmor());
	json eA = {
		{"name", equippedArmor->getName()},
		{"worth", equippedArmor->getWorth()},
		{"defense", equippedArmor->getDefense()}
	};

	string s; s += slot; // need this cuz slot has to be a string.

	//  construct new json save
	json newSave = {
		{"armors", armors},
		{"currentTopDef", player.getCurrentTopDef()},
		{"currentTopDmg", player.getCurrentTopDmg()},
		{"damage", player.getDamage()},
		{"defeats", player.getDefeats()},
		{"defense", player.getDefense()},
		{"equippedArmor", eA},
		{"equippedWeapon", eW},
		{"fileName", fileName},
		{"health", player.getHealth()},
		{"maxHealth", player.getMaxHealth()},
		{"name", player.getName()},
		{"powerLevel", player.getPowerLevel()},
		{"saveName", saveName},
		{"saveSlot", s},
		{"saveTime", time(0)},
		{"title", player.getTitle()},
		{"titleDefMod", player.getTitleDefMod()},
		{"titleDmgMod", player.getTitleDmgMod()},
		{"victories", player.getVictories()},
		{"wallet", player.getWallet()},
		{"weapons", weapons}
	};
	return newSave;
}

json Game::newPlayerFile(string& newName, string& newTitle)
{
	// make the file name to store so we know what file to open 
	// when saving later
	fs::path filePathName = playerDataFolderPath;
	string fileName = newTitle + newName + to_string(time(0)) + ".json";
	filePathName /= fileName;

	// calculate title mods. 
	int titleDefMod = 100000; int titleDmgMod = 100000;
	if(newTitle == "Assassin") { titleDefMod = -10; titleDmgMod = 10; }
	if(newTitle == "Tank") { titleDefMod = 10; titleDmgMod = -10; }
	// construct the initial player data json
	json armors = json::array();
	json weapons = json::array();
	json j = json::array({{
		{"armors", armors},
		{"currentTopDef", 0},
		{"currentTopDmg", 0},
		{"damage", 0},
		{"defeats", 0},
		{"defense", 0},
		{"equippedArmor", {
			{"name", "Shirt"},
			{"worth", 0},
			{"defense", 0}
		}},
		{"equippedWeapon", {
			{"name", "Fist"},
			{"worth", 0},
			{"damage", 10}
		}},
		{"fileName", fileName},
		{"health", 100},
		{"maxHealth", 100},
		{"name", newName},
		{"powerLevel", 0},
		{"saveName", "Autosave"},
		{"saveSlot", "A"},
		{"saveTime", time(0)},
		{"title", newTitle},
		{"titleDefMod", titleDefMod},
		{"titleDmgMod", titleDmgMod},
		{"victories", 0},
		{"wallet", 0},
		{"weapons", weapons}
	}});

	// create a new file for new player
	playerDataFile.open(filePathName, ios::out);
	playerDataFile << j.dump(2);
	playerDataFile.close();
	return j;
}

json Game::getMostRecentSave(json& playerInfo)
{
	// get most recent save from player data file/json
	int mostRecentSaveTime = 0;
	json playerSave;
	for (int i = 0; i < playerInfo.size(); i++)
	{
		int saveTime = playerInfo[i]["saveTime"];
		if (saveTime > mostRecentSaveTime) {
			mostRecentSaveTime = saveTime;
			playerSave = playerInfo[i];
		}
	}
	return playerSave;
}

// SHOP FUNCTIONS
vector<Item*> Game::stockShop()
{
	// clear shop
	for (int i = 0; i < shop.size(); i++)
	{
		delete shop[i];
	}
	shop.clear();
	// get item data. could hard code a map, but gonna read json file for now
	ifstream itemDataIn;
	json itemData;
	itemDataIn.open("item_data.json");
	itemDataIn >> itemData;
	itemDataIn.close();

	// determine tier to get items from. 
	int itemTierIndex = (player.getPowerLevel() / 10) - 1;

	// get random armor name. This one is kinda loaded.
	string armorName = itemData[itemTierIndex]["armors"][rand() % (itemData[itemTierIndex]["armors"].size())]["name"].get<string>();

	// get defense value. same as damage I guess
	int armorDefense = int(ceil(player.getPowerLevel() / 2)+ (rand() % 2) + 5);

	// get random weapon name
	string weaponName = itemData[itemTierIndex]["weapons"][rand() % (itemData[itemTierIndex]["weapons"].size())]["name"].get<string>();

	// get damage value
	int weaponDamage = int(ceil(player.getPowerLevel() / 2) + (rand() % 2) + 5);

	// for now just gonna generate 1 of each item type. worth is same as def/dam for now
	Item* a = new Armor(armorName, armorDefense, armorDefense);
	Item* w = new Weapon(weaponName, weaponDamage, weaponDamage);

	// not sure why I don't just put this directly in shop. eh who cares
	vector<Item*> deliveryTruck;
	deliveryTruck.push_back(a); deliveryTruck.push_back(w);
	return deliveryTruck;
}

// FIGHT FUNCTIONS
void Game::loadNewEnemy()
{
	// more copy paste from stockShop. sorry
	// here we equipping the enemy with items based off of player. rigged so the player wins right now,
	// since consumables aren't in the game yet.
	// get item data. could hard code a map, but gonna read json file for now
	ifstream dataIn;
	json itemData;
	dataIn.open("item_data.json");
	dataIn >> itemData;
	dataIn.close();

	// determine tier to get items from. 
	int itemTierIndex = (player.getPowerLevel() / 10) - 1;

	// get random armor name. This one is kinda loaded.
	string armorName = itemData[itemTierIndex]["armors"][rand() % (itemData[itemTierIndex]["armors"].size())]["name"].get<string>();

	// get defense value. same as damage I guess
	int armorDefense = int(ceil(player.getPowerLevel() / 2) + (rand() % 2));

	// get random weapon name
	string weaponName = itemData[itemTierIndex]["weapons"][rand() % (itemData[itemTierIndex]["weapons"].size())]["name"].get<string>();

	// get damage value
	int weaponDamage = int(ceil(player.getPowerLevel() / 2) + (rand() % 2));

	Item* a = new Armor(armorName, armorDefense, armorDefense);
	Item* w = new Weapon(weaponName, weaponDamage, weaponDamage);
	
	delete enemy.getEquippedWeapon(); // should deallocate the memory here
	enemy.equipWeapon(w); // equip new weapon
	delete enemy.getEquippedArmor(); 
	enemy.equipArmor(a); // equip new armor

	// more enemy things. not final values. here for demonstration
	enemy.updateDamage();
	enemy.updateDefense();
	enemy.setMaxHealth(player.getMaxHealth() - 10);
	enemy.setHealth(enemy.getMaxHealth());
	enemy.setWallet(player.getWallet()/4+10); 

	// for now we will always be fighting fighter chad
	enemy.setName("Chad");
	enemy.setTitle("Fighter");
}

bool Game::fight()
{
	bool fightAgain = false;
	bool end = false;
	while (!end)
	{
		// fight menu
		cout << "Fight!\n"
			<< enemy.getName() << " - HP: " << enemy.getHealth() << endl
			<< player.getName() << " - HP: " << player.getHealth() << endl
			<< "[2] Attack\n[1] Items\n[-] Run\n";

		// input
		string ui; std::cin >> ui;

		// decision
		if (ui == "2") // attack
		{
			clearScreen();
			int attack = enemy - player; // deals damage on enemy from player and returns that damage.
			cout << "Fight!\n"
				<< enemy.getName() << " - HP: " << enemy.getHealth() << endl
				<< player.getName() << " - HP: " << player.getHealth() << endl
			    << player.getName() << " attacks with " << player.getEquippedWeapon()->getName() << endl;
			Sleep(1000);
			cout << player.getName() << " dealt " << attack << " damage!\n";
			Sleep(2000);

			if (enemy.getHealth() < 0) // is enemy dead
			{
				Sleep(1000);
				clearScreen();
				player.recieveMoney(enemy.getWallet());
				fightAgain = fightWin();
				end = true;
			}
			else // enemy is not dead and attacks
			{
				clearScreen();
				int attack = player - enemy;
				cout << "Fight!\n"
					<< enemy.getName() << " - HP: " << enemy.getHealth() << endl
					<< player.getName() << " - HP: " << player.getHealth() << endl
				    << enemy.getName() << " attacks with " << enemy.getEquippedWeapon()->getName() << endl;
				Sleep(1000);
				cout << enemy.getName() << " dealt " << attack << " damage!";
				Sleep(2000);
				clearScreen();
			}
			if (player.getHealth() < 0) // is player dead
			{
				fightLose();
				end = true;
			}
		}
		else if (ui == "1") // items
		{
			clearScreen();
			decisionItems();
		}
		else if (ui == "-") // run away
		{
			clearScreen();
			end = runAway();
		}
		else { badInput(ui); }
	}
	return fightAgain;
}

bool Game::fightWin()
{
	bool cancel = false; // in this case this is just for getting out of this menu
	bool fightAgain = false;
	while (!cancel)
	{
		cout << player.getName() << " has defeated " << enemy.getName() << "! + $" << enemy.getWallet()
			<< "\n[1] Find another fight\n[-] Leave\n";
		string ui; std::cin >> ui;
		if (ui == "1")
		{
			clearScreen();
			fightAgain = true;
			cancel = true;
		}
		else if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else { badInput(ui); }
	}
	return fightAgain;
}

void Game::fightLose()
{
	bool cancel = false;
	while (!cancel)
	{
		cout << enemy.getName() << " has defeated " << player.getName() << "! - $" << enemy.getWallet() // penelty for lose is rewards right now
			<< "\n[1] Continue\n";
		string ui; cin >> ui;
		if (ui == "1")
		{
			clearScreen();
			cancel = true;
		}
		else { badInput(ui); }
	}
	return;
}

bool Game::runAway()
{
	bool run = false;
	bool cancel = false;
	while (!cancel)
	{
		cout << "Run!?\n[1] Run - $" << enemy.getWallet() / 2
			<< "\n[-] Cancel\n";
		// input
		string ui; std::cin >> ui;

		//decision
		if (ui == "1")
		{
			if (player.getWallet() - enemy.getWallet() >= 0) // can player pay
			{
				clearScreen();
				cout << "Loser...";
				run = true;
				cancel = true;
				Sleep(1000);
				clearScreen();
			}
			else
			{
				cout << "Not enough money";
				Sleep(1000);
				clearScreen();
				cancel = true;
			}
		}
		else if (ui == "-")
		{
			clearScreen();
			cancel = true;
		}
		else { badInput(ui); }
	}
	return run;
}

// OTHER FUNCTIONS

void Game::badInput(string& ui)
{
	// tells user bad inpu and displays their input and clears screen
	cout << "Bad Input '" << ui << "'";
	Sleep(1000); clearScreen();
	return;
}
void Game::clearScreen() 
{
	// https://stackoverflow.com/questions/6486289/how-can-i-clear-console in the comments from user Joma
	#if defined _WIN32
		system("cls");
		//clrscr(); // including header file : conio.h
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
		//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
	#elif defined (__APPLE__)
		system("clear");
	#endif
		return;
}