// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Character.h"
#include "Dice.h"

using namespace std;
using namespace CppUnit;
using namespace item;
using namespace itemcontainer;

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
	
	/* Driver code here... */

	Character::Character* fighterCharacter = new Character::Character("Marty", Character::Character_Class::Fighter);

	ItemContainer* fighterInventory = &fighterCharacter->Inventory();

	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence);
	Item* armorObject = new Item("testArmor", 3, Armor, ArmorClass);
	Item* shieldObject = new Item("testShield", 2, Shield, ArmorClass);
	Item* ringObject = new Item("testRing", 1, Ring, Wisdom);
	Item* beltObject = new Item("testBelt", 1, Belt, Strength);
	Item* bootsObject = new Item("testBoots", 2, Boots, Dexterity);
	Item* weaponObject = new Item("testWeapon", 2, Weapon, AttackBonus);

	fighterInventory->AddNewItem(*helmetObject);
	fighterInventory->AddNewItem(*armorObject);
	fighterInventory->AddNewItem(*shieldObject);
	fighterInventory->AddNewItem(*ringObject);
	fighterInventory->AddNewItem(*beltObject);
	fighterInventory->AddNewItem(*bootsObject);
	fighterInventory->AddNewItem(*weaponObject);

	fighterCharacter->Equip_Item(armorObject);
	fighterCharacter->Equip_Item(beltObject);
	fighterCharacter->Equip_Item(bootsObject);

	int remainingBackpackCapacity = fighterInventory->GetCapacity() - fighterInventory->GetAllItems().size();
	for (int i = 0; i < remainingBackpackCapacity; i++)
	{
		Item* newItem = new Item();
		fighterInventory->AddNewItem(*newItem);
	}

	fighterCharacter->Print_Character_Sheet();

	cout << endl;

	ItemContainer* treasureChest = new ItemContainer("Silver Chest", TreasureChest, 5);

	int chestCapacity = treasureChest->GetCapacity();
	for (int i = 0; i < chestCapacity; i++)
	{
		Item* newItem = new Item();
		treasureChest->AddNewItem(*newItem);
	}

	treasureChest->PrintItemVector();

	cout << endl;

	Dice* dice = new Dice();
	int rollValue = dice->roll("4d20+4");
	cout << "Dice rolled: " << rollValue << endl;

	getchar();

	delete dice;
	fighterInventory->GetAllItems().clear();
	delete fighterCharacter;
	treasureChest->GetAllItems().clear();
	delete treasureChest;

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
