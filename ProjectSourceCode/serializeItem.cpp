#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <regex>

#include "serializeItem.h"

using namespace std;
using namespace serializeItem;

namespace {
	vector<Item*> BuildItems(const vector<ItemRecord*>& _loadedRecords) {
		vector<Item*> loadedItems;

		for (int i = 0; i < (int)_loadedRecords.size(); i++)
		{
			Item* loadedItem = new Item(_loadedRecords[i]->itemId,
										_loadedRecords[i]->itemName,
										_loadedRecords[i]->enchantmentBonus,
										_loadedRecords[i]->itemtype,
										_loadedRecords[i]->enchantmentType,
										_loadedRecords[i]->weight);
			loadedItems.push_back(loadedItem);
		}

		return loadedItems;
	}

	vector<Item*> GetItems(ifstream* fileInput) {
		vector<ItemRecord*> itemRecords;

		while (!fileInput->eof()) {
			string nextLine = "";
			getline(*fileInput, nextLine);

			stringstream lineStream(nextLine);

			vector<string> segmentList;

			string segment = "";
			while (getline(lineStream, segment, ',')) {
				segmentList.push_back(segment);
			}

			ItemRecord* foundRecord = new ItemRecord;
			foundRecord->itemId = stoi(segmentList[0]);
			foundRecord->itemName = segmentList[1];
			foundRecord->enchantmentBonus = stoi(segmentList[2]);
			foundRecord->itemtype = (ItemType)stoi(segmentList[3]);
			foundRecord->enchantmentType = (CharacterStats)stoi(segmentList[4]);
			foundRecord->weight = stof(segmentList[5]);
			itemRecords.push_back(foundRecord);
		}

		vector<Item*> resultVector = BuildItems(itemRecords);

		return resultVector;
	}
	
	vector<ItemContainerRecord*> GetContainerRecords(ifstream* fileInput) {
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

			ItemContainerRecord* foundRecord = new ItemContainerRecord;
			foundRecord->containerId = stoi(segmentList[0]);
			foundRecord->itemName = segmentList[1];
			foundRecord->itemtype = (ItemType)stoi(segmentList[2]);
			foundRecord->weight = stof(segmentList[3]);
			foundRecord->capacity = stof(segmentList[4]);

			smatch match;

			regex numberRgx("[0-9]+");

			while (regex_search(segmentList[5], match, numberRgx)) {
				foundRecord->itemIDs.push_back(stoi(match.str()));

				segmentList[5] = match.suffix().str();
			}

			resultVector.push_back(foundRecord);
		}

		return resultVector;
	}

	vector<ItemRecord*> BuildItemRecords(const vector<Item*>& _items) {
		vector<ItemRecord*> resultList;

		for (int i = 0; i < (int)_items.size(); i++)
		{
			ItemRecord* newRecord = new ItemRecord;
			newRecord->itemId = _items[i]->GetItemId();
			newRecord->itemName = _items[i]->GetItemName();
			newRecord->enchantmentBonus = _items[i]->GetEnchantmentBonus();
			newRecord->itemtype = _items[i]->GetItemType();
			newRecord->enchantmentType = _items[i]->GetEnchantmentType();
			newRecord->weight = _items[i]->GetItemWeight();
			resultList.push_back(newRecord);
		}

		return resultList;
	}
	
	vector<ItemContainerRecord*> BuildContainerRecords(const vector<ItemContainer*>& _containers) {
		vector<ItemContainerRecord*> resultList;

		for (int i = 0; i < (int)_containers.size(); i++)
		{
			ItemContainerRecord* newRecord = new ItemContainerRecord;
			newRecord->containerId = _containers[i]->GetItemId();
			newRecord->itemName = _containers[i]->GetItemName();
			newRecord->itemtype = _containers[i]->GetItemType();
			newRecord->weight = _containers[i]->GetItemWeight();
			newRecord->capacity = _containers[i]->GetCapacity();

			vector<int> itemIDs;
			
			vector<Item> containerItems = _containers[i]->GetAllItems();
			for (int i = 0; i < (int)containerItems.size(); i++)
			{
				itemIDs.push_back(containerItems[i].GetItemId());
			}
			
			newRecord->itemIDs = itemIDs;
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
				/*_recordsToSave[i]->containerId <<
				"," <<*/
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
			vector<int> itemIDs = _recordsToSave[i]->itemIDs;

			int itemIDVectorSize = itemIDs.size();

			ostringstream itemIDsStringStream;
			itemIDsStringStream << "[";
			for (int i = 0; i < itemIDVectorSize; i++)
			{
				if (i + 1 == itemIDVectorSize) {
					itemIDsStringStream << to_string(itemIDs[i]);

					break;
				}

				itemIDsStringStream << to_string(itemIDs[i]) << ":";
			}
			itemIDsStringStream << "]";

			csvOutput << _recordsToSave[i]->containerId <<
				"," <<
				_recordsToSave[i]->itemName <<
				"," <<
				_recordsToSave[i]->itemtype <<
				"," <<
				_recordsToSave[i]->weight <<
				"," <<
				_recordsToSave[i]->capacity <<
				"," <<
				itemIDsStringStream.str() <<
				endl;
		}

		return csvOutput.str();
	}
}

namespace serializeItem {
	vector<Item*> LoadItems(const string& _fileURI) {
		ifstream itemInputStream(_fileURI);
		if (!itemInputStream.is_open()) {
			throw invalid_argument("Failed to open the file at: " + _fileURI);
		}

		vector<Item*> loadedItems = GetItems(&itemInputStream);

		itemInputStream.close();

		return loadedItems;
	}
	
	vector<ItemContainerRecord*> LoadItemContainerRecords(const string& _fileURI) {
		ifstream containerInputStream(_fileURI);
		if (!containerInputStream.is_open()) {
			throw invalid_argument("Failed to open the file at: " + _fileURI);
		}

		vector<ItemContainerRecord*> containerRecords = GetContainerRecords(&containerInputStream);

		containerInputStream.close();

		return containerRecords;
	}

	void SaveItems(const string& _fileURI, const vector<Item*>& _itemsToSave) {
		vector<ItemRecord*> recordsToSave = BuildItemRecords(_itemsToSave);

		string csvOutput = BuildItemCSVOutput(recordsToSave);

		ofstream itemOutputStream(_fileURI);
		itemOutputStream << csvOutput;

		itemOutputStream.close();
	}
	
	void SaveItemContainers(const string& _fileURI, const vector<ItemContainer*>& _containersToSave) {
		vector<ItemContainerRecord*> recordsToSave = BuildContainerRecords(_containersToSave);

		string csvOutput = BuildContainerCSVOutput(recordsToSave);

		ofstream itemOutputStream(_fileURI);
		itemOutputStream << csvOutput;

		itemOutputStream.close();
	}
}
