// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Character.h"

using namespace CppUnit;

int main()
{
    std::cout << "Hello World!\n";
    Character::Character k;
    item::Item sword("sword", 1, item::Weapon, item::Strength);
    std::cout << k.Equipe_Item(&sword);

    // Get the top level suite from the registry
    //Test* suite = TestFactoryRegistry::getRegistry().makeTest();

    //// Adds the test to the list of test to run
    //TextUi::TestRunner runner;
    //runner.addTest(suite);

    //// Change the default outputter to a compiler error format outputter
    //runner.setOutputter(new CompilerOutputter(&runner.result(),
    //    std::cerr));
    //// Run the tests.
    //bool wasSucessful = runner.run();

    //getchar();

    //// Return error code 1 if the one of test failed.
    //return wasSucessful ? 0 : 1;
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
