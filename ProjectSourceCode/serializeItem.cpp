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
	
	vector<ItemContainerRecord*> ReadContainerRecords(ifstream* fileInput, const vector<int>& _IDVector) {
		vector<ItemContainerRecord*> resultVector;

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
				if (stoi(segmentList[1]) == _IDVector[i] || stoi(segmentList[2]) == _IDVector[i]) {
					foundID = true;

					break;
				}
			}

			if (!foundID) {
				continue;
			}

			ItemContainerRecord* foundRecord = new ItemContainerRecord;
			foundRecord->containerId = stoi(segmentList[0]);
			foundRecord->characterId = stoi(segmentList[1]);
			foundRecord->mapCellId = stoi(segmentList[2]);
			foundRecord->itemName = segmentList[3];
			foundRecord->enchantmentBonus = stoi(segmentList[4]);
			foundRecord->itemtype = (ItemType)stoi(segmentList[5]);
			foundRecord->enchantmentType = (CharacterStats)stoi(segmentList[6]);
			foundRecord->weight = stof(segmentList[7]);
			foundRecord->capacity = stof(segmentList[8]);
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
		ifstream containerInputStream(_fileURI);
		if (!containerInputStream.is_open()) {
			throw invalid_argument("Failed to open the file at: " + _fileURI);
		}

		vector<ItemContainerRecord*> containerRecords = ReadContainerRecords(&containerInputStream, _idVector);

		return containerRecords;
	}

	void SaveItems(vector<Item*> _itemsToSave) {

	}
	
	void SaveItemContainers(vector<ItemContainer*> _containersToSave) {

	}
}
