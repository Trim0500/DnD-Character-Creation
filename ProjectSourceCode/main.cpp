// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "game.h"
#include "../GUI/MainMenu.h"
#include "Wall.h"

using namespace CppUnit;
using namespace CampaignEditor;

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

	//MainMenu * m = new MainMenu();
	//m->show();

	//Fl::run();

	getchar();

	//create random machine
	std::random_device rd;

	//hardcode maps and campaing here
	//creare player Character
	Character::Character* playerCharacter = new Character::Character();
	//Create map
	Map::Map* currentMap = new Map::Map(20,20);
	//add player to map
	currentMap->setCharacter(9, 9, playerCharacter);
	//add walls to map
	for (int i = 0; i < currentMap->getRows(); i++) {
		currentMap->setCell(i, 0, new Wall);
	}
	for (int i = 0; i < currentMap->getRows(); i++) {
		currentMap->setCell(i, currentMap->getCols()-1, new Wall);
	}
	//add items to map
	//between 0 and 5 items
	int numOfItems = rd() % 5;
	for (int i = 0; i < numOfItems; i++) {
		currentMap->setCell(rd() % (currentMap->getRows()), rd() % (currentMap->getRows())+1, new item::Item());
	}
	//Create campaign
	campaign::Campaign* currentCampaign = new campaign::Campaign(1,1);
	//Add map to campaing
	currentCampaign->AddMapToCampaign(1, 1, *currentMap);
	//Create game instance	
	game::Game* currentGame = new game::Game();
	//set currentCampaiogn in currentGame
	currentGame->SetGameCampaign(currentCampaign);
	//Print map
	currentMap->printMap();
	//set player character 
	currentGame->SetActiveCharacter(playerCharacter);

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
