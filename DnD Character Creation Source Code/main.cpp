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

#include "GUI/ItemEditor.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>


using namespace CppUnit;
using namespace item;
using namespace itemcontainer;
using namespace demoitem;
using namespace CampaignEditor;

int main(int argc, char** argv)
{
	ItemEditor* window = new ItemEditor(800, 640);
	// Fl_Box* box = new Fl_Box(20, 40, 300, 100, "Hello, World!");
	// box->box(FL_UP_BOX);
	// box->labelfont(FL_BOLD + FL_ITALIC);
	// box->labelsize(36);
	// box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show(argc, argv);
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
