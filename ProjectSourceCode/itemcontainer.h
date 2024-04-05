/*!
* \file itemcontainer.h
* \brief Header file for the ItemContainer class
* 
* @author Tristan Lafleur (40245238)
*
* This file puts in the forwrad declarations for the ItemContainer class
* 
* The game rules involved in the design of this file follow the d20 5e DnD rules. Therefore, three container types exist for the
*     gameworld and character, Backpack, Worn Items and Treasure Chests. Chests need to be place on the gameworld map to supply
*     the character with loot to pick and choose from and into their backpack which can then have items be taken out and equipped.
* 
* The design of this file is to implement the generation for item containers by way of including a list of items, retreiving
*     the items by certain metrics and adding in new ones. While the specifications mention that a container can hold any number
*     of items, this does not hold true for every type such as the case of Worn Items whereby only 7 can be used. Therefore, 
*     a capacity parameter is put in place to limit a container. Since containers are set in stone, no randomness is found for
*     these objects unlike the actual items. The container is a subclass as it ends up having many similar properties to items
*     and so allows the containers to be easier to maintain and extend later on.
* 
* The libraries used in this file would be string, vector and algorithm. The reasoning for it is that there is a need to provide
*     and interface to have a data structure that allows for automatic resizing as containers can be dynamically sized throughout
*     runtime and the items in the structure need to be found and retreived.
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "item.h"

// using namespace std;
using namespace item;

/*!
* \namespace itemcontainer
* \brief Namespace for the character item containers
*/
namespace itemcontainer {
	/*!
	* \class ItemContainer
	* \brief Class to abstract the different item containers
	* 
	* Class that is meant to abstract various kinds of item containers for a character.
	* These containers use a list from the std library to allow for any number of items to be added to a container.
	*/
	class ItemContainer : public Item {
		public:
			/*!
			* \fn ItemContainer
			* \brief Overloaded constructior for ItemContainer
			*/
			ItemContainer(const std::string&, const int&, const float&);

			float GetCapacity() { return capacity; };

			void SetWeightLimit(const float& _capacity) { capacity = _capacity; };

			int AddNewItem(Item*);

			std::vector<Item>& GetAllItems() { return items; };


			void SetItems(std::vector<Item> _items) { items = _items; };

			/*!
			* \fn RemoveItems
			* \brief Method to remove some items from a container
			* \param _itemToRemove Vector of Item instance pointers representing the items selected for removal
			*/
			void RemoveItems(std::vector<Item*>);

			float GetTotalItemWeight();

			Item* GetItem(const int&);

			/*!
			* \fn GetItem
			* \brief Overloaded method to find an item by name
			* 
			* Overloaded method that uses an item name to find the specific item in the list and return it.
			*/
			Item* GetItem(const std::string&);
			/*!
			* \fn GetItem
			* \brief Overloaded method to find an item by item type
			*
			* Overloaded method that uses an item type value (1-7) to find the specific item in the list and return it.
			*/
			Item* GetItem(ItemType);

			/*!
			* \fn GetItems
			* \brief Overloaded method to find a list of items via enchantment bonus
			* 
			* Overloaded member function that will use an enchantment bonus (1-5) to find the items that have that bonus.
			*/
			std::vector<Item> GetItemsByEnchantmentBonus(const int&);
			/*!
			* \fn GetItems
			* \brief Overloaded method to find a list of items via item type
			*
			* Overloaded member function that will use an item type enum value (1-7) to find the items that have that type.
			*/
			std::vector<Item> GetItemsByItemType(const int&);
			/*!
			* \fn GetItems
			* \brief Overloaded method to find a list of items via character stat
			*
			* Overloaded member function that will use a character stat enum value (0-8) to find the items that have that type.
			*/
			std::vector<Item> GetItemsByStat(const int&);
			/*!
			* \fn PrintItemVector
			* \brief Function to print out the info on individual items
			*/
			void PrintItemVector();
		private:
			/*!
			* \var capacity
			* \brief Integer that represents the carrying capacity (in lbs) for the container
			*/
			float capacity;

			/*!
			* \var items
			* \brief Vector of type Item that represents the containers item instances
			*/
			std::vector<Item> items;
	};
}