#include <iostream>
#include <string>

#include "demoitem.h"
#include "item.h"
#include "itemcontainer.h"

// using namespace std;
using namespace item;
using namespace itemcontainer;

namespace {

}

namespace demoitem {
	void ShowCaseItemCreation() {
		ItemContainer* treasureChest = new ItemContainer("Silver Chest", TreasureChest, 250);

		int chestCapacity = treasureChest->GetCapacity();
		float totalChestItemWeight = 0.0;
		while (true)
		{
			if (totalChestItemWeight >= treasureChest->GetCapacity() / 2) {
				break;
			}

			Item* newItem = new Item();
			treasureChest->AddNewItem(newItem);
			totalChestItemWeight += newItem->GetItemWeight();
		}

		treasureChest->PrintItemVector();
	}
}
