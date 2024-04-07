// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Game/game.h"
#include "../GUI/MainMenu.h"
#include "Interactable/Wall.h"
#include "Game/gamelogger.h"
#include "Door\door.h"

using namespace CppUnit;
using namespace CampaignEditor;
using namespace gamelogger;
using namespace door;

int main()
{
	// Get the top level suite from the registry
	Test* suite = TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CompilerOutputter(&runner.result(),
		std::cerr));
	// Run the tests.
	bool wasSucessful = runner.run();

	// Return error code 1 if the one of test failed.
	if (!wasSucessful) {
		return 1;
	}

	MainMenu * m = new MainMenu();
	m->show();

	Fl::run();

	getchar();

	//hardcode maps and campaing here
	//creare player Character
	Character::Character* playerCharacter = new Character::Character();
	Character::Character* enemyCharacter = new Character::Character("Testaniel Unitoph", Character::Character_Class::Fighter, false, new AggressorStrategy());
	playerCharacter->Inventory().AddNewItem(new item::Item("testShield", 2, Shield, ArmorClass, 10));

	//Create map
	Map::Map* currentMap = new Map::Map(20,20);
	std::vector<int> currentMapLocation;
	currentMapLocation.push_back(1);
	currentMapLocation.push_back(1);

	std::vector<int> currentMapDoorSpawnPoint;
	currentMapDoorSpawnPoint.push_back(12);
	currentMapDoorSpawnPoint.push_back(9);

	Map::Map* otherMap = new Map::Map(10, 10);
	std::vector<int> otherMapLocation;
	otherMapLocation.push_back(2);
	otherMapLocation.push_back(1);

	std::vector<int> otherMapDoorSpawnPoint;
	otherMapDoorSpawnPoint.push_back(6);
	otherMapDoorSpawnPoint.push_back(5);

	Door* door = new Door(1, currentMap->GetMapID(), otherMap->GetMapID(), currentMapLocation, otherMapLocation, currentMapDoorSpawnPoint, otherMapDoorSpawnPoint);
	currentMap->setCell(10, 8, door);
	otherMap->setCell(4, 4, door);

	GameLogger* gameLogger = new GameLogger(currentMap);
	playerCharacter->Attach(gameLogger);
	enemyCharacter->Attach(gameLogger);

	//add player to map
	currentMap->setCharacter(9, 9, playerCharacter);
	currentMap->setCharacter(9, 12, enemyCharacter);
	//add walls to map
	for (int i = 0; i < currentMap->getRows(); i++) {
		currentMap->setCell(i, 0, new Wall);
	}
	for (int i = 0; i < currentMap->getRows(); i++) {
		currentMap->setCell(i, currentMap->getCols()-1, new Wall);
	}
	//create random machine
	std::random_device rd;
	//add items to map
	//between 0 and 5 items
	int numOfItems = rd() % 5;
	for (int i = 0; i < numOfItems; i++) {
		currentMap->setCell(rd() % (currentMap->getRows()), rd() % (currentMap->getRows())+1, new item::Item());
	}

	currentMap->setCell(9, 8, new Item());

	ItemContainer* backpackObject = new ItemContainer("Wanderer's Backpack", Backpack, 30.0);
	
	Item* backpackShieldItem = new Item("Sturdy Shield", 4, Shield, ArmorClass, 12);
	Item* backpackBootsItem = new Item("Traveler's Boots", 4, Boots, Dexterity, 5);

	backpackObject->AddNewItem(backpackShieldItem);
	backpackObject->AddNewItem(backpackBootsItem);

	currentMap->setCell(8, 8, backpackObject);

	//Create campaign
	campaign::Campaign* currentCampaign = new campaign::Campaign(2, 2);
	//Add map to campaing
	currentCampaign->AddMapToCampaign(1, 1, *currentMap);
	currentCampaign->AddMapToCampaign(2, 1, *otherMap);
	CampaignMap currentCampaignMap;
	currentCampaignMap.coorX = 1;
	currentCampaignMap.coorY = 1;
	currentCampaignMap.mapID = currentMap->GetMapID();
	currentCampaign->SetCurrentMap(currentCampaignMap);

	//Create game instance	
	game::Game* currentGame = new game::Game();
	//set currentCampaiogn in currentGame
	currentGame->SetGameCampaign(currentCampaign);
	//set player character 
	currentGame->SetActiveCharacter(playerCharacter);
	std::vector<Character::Character*> charactersInGame;
	charactersInGame.push_back(playerCharacter);
	charactersInGame.push_back(enemyCharacter);
	currentGame->SetCharactersInMap(charactersInGame);
	currentGame->Attach(gameLogger);

	char userInput = ' ';
	while (userInput != 'E') {
		//Main gameplay loop
		system("cls");

		//Print map
		//currentMap->printMap();
		CampaignMap currentCampaignMap = currentGame->GetGameCampaign()->GetCurrentMap();
		Map::Map* map = currentGame->GetGameCampaign()->GetMap(currentCampaignMap.coorX, currentCampaignMap.coorY);
		map->printMap();

		currentGame->PrintActionMenu(playerCharacter);

		currentGame->GetUserSelection(userInput);

		currentGame->ProcessUserAction(userInput,playerCharacter);

		if (currentGame->GetActiveCharacter() != playerCharacter) {
			int x, y;
			currentMap->GetCharacterCoordinates(x, y, currentGame->GetActiveCharacter());

			CellActionInfo npcCellAction = currentGame->GetActiveCharacter()->DecideNPCAction(currentMap->getGrid(), x + 1, y + 1);
			currentGame->EndTurn(npcCellAction.actionName, npcCellAction.row, npcCellAction.col);
		}

		getchar();

		//currentGame->PrintActionMenu(playerCharacter);
	}
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
