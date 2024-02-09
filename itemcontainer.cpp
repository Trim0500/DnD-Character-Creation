/*
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
	/*
	* \fn FindItemByName
	* \brief Get an item from the item container via name
	*
	* Helper function to the ItemContainer class to find an item from an instance vector by item name.
	*
	* @param _itemVector The item instance vector to search from
	* @param _nameKey The name of the item to search against in the list
	*
	* @returns An iterator pointing to the item instance in the vector
	*/
	vector<Item>::iterator FindItemByName(vector<Item> _itemVector, const string& _nameKey) {
		return find_if(_itemVector.begin(), _itemVector.end(), [_nameKey](Item item) { return item.GetItemName() == _nameKey; });
	}

	/*
	* \fn FindItemByItemType
	* \brief Get an item from the item container via item type
	*
	* Helper function to the ItemContainer class to find an item from an instance vector by item type.
	*
	* @param _itemVector The item instance vector to search from
	* @param _itemTypeKey The item type value of the item to search against in the list
	*
	* @returns An iterator pointing to the item instance in the vector
	*/
	vector<Item>::iterator FindItemByItemType(vector<Item> _itemVector, const int& _itemTypeKey) {
		return find_if(_itemVector.begin(), _itemVector.end(), [_itemTypeKey](Item item) { return item.GetItemType() == (ItemType)_itemTypeKey; });
	}
}

namespace itemcontainer {
	ItemContainer::ItemContainer(const string& _containerName, const int& _containerType) : Item(_containerName, 0, _containerType, 10) {
		vector<Item> _items;
		items = _items;
	}

	Item ItemContainer::GetItem(const string& nameKey) {
		vector<Item>::iterator it = FindItemByName(items, nameKey);
		if (it != items.end()) {
			return *it;
		}
	}

	Item ItemContainer::GetItem(const int& itemType) {
		vector<Item>::iterator it = FindItemByItemType(items, itemType);
		if (it != items.end()) {
			return *it;
		}
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
}
