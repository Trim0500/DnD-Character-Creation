// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <filesystem>

#include "Character.h"
#include "Dice.h"
#include "Map.h"
#include "demoitem.h"
#include "DiceDemo.h"
#include "demoCharacter.h"
#include "serializeItem.h"

#define SAVED_ITEMS_URI "\\SavedItems\\SavedItems.csv"
#define SAVED_CONTAINERS_URI "\\SavedItems\\SavedItemContainers.csv"
#define SAVED_DUMMY_ITEMS_URI "\\SavedItems\\DUMMYSavedItems.csv"

using namespace std;
using namespace CppUnit;
using namespace item;
using namespace itemcontainer;
using namespace demoitem;
using namespace serializeItem;

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
	
	//ShowCaseItemCreation();

	//DiceDemo();

	//demo_character();

	//Map::Map* map = Map::Map::Create(); //  this function takes care of everything you need to create a map

	string currentPath = filesystem::current_path().string();

	ostringstream fullURI;
	fullURI << currentPath << SAVED_ITEMS_URI;

	cout << "The file is attempted to be found at: " << fullURI.str() << endl;

	try {
		vector<Item*> container1ItemRecords = LoadItems(fullURI.str());

		for (int i = 0; i < (int)container1ItemRecords.size(); i++)
		{
			cout << "Item Record info:" << endl;
			cout << "-----------------" << endl << endl;
			cout << "Item Id: " << container1ItemRecords[i]->GetItemId() << endl;
			cout << "Item Name: " << container1ItemRecords[i]->GetItemName() << endl;
			cout << "Enchantment Bonus: +" << container1ItemRecords[i]->GetEnchantmentBonus() << endl;
			cout << "Item Type: " << container1ItemRecords[i]->GetItemType() << endl;
			cout << "Enchantment Type: " << container1ItemRecords[i]->GetEnchantmentType() << endl;
			cout << "-----------------" << endl << endl;
		}
	}
	catch (invalid_argument exc) {
		cout << exc.what() << endl;
	}

	Item* backpackShieldItem = new Item("testBackpackShield", 4, Shield, ArmorClass, 12);
	Item* backpackBootsItem = new Item("testBackpackBoots", 4, Boots, Dexterity, 5);
		
	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence, 5);
	Item* armorObject = new Item("testArmor", 3, Armor, ArmorClass, 45);

	vector<Item*> testItemVector;
	testItemVector.push_back(backpackShieldItem);
	testItemVector.push_back(backpackBootsItem);
	testItemVector.push_back(helmetObject);
	testItemVector.push_back(armorObject);

	string currentPath2 = filesystem::current_path().string();

	ostringstream fullURI2;
	fullURI2 << currentPath2 << SAVED_DUMMY_ITEMS_URI;

	SaveItems(fullURI2.str(), testItemVector);

	string currentPath3 = filesystem::current_path().string();

	ostringstream fullURI3;
	fullURI3 << currentPath3 << SAVED_CONTAINERS_URI;

	getchar();

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
