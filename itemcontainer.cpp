/*!
* \file itemcontainer.cpp
* \brief Implementation file for the ItemContainer class
*
* This file puts in the implementation functions for the ItemContainer class
*/

#include <iostream>
#include <string>
#include <algorithm>

#include "item.h"
#include "itemcontainer.h"

using namespace std;
using namespace item;

namespace {
	
}

namespace itemcontainer {
	ItemContainer::ItemContainer(const string& _containerName, const int& _containerType, const int& _capacity) :
					Item(_containerName, 0, _containerType, 10) {
		vector<Item> _items;
		items = _items;
		capacity = _capacity;
	}

	Item* ItemContainer::GetItem(const string& nameKey) {
		for (size_t i = 0; i < items.size(); i++)
		{
			if (items[i].GetItemName() == nameKey) {
				return &items[i];
			}
		}

		return nullptr;
	}

	Item* ItemContainer::GetItem(const int& itemType) {
		for (size_t i = 0; i < items.size(); i++)
		{
			if (items[i].GetItemType() == itemType) {
				return &items[i];
			}
		}

		return nullptr;
	}

	vector<Item> ItemContainer::GetItemsByEnchantmentBonus(const int& enchantmentBonus) {
		vector<Item> resultVect;
		copy_if(items.begin(),
				items.end(),
				back_inserter(resultVect), 
			[enchantmentBonus](Item item) { return item.GetEnchantmentBonus() == enchantmentBonus; });

		return resultVect;
	}

	vector<Item> ItemContainer::GetItemsByItemType(const int& itemType) {
		vector<Item> resultVect;
		copy_if(items.begin(),
			items.end(),
			back_inserter(resultVect),
			[itemType](Item item) { return item.GetItemType() == (ItemType)itemType; });

		return resultVect;
	}

	vector<Item> ItemContainer::GetItemsByStat(const int& enchantmentType) {
		vector<Item> resultVect;
		copy_if(items.begin(),
			items.end(),
			back_inserter(resultVect),
			[enchantmentType](Item item) { return item.GetEnchantmentType() == (CharacterStats)enchantmentType; });

		return resultVect;
	}

	void ItemContainer::PrintItemVector() {
		cout << "\t\t" << this->GetItemName() << " Items Information" << endl;
		cout << "------------------------------------------" << endl << endl;
		
		for (int i = 0; i < items.size(); i++)
		{
			cout << items[i].GetItemName()
					<< "\t"
					<< itemTypeStrings[items[i].GetItemType() - 1]
					<< "\t"
					<< to_string(items[i].GetEnchantmentBonus())
					<< "\t"
					<< statStrings[items[i].GetEnchantmentType()]
					<< endl;
		}
		cout << "------------------------------------------" << endl;
	}
}
