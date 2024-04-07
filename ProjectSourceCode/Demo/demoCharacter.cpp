#include "demoCharacter.h"

void demo_character()
{
	Character::Character* demo_character = nullptr;
	bool leave = false;
	while (!leave)
	{
		std::vector<int> demo_attributes(6);
		std::string demo_name;

		std::cout << std::endl << "OPTIONS" << std::endl;
		std::cout << "1: Create random character" << std::endl;
		std::cout << "2: Create character" << std::endl;
		std::cout << "3: Leave Character feature demo" << std::endl;
		int user_input = 0;
		std::cin >> user_input;
		if(std::cin.fail()) {
			std::cin.clear();
			std::cout << "Bad entry.  Enter a NUMBER: ";
			return;
		}
		switch (user_input)
		{
		case 1:
			std::cout << "Creating a level 1 fighter character with random attributes..." << std::endl;
			demo_character = new Character::Character(Character::Character_Class::Fighter);
			std::cout << "Printing character sheet..." << std::endl;
			demo_character->Print_Character_Sheet();
			delete demo_character;
			break;
		case 2:
			std::cout << "Creating a level 1 fighter character..." << std::endl<<"Input desired ability scores..."<<std::endl;
			try {
				std::cout << "Strength: ";
				std::cin >> demo_attributes[0];
				std::cout << "Dexterity: ";
				std::cin >> demo_attributes[1];
				std::cout << "Constitution: ";
				std::cin >> demo_attributes[2];
				std::cout << "Intelligence: ";
				std::cin >> demo_attributes[3];
				std::cout << "Wisdom: ";
				std::cin >> demo_attributes[4];
				std::cout << "Charisma: ";
				std::cin >> demo_attributes[5];
			}
			catch (int e) {
				std::cerr << "Invalid input! Error '" << e << "'" << std::endl;
				return;
			}
			std::cout << "Input character name: ";
			std::cin >> demo_name;
			demo_character = new Character::Character(demo_name,Character::Character_Class::Fighter, demo_attributes,true);
			std::cout << "Printing character sheet..." << std::endl;
			demo_character->Print_Character_Sheet();
			delete demo_character;
			break;
		case 3:
			std::cout << "Later gator!" << std::endl;
			leave = true;
			break;
		default:
			std::cout << "Invalid input! '" << user_input << "' is not one of the available options!" << std::endl;
			return;
			break;
		}
	}
	return;

}