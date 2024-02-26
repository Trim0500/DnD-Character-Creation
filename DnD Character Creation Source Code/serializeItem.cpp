#include <iostream>

#include "serializeItem.h"

using namespace std;
using namespace serializeItem;

namespace {

}

namespace serializeItem {
	list<Item*> LoadItems(const string& _fileURI) {
		list<Item*> itemList;
		return itemList;
	}
	
	list<ItemContainer*> LoadItemContainers(const string& _fileURI) {
		list<ItemContainer*> containerList;
		return containerList;
	}

	void SaveItems(vector<Item*> _itemsToSave) {

	}
	
	void SaveItemContainers(vector<ItemContainer*> _containersToSave) {

	}
}
