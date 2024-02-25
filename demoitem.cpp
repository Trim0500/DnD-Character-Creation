#include <iostream>
#include <string>

#include "demoitem.h"
#include "item.h"
#include "itemcontainer.h"

using namespace std;
using namespace item;
using namespace itemcontainer;

namespace {

}

namespace demoitem {
	void ShowCaseItemCreation() {
		cout << "-----     Item Creation     ------" << endl << endl;

		cout << "Please specify the name of the container";
		
		string containerName;
		cin >> containerName;

		cout << endl;
		cout << "Please specify the container type (Backpack = 8, Worn Items = 9, Treasure Chest = 10)";

		int containerType;
		string containerTypeInput;
		cin >> containerTypeInput;
		containerType = stoi(containerTypeInput);

		cout << endl;
		cout << "Please specify the container weight capacity (in lbs, max of 2 decimal points)";

		float containerCapacity;
		string containerCapacityInput;
		cin >> containerCapacityInput;
		containerCapacity = stoi(containerCapacityInput);

		ItemContainer newContainer(containerName, containerType, containerCapacity);

		char enterAgain;
		cout << "Create a new item? (y|Y or n|N)";
		cin >> enterAgain;

		while (tolower(enterAgain) != 'n') {
			cout << "Please specify the name of the item: ";
		
			string demoItemName;
			cin >> demoItemName;

			cout << endl;
			cout << "Please specify the enchantment bonus of the item (1 - 5): ";

			int bonus = 0;
			string bonusInput;
			cin >> bonusInput;
			bonus = stoi(bonusInput);

			cout << endl;
			cout << "Please specify the type of the item (Helmet = 1, Armor = 2, Shield = 3, Ring = 4, Belt = 5, Boots = 6, Weapon = 7): ";

			int itemType = 0;
			string itemTypeInput;
			cin >> itemTypeInput;
			itemType = stoi(itemTypeInput);

			cout << endl;
			cout << "Please specify the type of the enchantment (Strength = 0, Dexterity = 1, Constitution = 2, Intelligence = 3, Wisdom = 4, Charisma = 5, ArmorClass = 6, Attack = 7, Damage Bonus = 8): ";

			int enchantmentType = 0;
			string enchantmentTypeInput;
			cin >> enchantmentTypeInput;
			enchantmentType = stoi(enchantmentTypeInput);

			cout << endl;
			cout << "Please specify the item weight (in lbs, max of 2 decimal points): ";

			float weight = 0;
			string weightInput;
			cin >> weightInput;
			weight = stof(weightInput);

			Item newItem(demoItemName, bonus, itemType, enchantmentType, weight);

			int addResult = newContainer.AddNewItem(&newItem);
			if (addResult == -1) {
				cout << "Can't add the item to the container! It may be too heavy or the item can't be equipped!";
			}

			cout << endl;
			cout << "Create a new item? (y|Y or n|N)";
			cin >> enterAgain;
		}

		cout << endl;
		cout << "Here are the items that were added to the container" << endl;

		newContainer.PrintItemVector();
	}
}
