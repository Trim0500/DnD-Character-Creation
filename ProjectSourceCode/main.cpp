// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <filesystem>
#include "Character.h"
#include "item.h"
#include "SerializeCharacter.h"
#include "serializeItem.h"

using namespace CppUnit;

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
	
	getchar();
	Character::Character bob;
	item::Item test_item;
	item::Item test_item1;
	bob.Inventory().AddNewItem(&test_item);
	bob.Inventory().AddNewItem(&test_item1);
	bob.Equip_Item(&bob.Inventory().GetAllItems().at(0));
	serializecharacter::SaveCharacter(&bob, "");
	bob.Print_Character_Sheet();
	std::string charFilePath = serializecharacter::FindCharacterFile(34, "");
	Character::Character lucy = Character::Character(serializecharacter::LoadCharacter(charFilePath));
	lucy.Print_Character_Sheet();

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
