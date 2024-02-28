#include <iostream>
#include <fstream>

#include "serializeItem.h"

using namespace std;
using namespace serializeItem;

namespace {
	vector<ItemRecord*> ReadItemRecords(ifstream* fileInput, const vector<int>& _IDVector) {
		vector<ItemRecord*> resultVector;

		while (!fileInput->eof()) {
			string itemIdText = "";
			string containerIdText = "";

			getline(*fileInput, itemIdText);
			getline(*fileInput, containerIdText);

			bool foundID = false;

			for (int i = 0; i < _IDVector.size(); i++)
			{
				if (stoi(containerIdText) == _IDVector[i]) {
					foundID = true;

					break;
				}
			}

			if (!foundID) {
				continue;
			}

			string itemName = "";
			string enchantmentBonusText = "";
			string itemTypeText = "";
			string enchantmentTypeText = "";
			string weightText = "";

			getline(*fileInput, itemName);
			getline(*fileInput, enchantmentBonusText);
			getline(*fileInput, itemTypeText);
			getline(*fileInput, enchantmentTypeText);
			getline(*fileInput, weightText);

			ItemRecord* foundRecord = new ItemRecord;
			foundRecord->itemId = stoi(itemIdText);
			foundRecord->containerId = stoi(containerIdText);
			foundRecord->itemName = itemName;
			foundRecord->enchantmentBonus = stoi(enchantmentBonusText);
			foundRecord->itemtype = (ItemType)stoi(itemTypeText);
			foundRecord->enchantmentType = (CharacterStats)stoi(enchantmentTypeText);
			foundRecord->weight = stof(weightText);
			resultVector.push_back(foundRecord);
		}

		return resultVector;
	}
}

namespace serializeItem {
	vector<ItemRecord*> LoadItemsByContainerIDs(const string& _fileURI, const vector<int>& _containerIDs) {
		ifstream itemInputStream(_fileURI);
		if (!itemInputStream.is_open()) {
			throw invalid_argument("Failed to open the file at: " + _fileURI);
		}

		vector<ItemRecord*> itemRecords = ReadItemRecords(&itemInputStream, _containerIDs);
		
		return itemRecords;
	}
	
	vector<ItemContainerRecord*> LoadItemContainersByIDs(const string& _fileURI, const vector<int>& _idVector) {
		vector<ItemContainerRecord*> containerList;
		return containerList;
	}

	void SaveItems(vector<Item*> _itemsToSave) {

	}
	
	void SaveItemContainers(vector<ItemContainer*> _containersToSave) {

	}
}
