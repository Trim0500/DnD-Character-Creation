/*
* \file itemcontainer.h
* \brief Header file for the ItemContainer class
*
* This file puts in the forwrad declarations for the ItemContainer class
*/

#pragma once

#include <iostream>
#include <string>
#include <list>

#include "item.h"

using namespace std;
using namespace item;

/*
* \namespace itemcontainer
* \brief Namespace for the character item containers
*/
namespace itemcontainer {
	/*
	* \enum ItemContainerType
	* \brief Enum that represents the different item containers
	* 
	* An enum that identifies the different character or map item containers.
	*/
	enum ItemContainerType {
		Backback = 1,
		WornItems,
		TreasureChest
	};

	/*
	* \class ItemContainer
	* \brief Class to abstract the different item containers
	* 
	* Class that is meant to abstract various kinds of item containers for a character.
	* These containers use a list from the std library to allow for any number of items to be added to a container.
	*/
	class ItemContainer {
		public:
			/*
			* \fn ItemContainer
			* \brief Overloaded constructior for ItemContainer
			*/
			ItemContainer(const string&, const int&);
			string GetName() { return name; };
			ItemContainerType GetItemContainerType() { return containerType; };
			list<Item> GetAllItems() { return items; };
			/*
			* \fn GetItem
			* \brief Overloaded method to find an item by name
			* 
			* Overloaded method that uses an item name to find the specific item in the list and return it.
			*/
			Item GetItem(string);
			/*
			* \fn GetItem
			* \brief Overloaded method to find an item by item type
			*
			* Overloaded method that uses an item type value (1-7) to find the specific item in the list and return it.
			*/
			Item GetItem(int);
			/*
			* \fn GetItems
			* \brief Overloaded method to find a list of items via enchantment bonus
			* 
			* Overloaded member function that will use an enchantment bonus (1-5) to find the items that have that bonus.
			*/
			list<Item> GetItemsByEnchantmentBonus(int);
			/*
			* \fn GetItems
			* \brief Overloaded method to find a list of items via item type
			*
			* Overloaded member function that will use an item type enum value (1-7) to find the items that have that type.
			*/
			list<Item> GetItemsByItemType(int);
			/*
			* \fn GetItems
			* \brief Overloaded method to find a list of items via character stat
			*
			* Overloaded member function that will use a character stat enum value (1-9) to find the items that have that type.
			*/
			list<Item> GetItemsByStat(int);
			void AddNewItem(const Item& newItem) { items.push_back(newItem); };
		private:
			/*
			* A variable
			*/
			string name;
			/*
			* A variable
			*/
			ItemContainerType containerType;
			/*
			* A variable
			*/
			list<Item> items;
	};
}