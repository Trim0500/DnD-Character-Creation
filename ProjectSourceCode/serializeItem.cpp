#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "serializeItem.h"

using namespace std;
using namespace serializeItem;

namespace {
	vector<ItemRecord*> ReadItemRecords(ifstream* fileInput, const vector<int>& _IDVector) {
		vector<ItemRecord*> resultVector;

		while (!fileInput->eof()) {
			string nextLine = "";
			getline(*fileInput, nextLine);

			stringstream lineStream(nextLine);
			
			vector<string> segmentList;

			string segment = "";
			while (getline(lineStream, segment, ',')) {
				segmentList.push_back(segment);
			}

			bool foundID = false;

			for (int i = 0; i < _IDVector.size(); i++)
			{
				if (stoi(segmentList[1]) == _IDVector[i]) {
					foundID = true;

					break;
				}
			}

			if (!foundID) {
				continue;
			}

			ItemRecord* foundRecord = new ItemRecord;
			foundRecord->itemId = stoi(segmentList[0]);
			foundRecord->containerId = stoi(segmentList[1]);
			foundRecord->itemName = segmentList[2];
			foundRecord->enchantmentBonus = stoi(segmentList[3]);
			foundRecord->itemtype = (ItemType)stoi(segmentList[4]);
			foundRecord->enchantmentType = (CharacterStats)stoi(segmentList[5]);
			foundRecord->weight = stof(segmentList[6]);
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
