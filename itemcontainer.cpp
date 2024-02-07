/*
* \file itemcontainer.cpp
* \brief Implementation file for the ItemContainer class
*
* This file puts in the implementation functions for the ItemContainer class
*/

#include <iostream>
#include <list>
#include <string>

#include "item.h"
#include "itemcontainer.h"

using namespace std;
using namespace item;

namespace {

}

namespace itemcontainer {
	ItemContainer::ItemContainer(const string& _containerName, const int& _containerType) {
		name = _containerName;
		containerType = (ItemContainerType)_containerType;
		list<Item> _items;
		items = _items;
	}

	Item ItemContainer::GetItem(string nameKey) {
		list<Item>::iterator it = find_if(items.begin(),
											items.end(),
											[nameKey](Item item)
											{
												return item.itemName == nameKey;
											});
		if (it != items.end()) {
			return *it;
		}
	}

	Item ItemContainer::GetItem(int itemType) {
		list<Item>::iterator it = find_if(items.begin(),
											items.end(),
											[itemType](Item item)
											{
												return item.itemType == itemType; 
											});
		if (it != items.end()) {
			return *it;
		}
	}

	list<Item> ItemContainer::GetItemsByEnchantmentBonus(int enchantmentBonus) {
		list<Item> resultList(items);

		for (int i = 0; i < items.size(); i++)
		{
			list<Item>::iterator it = find_if(resultList.begin(),
												resultList.end(),
												[enchantmentBonus](Item item)
												{
													return item.enchantmentBonus != enchantmentBonus;
												});
			if (it != resultList.end()) {
				resultList.remove(*it);
			}
		}

		return resultList;
	}

	list<Item> ItemContainer::GetItemsByItemType(int itemType) {
		list<Item> resultList(items);

		for (int i = 0; i < items.size(); i++)
		{
			list<Item>::iterator it = find_if(resultList.begin(),
												resultList.end(),
												[itemType](Item item)
												{
													return item.itemType != itemType;
												});
			if (it != resultList.end()) {
				resultList.remove(*it);
			}
		}

		return resultList;
	}

	list<Item> ItemContainer::GetItemsByStat(int enchantmentType) {
		list<Item> resultList(items);

		for (int i = 0; i < items.size(); i++)
		{
			list<Item>::iterator it = find_if(resultList.begin(),
												resultList.end(),
												[enchantmentType](Item item)
												{
													return item.enchantmentType != enchantmentType;
												});		
			if (it != resultList.end()) {
				resultList.remove(*it);
			}
		}

		return resultList;
	}
}
