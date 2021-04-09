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
	// title
	cout << "Game Of Fight\n\n";

	//get players file
	fstream playersDataFile;
	playersDataFile.open("players.data", ios::in);
	if (!playersDataFile) // if player file doesn't exist. help from good ol' SO
	{
		playersDataFile.open("players.data", ios::out);
		playersDataFile.close();
		playersDataFile.open("players.data", ios::in);
	}

	while (!playersDataFile.eof())
	{
		vector<string> vs;
		string s;
		getline(playersDataFile, s);
		vs.push_back(s);
		player.
	}
	playersDataFile.close();
	return;
}

void Game::playerSelectConfirmation()
{

}

void Game::playerCreationName()
{

}

void Game::playerCreationClass()
{

}

void Game::playerCreationConfirmation()
{

}

// DECISION MENU FINCTIONS
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

// SAVE FUNCTIONS
void Game::newSave()
{

}

void Game::loadSave()
{

}

// OTHER FUNCTIONS
void Game::clearScreen()
{

}