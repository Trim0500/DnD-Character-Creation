#pragma once

#include <string>
#include <list>
#include <vector>

#include "item.h"
#include "itemcontainer.h"
#include "Character.h"

using namespace std;
using namespace item;
using namespace itemcontainer;

namespace serializeItem {
	struct ItemRecord
	{
		int itemId;
		int containerId;
		string itemName;
		int enchantmentBonus;
		ItemType itemtype;
		CharacterStats enchantmentType;
		float weight;
	};
	
	struct ItemContainerRecord
	{
		int containerId;
		int characterId;
		int mapCellId;
		string itemName;
		int enchantmentBonus;
		ItemType itemtype;
		CharacterStats enchantmentType;
		float weight;
		float capacity;
	};

	vector<ItemRecord*> LoadItemsByContainerIDs(const string&, const vector<int>&);
	
	vector<ItemContainerRecord*> LoadItemContainersByIDs(const string&, const vector<int>&);

	void SaveItems(const string&, const vector<ItemContainer*>&);
	
	void SaveItemContainers(const string&, const vector<Character::Character*>&);
}
