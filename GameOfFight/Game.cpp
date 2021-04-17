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
// DATA FUNCTIONSl


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
			// print decision menu
			cout << player.getName() << " - $" << player.getWallet() << " - HP: " << player.getHealth() << endl
				<< "[4] Fight\n[3] Items\n[2] Shop\n[1] Stats\n[0] Saves\n[-] Character Select\n[=] Quit Game\n";

			string ui; std::cin >> ui;
			if (ui == "4") 
			{
			}
			else if (ui == "3") 
			{
				clearScreen();
				decisionItems();
			}
			else if (ui == "2") 
			{
			}
			else if (ui == "1") 
			{
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
		cout << "Go to character select\n[2] Save and go\n[1] Autosave and go\n[0] Go without saving\n[-] Cancel";

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

}

void Game::decisionShop()
{

}

void Game::decisionItems() throw (invalid_argument)
{
	bool cancel = false;
	while (!cancel)
	{
		// print menu
		cout << "Items - " << player.getName() << "\n[-] Cancel\n[1] " 
			<< player.getEquippedWeapon().getName() << " (Equipped)\n[2] "
			<< player.getEquippedArmor().getName() << " (Equipped)\n";
		vector<Item> items = player.getItems();
		for (int i = 0, j = 3; i < items.size(); i++, j++)
		{
			cout << "[" << j << "] " << items[i].getName() << endl;
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
			Weapon w = player.getEquippedWeapon();
			equippedItemFocusMenu(w);
		}
		else if (ui == "2")
		{
			clearScreen();
			Armor a = player.getEquippedArmor();
			equippedItemFocusMenu(a);
		}
		else
		{
			try
			{
				int ui2 = 0;
				ui2 = stoi(ui);
				if (3 <= ui2 && ui2 < items.size())
				{
					clearScreen();
					itemFocusMenu(items[ui2 - 3]);
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

}

// DECISION SUBMENU FUNCTIONS

void Game::equippedItemFocusMenu(Item& i)
{
	bool cancel = false;
	while (!cancel)
	{
		cout << i.toString() << "[-] Cancel\n";
		string ui; std::cin >> ui;
		switch (ui[0])
		{
		case '-': clearScreen(); cancel = true; break;
		default: badInput(ui);
		}
	}
	return;
}

void Game::itemFocusMenu(Item& i)
{
	bool cancel = false;
	while (!cancel)
	{
		cout << i.toString() << "[1] Equip\n[-] Cancel\n";
		string ui; std::cin >> ui;
		switch (ui[0])
		{
		case '1':
			// equip the thing
			clearScreen();
			cancel = true;
			break;
		case '-':
			cancel = true;
			break;
		default:
			badInput(ui);
		}
	}
	return;
}

void Game::saveFocusMenu(char slot)
{
	string s; s += slot;
	int index;
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
			selectedPlayerSave = selectedPlayerFile[index];
			clearScreen();
			newSaveMenu();
			loadSave();
			cancel = true;
			break;
		case '1':
			selectedPlayerSave = selectedPlayerFile[index];
			autoSave();
			loadSave();
			cancel = true;
			break;
		case '0':
			selectedPlayerSave = selectedPlayerFile[index];
			loadSave();
			cancel = true;
			break;
		case '-':
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
		Weapon w(name, worth, damage);
		p.addItem(w);
	}

	// load armor items
	for (int i = 0; i < selectedPlayerSave["armors"].size(); i++)
	{
		string name = selectedPlayerSave["armors"][i]["name"];
		int worth = selectedPlayerSave["armors"][i]["worth"];
		int defense = selectedPlayerSave["armors"][i]["defense"];
		Armor a(name, worth, defense);
		p.addItem(a);
	}

	// load equipped weapon
	string wName = selectedPlayerSave["equippedWeapon"]["name"].get<string>();
	int wWorth = selectedPlayerSave["equippedWeapon"]["worth"].get<int>();
	int wDamage = selectedPlayerSave["equippedWeapon"]["damage"].get<int>();
	Weapon w(wName, wWorth, wDamage);
	p.equipWeapon(w);

	//load equipped armor
	string aName = selectedPlayerSave["equippedArmor"]["name"].get<string>();
	int aWorth = selectedPlayerSave["equippedArmor"]["worth"].get<int>();
	int aDefense = selectedPlayerSave["equippedArmor"]["defense"].get<int>();
	Armor a(aName, aWorth, aDefense);
	p.equipArmor(a);

	// deep copy p to player
	player = p;
	return;
}

json Game::constructNewSaveJson(char slot, string saveName, string fileName)
{
	// get items and sort them as weapons and armor and 
	// put them into respective containers for saving
	vector <Item> items = player.getItems();

	json weapons = json::array();
	json armors = json::array();

	for (int i = 0; i < items.size(); i++)
	{
		Item t = items[i];
		Item* pt = &t;
		// dynamic casting. fun
		Weapon* w = dynamic_cast<Weapon*>(pt);
		Armor* a = dynamic_cast<Armor*>(pt);
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
	Weapon equippedWeapon;
	equippedWeapon = player.getEquippedWeapon();
	json eW = {
		{"name", equippedWeapon.getName()}, // throws error reading characters of string: bad_alloc
		{"worth", equippedWeapon.getWorth()},
		{"damage", equippedWeapon.getDamage()}
	};

	// get equipped armor and its data members
	Armor equippedArmor;
	equippedArmor = player.getEquippedArmor();
	json eA = {
		{"name", equippedArmor.getName()},
		{"worth", equippedArmor.getWorth()},
		{"defense", equippedArmor.getDefense()}
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
		{"wallet", player.getDefeats()},
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
		{"titleDefMod", 0},
		{"titleDmgMod", 0},
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