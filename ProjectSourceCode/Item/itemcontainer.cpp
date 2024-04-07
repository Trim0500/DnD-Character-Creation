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

// using namespace std;
using namespace item;

namespace {
	
}

namespace itemcontainer {
	ItemContainer::ItemContainer(const std::string& _containerName, const int& _containerType, const float& _capacity) :
					Item(_containerName, 0, _containerType, 10, _containerType == 8 ? 5 : _containerType == 10 ? 25 : 0) {
		std::vector<Item> _items;
		items = _items;
		capacity = _capacity;
	}

	int ItemContainer::AddNewItem(Item* newItem) {
		if (GetItemType() == WornItems) {
			Item* foundItem = GetItem(newItem->GetItemType());
			if (foundItem != nullptr) {
				return -1;
			}
		}
		else if (newItem->GetItemWeight() + GetTotalItemWeight() >= capacity) {
			return -1;
		}

		items.push_back(*newItem);

		return 1;
	}

	void ItemContainer::RemoveItems(std::vector<Item*> _itemToRemove) {
		for (int i = 0; i < (int)_itemToRemove.size(); i++)
		{
			Item itemToRemove = *_itemToRemove[i];
			if (GetItem(itemToRemove.GetItemId()) != nullptr) {
				items.erase(std::remove(items.begin(), items.end(), itemToRemove), items.end());
			}
		}
	}

	float ItemContainer::GetTotalItemWeight() {
		float total = 0.0;

		for (size_t i = 0; i < items.size(); i++)
		{
			total += items[i].GetItemWeight();
		}

		return total;
	}

	Item* ItemContainer::GetItem(const int& _itemID) {
		for (size_t i = 0; i < items.size(); i++)
		{
			if (items[i].GetItemId() == _itemID) {
				return &items[i];
			}
		}

		return nullptr;
	}

	Item* ItemContainer::GetItem(const std::string& nameKey) {
		for (size_t i = 0; i < items.size(); i++)
		{
			if (items[i].GetItemName() == nameKey) {
				return &items[i];
			}
		}

		return nullptr;
	}

	Item* ItemContainer::GetItem(ItemType itemType) {
		for (size_t i = 0; i < items.size(); i++)
		{
			if (items[i].GetItemType() == itemType) {
				return &items[i];
			}
		}

		return nullptr;
	}

	std::vector<Item> ItemContainer::GetItemsByEnchantmentBonus(const int& enchantmentBonus) {
		std::vector<Item> resultVect;
		copy_if(items.begin(),
				items.end(),
				back_inserter(resultVect), 
			[enchantmentBonus](Item item) { return item.GetEnchantmentBonus() == enchantmentBonus; });

		return resultVect;
	}

	std::vector<Item> ItemContainer::GetItemsByItemType(const int& itemType) {
		std::vector<Item> resultVect;
		copy_if(items.begin(),
			items.end(),
			back_inserter(resultVect),
			[itemType](Item item) { return item.GetItemType() == (ItemType)itemType; });

		return resultVect;
	}

	std::vector<Item> ItemContainer::GetItemsByStat(const int& enchantmentType) {
		std::vector<Item> resultVect;
		copy_if(items.begin(),
			items.end(),
			back_inserter(resultVect),
			[enchantmentType](Item item) { return item.GetEnchantmentType() == (CharacterStats)enchantmentType; });

		return resultVect;
	}

	void ItemContainer::PrintItemVector() {
		std::cout << "\t\t" << this->GetItemName() << " Items Information" << std::endl;
		std::cout << "------------------------------------------" << std::endl << std::endl;
		
		for (int i = 0; i < items.size(); i++)
		{
			std::cout << i + 1
					<< ". "
					<< items[i].GetItemName()
					<< "\t"
					<< itemTypeStrings[items[i].GetItemType() - 1]
					<< "\t"
					<< std::to_string(items[i].GetEnchantmentBonus())
					<< "\t"
					<< statStrings[items[i].GetEnchantmentType()]
					<< "\t"
					<< std::to_string(items[i].GetItemWeight())
					<< "lbs"
					<< std::endl;
		}
		std::cout << "------------------------------------------" << std::endl;
	}
}
