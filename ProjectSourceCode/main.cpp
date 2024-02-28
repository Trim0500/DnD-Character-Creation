// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Character.h"
#include "Dice.h"
#include "Map.h"
#include "demoitem.h"
#include "DiceDemo.h"
#include "demoCharacter.h"
#include "serializeItem.h"

#define SAVED_ITEMS_URI "SavedItems\\SavedItems.csv"

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

	/*vector<int> dummy;
	dummy.push_back(1);

	try {
		vector<ItemRecord*> container1ItemRecords = LoadItemsByContainerIDs(SAVED_ITEMS_URI, dummy);

		for (int i = 0; i < (int)container1ItemRecords.size(); i++)
		{
			cout << "Item Record info:" << endl;
			cout << "Item Id: " << container1ItemRecords[i]->itemId << endl;
			cout << "Container Id: " << container1ItemRecords[i]->containerId << endl;
			cout << "Item Name: " << container1ItemRecords[i]->itemName << endl;
			cout << "Enchantment Bonus: +" << container1ItemRecords[i]->enchantmentBonus << endl;
			cout << "Item Type: " << container1ItemRecords[i]->itemtype << endl;
			cout << "Enchantment Type: " << container1ItemRecords[i]->enchantmentType << endl;
		}
	}
	catch (invalid_argument exc) {
		cout << "Failed to find the Item Records." << endl;
	}*/

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
