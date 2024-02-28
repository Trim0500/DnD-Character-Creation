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

	vector<ItemRecord*> BuildItemRecords(const vector<ItemContainer*>& _itemContainers) {
		vector<ItemRecord*> resultList;

		for (int i = 0; i < (int)_itemContainers.size(); i++)
		{
			vector<Item> _itemsToSave = _itemContainers[i]->GetAllItems();
			for (int j = 0; j < (int)_itemsToSave.size(); j++)
			{
				ItemRecord* newRecord = new ItemRecord;
				newRecord->itemId = _itemsToSave[j].GetItemId();
				newRecord->containerId = _itemContainers[i]->GetItemId();
				newRecord->itemName = _itemsToSave[j].GetItemName();
				newRecord->enchantmentBonus = _itemsToSave[j].GetEnchantmentBonus();
				newRecord->itemtype = _itemsToSave[j].GetItemType();
				newRecord->enchantmentType = _itemsToSave[j].GetEnchantmentType();
				newRecord->weight = _itemsToSave[j].GetItemWeight();
				resultList.push_back(newRecord);
			}
		}

		return resultList;
	}
	
	vector<ItemContainerRecord*> BuildContainerRecords(const vector<Character::Character*>& _characters) {
		vector<ItemContainerRecord*> resultList;

		for (int i = 0; i < (int)_characters.size(); i++)
		{
			ItemContainer containerToSave = _characters[i]->Inventory();

			ItemContainerRecord* newRecord = new ItemContainerRecord;
			newRecord->containerId = containerToSave.GetItemId();
			newRecord->characterId = _characters[i]->ID();
			newRecord->mapCellId = 0;
			newRecord->itemName = containerToSave.GetItemName();
			newRecord->enchantmentBonus = containerToSave.GetEnchantmentBonus();
			newRecord->itemtype = containerToSave.GetItemType();
			newRecord->enchantmentType = containerToSave.GetEnchantmentType();
			newRecord->weight = containerToSave.GetItemWeight();
			newRecord->capacity = containerToSave.GetCapacity();
			resultList.push_back(newRecord);
		}

		return resultList;
	}

	string BuildItemCSVOutput(const vector<ItemRecord*>& _recordsToSave) {
		string outputResult;

		ostringstream csvOutput;
		for (int i = 0; i < (int)_recordsToSave.size(); i++)
		{
			csvOutput << _recordsToSave[i]->itemId <<
				"," <<
				_recordsToSave[i]->containerId <<
				"," <<
				_recordsToSave[i]->itemName <<
				"," <<
				_recordsToSave[i]->enchantmentBonus <<
				"," <<
				_recordsToSave[i]->itemtype <<
				"," <<
				_recordsToSave[i]->enchantmentType <<
				"," <<
				_recordsToSave[i]->weight <<
				endl;
		}

		return csvOutput.str();
	}
	
	string BuildContainerCSVOutput(const vector<ItemContainerRecord*>& _recordsToSave) {
		string outputResult;

		ostringstream csvOutput;
		for (int i = 0; i < (int)_recordsToSave.size(); i++)
		{
			csvOutput << _recordsToSave[i]->containerId <<
				"," <<
				_recordsToSave[i]->characterId <<
				"," <<
				_recordsToSave[i]->mapCellId <<
				"," <<
				_recordsToSave[i]->itemName <<
				"," <<
				_recordsToSave[i]->enchantmentBonus <<
				"," <<
				_recordsToSave[i]->itemtype <<
				"," <<
				_recordsToSave[i]->enchantmentType <<
				"," <<
				_recordsToSave[i]->weight <<
				"," <<
				_recordsToSave[i]->capacity <<
				endl;
		}

		return csvOutput.str();
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

	void SaveItems(const string& _fileURI, const vector<ItemContainer*>& _associatedContainers) {
		vector<ItemRecord*> recordsToSave = BuildItemRecords(_associatedContainers);

		string csvOutput = BuildItemCSVOutput(recordsToSave);
		
		ofstream itemOutputStream(_fileURI);
		itemOutputStream << csvOutput;

		itemOutputStream.close();
	}
	
	void SaveItemContainers(const string& _fileURI, const vector<Character::Character*>& _associatedCharacters) {
		vector<ItemContainerRecord*> recordsToSave = BuildContainerRecords(_associatedCharacters);

		string csvOutput = BuildContainerCSVOutput(recordsToSave);

		ofstream itemOutputStream(_fileURI);
		itemOutputStream << csvOutput;

		itemOutputStream.close();
	}
}
