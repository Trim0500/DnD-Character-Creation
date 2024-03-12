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
#include "../GUI/MainMenu.h"

using namespace std;
using namespace CppUnit;
using namespace item;
using namespace itemcontainer;
using namespace demoitem;
using namespace CampaignEditor;

int main()
{
	MainMenu * m = new MainMenu();
	m->show();
	return Fl::run();
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
