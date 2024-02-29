#pragma once

#include <string>
#include <list>
#include <vector>

#include "item.h"
#include "itemcontainer.h"
//#include "Character.h"

using namespace std;
using namespace item;
using namespace itemcontainer;

namespace serializeItem {
	struct ItemRecord
	{
		int itemId;
		string itemName;
		int enchantmentBonus;
		ItemType itemtype;
		CharacterStats enchantmentType;
		float weight;
	};
	
	struct ItemContainerRecord
	{
		int containerId;
		string itemName;
		ItemType itemtype;
		float weight;
		float capacity;
		vector<int> itemIDs;
	};

	vector<Item*> LoadItems(const string&);

	vector<ItemContainerRecord*> LoadItemContainerRecords(const string& _fileURI);

	void SaveItems(const string&, const vector<Item*>&);
	
	void SaveItemContainers(const string&, const vector<ItemContainer*>&);
}
