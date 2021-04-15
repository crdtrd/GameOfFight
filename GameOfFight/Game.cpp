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
void Game::playerSelect()
{
	bool quit = false;
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
		vector<json> playerSaves;
		for (fs::path p : fs::directory_iterator(playerDataFolderPath)) // baby's first iterator
		{
			string playerData;
			json j;
			playerDataFile.open(p, ios::in);
			playerDataFile >> j;
			playerDataFile.close();
			playerSaves.push_back(getMostRecentSave(j));
		}

		// get player character names and display them as options
		for (int i = 0; i < playerSaves.size(); i++)
		{
			cout << "[" << i + 1 << "] " << playerSaves[i]["name"].get<string>() << endl;
		}

		// display other options
		cout << "[0] Create Character\n[-] Quit Game\n";

		// user input
		string ui; cin >> ui;
		if (ui == "0") { playerSaves.clear(); clearScreen(); playerCreationName(); }
		else if (ui == "-") { clearScreen(); cout << "Game Of Fight\n\nGoodbye\n"; quit = true; }
		else
		{
			try
			{
				int ui2 = 0;
				ui2 = stoi(ui) - 1;
				if (ui2 < playerSaves.size() && ui2 >= 0)
				{
					clearScreen();
					json playerSelection = playerSaves[ui2];
					playerSaves.clear();
					playerSelectConfirmation(playerSelection);

				}
				else { playerSaves.clear(); badInput(ui); }
			}
			catch (invalid_argument& e) { playerSaves.clear(); badInput(ui); }
		}
	}
	return;
}

void Game::playerSelectConfirmation(json& playerSave)
{
	bool cancel = false;
	while (!cancel) {
		// display some player stats
		cout << playerSave["name"].get<string>() << ": " << playerSave["title"].get<string>() << endl;
		cout << "Power Level: " << playerSave["powerLevel"].get<int>() << endl;
		cout << "Wallet: " << playerSave["wallet"].get<int>() << endl;
		cout << "HP: " << playerSave["health"].get<int>() << endl;
		cout << playerSave["equippedWeapon"]["name"].get<string>() << ": "
			<< playerSave["equippedWeapon"]["damage"].get<int>() << endl;
		cout << playerSave["equippedArmor"]["name"].get<string>() << ": "
			<< playerSave["equippedArmor"]["defense"].get<int>() << endl;

		// display options
		cout << "[1] Play\n[-] Cancel\n";

		// user input
		string ui; cin >> ui;
		if (ui == "1")
		{
			cancel = true;
			loadSave(playerSave);
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
			json playerInfo = newPlayerFile(newName, newTitle); 
			json playerSave = getMostRecentSave(playerInfo);
			loadSave(playerSave);
			clearScreen(); 
			decisionMenu(); 
			cancel = true; 
		}
		else if (ui == "-") { cancel = true; }
		else { badInput(ui); }
	}
	return;
}

// DECISION MENU FUNCTIONS
void Game::decisionMenu()
{
	
}

void Game::decisionQuitGame()
{

}

void Game::decisionCharacterSelect()
{

}

void Game::decisionSaves()
{

}

void Game::decisionStats()
{

}

void Game::decisionShop()
{

}

void Game::decisionItems()
{

}

void Game::decisionFight()
{

}

// FILE FUNCTIONS
void Game::newSave()
{

}

void Game::loadSave(json& save)
{

}

json Game::newPlayerFile(string& newName, string& newTitle)
{
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
		{"health", 100},
		{"maxHealth", 100},
		{"name", newName},
		{"powerLevel", 0},
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
	fs::path filePathName = playerDataFolderPath;
	filePathName /= newTitle + newName + to_string(time(0)) + ".json";
	playerDataFile.open(filePathName, ios::out);
	playerDataFile << j.dump(2);
	playerDataFile.close();
	return j;
}

json Game::getMostRecentSave(json& playerInfo)
{
	// get most recent save.
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