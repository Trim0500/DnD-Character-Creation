/*!
* \file serializeItem.cpp
* \brief File that implements the serialization of the Items and Containers present in a campaign.
* 
* \author Tristan Lafleur (40245238)
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <regex>

#include "serializeItem.h"

using namespace serializeItem;

namespace {
	/*!
	* \fn BuildItems
	* \brief Free function that takes a vector of ItemRecord instance pointers to make instances of Item into memory
	* 
	* \param _loadedRecords Vector of ItemRecord instance pointers that represent the retrieved CSV records
	* 
	* \return Vector of dynamically allocated Item instance pointers representing the saved items loaded into memory
	*/
	std::vector<Item*> BuildItems(const std::vector<ItemRecord*>& _loadedRecords) {
		std::vector<Item*> loadedItems;

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

	/*!
	* \fn GetItems
	* \brief Free function that takes a pointer to an opened file stream and reads the contents to create Item instances
	* 
	* \param fileInput Pointer to the opened file stream
	* 
	* \return Vector of dynamically allocated Item instance pointers representing the saved items loaded into memory
	*/
	std::vector<Item*> GetItems(std::ifstream* fileInput) {
		std::vector<ItemRecord*> itemRecords;

		while (!fileInput->eof()) {
			std::string nextLine = "";
			std::getline(*fileInput, nextLine);

			if (nextLine.empty()) {
				continue;
			}

			std::stringstream lineStream(nextLine);

			std::vector<std::string> segmentList;

			std::string segment = "";
			while (std::getline(lineStream, segment, ',')) {
				segmentList.push_back(segment);
			}

			ItemRecord* foundRecord = new ItemRecord;
			foundRecord->itemId = std::stoi(segmentList[0]);
			foundRecord->itemName = segmentList[1];
			foundRecord->enchantmentBonus = std::stoi(segmentList[2]);
			foundRecord->itemtype = (ItemType)std::stoi(segmentList[3]);
			foundRecord->enchantmentType = (CharacterStats)std::stoi(segmentList[4]);
			foundRecord->weight = std::stof(segmentList[5]);
			itemRecords.push_back(foundRecord);
		}

		std::vector<Item*> resultVector = BuildItems(itemRecords);

		return resultVector;
	}
	
	/*!
	* \fn GetContainerRecords
	* \brief Free function that takes a pointer to an opened file stream and reads the contents to create ItemContainerRecord instances
	* 
	* \param fileInput Pointer to the opened file stream
	* 
	* \return Vector of dynamically allocated ItemContainerRecord instance pointers representing the container records loaded into memory
	*/
	std::vector<ItemContainerRecord*> GetContainerRecords(std::ifstream* fileInput) {
		std::vector<ItemContainerRecord*> resultVector;

		while (!fileInput->eof()) {
			std::string nextLine = "";
			std::getline(*fileInput, nextLine);

			if (nextLine.empty()) {
				continue;
			}

			std::stringstream lineStream(nextLine);

			std::vector<std::string> segmentList;

			std::string segment = "";
			while (std::getline(lineStream, segment, ',')) {
				segmentList.push_back(segment);
			}

			ItemContainerRecord* foundRecord = new ItemContainerRecord;
			foundRecord->containerId = std::stoi(segmentList[0]);
			foundRecord->itemName = segmentList[1];
			foundRecord->itemtype = (ItemType)std::stoi(segmentList[2]);
			foundRecord->weight = std::stof(segmentList[3]);
			foundRecord->capacity = std::stof(segmentList[4]);

			std::smatch match;

			std::regex numberRgx("[0-9]+");

			while (regex_search(segmentList[5], match, numberRgx)) {
				foundRecord->itemIDs.push_back(std::stoi(match.str()));

				segmentList[5] = match.suffix().str();
			}

			resultVector.push_back(foundRecord);
		}

		return resultVector;
	}

	/*!
	* \fn BuildItemRecords
	* \brief Free function that takes a vector of Item instance pointers to build the records to save into a CSV
	* 
	* \param _items Vector of Item instance pointers that represent all the Item instances in memory to save
	* 
	* \return Vector of dynamically allocated ItemRecord instance pointers representing the item records to save
	*/
	std::vector<ItemRecord*> BuildItemRecords(const std::vector<Item*>& _items) {
		std::vector<ItemRecord*> resultList;

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
	
	/*!
	* \fn BuildContainerRecords
	* \brief Free function that takes a vector of ItemContainer instance pointers to build the records to save into a CSV
	* 
	* \param _containers Vector of ItemContainer instance pointers that represent all the ItemContainer instances in memory to save
	* 
	* \return Vector of dynamically allocated ItemContainerRecord instance pointers representing the container records to save
	*/
	std::vector<ItemContainerRecord*> BuildContainerRecords(const std::vector<ItemContainer*>& _containers) {
		std::vector<ItemContainerRecord*> resultList;

		for (int i = 0; i < (int)_containers.size(); i++)
		{
			ItemContainerRecord* newRecord = new ItemContainerRecord;
			newRecord->containerId = _containers[i]->GetItemId();
			newRecord->itemName = _containers[i]->GetItemName();
			newRecord->itemtype = _containers[i]->GetItemType();
			newRecord->weight = _containers[i]->GetItemWeight();
			newRecord->capacity = _containers[i]->GetCapacity();

			std::vector<int> itemIDs;
			
			std::vector<Item> containerItems = _containers[i]->GetAllItems();
			for (int i = 0; i < (int)containerItems.size(); i++)
			{
				itemIDs.push_back(containerItems[i].GetItemId());
			}
			
			newRecord->itemIDs = itemIDs;
			resultList.push_back(newRecord);
		}

		return resultList;
	}

	/*!
	* \fn BuildItemCSVOutput
	* \brief Free function that takes a vector of Itemrecord instance pointers to build the CSV output to write to a file
	* 
	* \param _recordsToSave Vector of ItemRecord instance pointers that represent all the item records derive an output from
	* 
	* \return String that represents the completed CSV output to write to a file
	*/
	std::string BuildItemCSVOutput(const std::vector<ItemRecord*>& _recordsToSave) {
		std::string outputResult;

		std::ostringstream csvOutput;
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
				std::endl;
		}

		return csvOutput.str();
	}
	
	/*!
	* \fn BuildContainerCSVOutput
	* \brief Free function that takes a vector of ItemContainerRecord instance pointers to build the CSV output to write to a file
	* 
	* \param _recordsToSave Vector of ItemContainerRecord instance pointers that represent all the container records derive an output from
	* 
	* \return String that represents the completed CSV output to write to a file
	*/
	std::string BuildContainerCSVOutput(const std::vector<ItemContainerRecord*>& _recordsToSave) {
		std::string outputResult;

		std::ostringstream csvOutput;
		for (int i = 0; i < (int)_recordsToSave.size(); i++)
		{
			std::vector<int> itemIDs = _recordsToSave[i]->itemIDs;

			int itemIDVectorSize = itemIDs.size();

			std::ostringstream itemIDsStringStream;
			itemIDsStringStream << "[";
			for (int i = 0; i < itemIDVectorSize; i++)
			{
				if (i + 1 == itemIDVectorSize) {
					itemIDsStringStream << std::to_string(itemIDs[i]);

					break;
				}

				itemIDsStringStream << std::to_string(itemIDs[i]) << ":";
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
				std::endl;
		}

		return csvOutput.str();
	}
}

namespace serializeItem {
	std::vector<Item*> LoadItems(const std::string& _fileURI) {
		std::ifstream itemInputStream(_fileURI);
		if (!itemInputStream.is_open()) {
			throw std::invalid_argument("Failed to open the file at: " + _fileURI);
		}

		std::vector<Item*> loadedItems = GetItems(&itemInputStream);

		itemInputStream.close();

		return loadedItems;
	}
	
	std::vector<ItemContainerRecord*> LoadItemContainerRecords(const std::string& _fileURI) {
		std::ifstream containerInputStream(_fileURI);
		if (!containerInputStream.is_open()) {
			throw std::invalid_argument("Failed to open the file at: " + _fileURI);
		}

		std::vector<ItemContainerRecord*> containerRecords = GetContainerRecords(&containerInputStream);

		containerInputStream.close();

		return containerRecords;
	}

	void SaveItems(const std::string& _fileURI, const std::vector<Item*>& _itemsToSave) {
		std::vector<ItemRecord*> recordsToSave = BuildItemRecords(_itemsToSave);

		std::string csvOutput = BuildItemCSVOutput(recordsToSave);

		std::ofstream itemOutputStream(_fileURI);
		itemOutputStream << csvOutput;

		itemOutputStream.close();
	}
	
	void SaveItemContainers(const std::string& _fileURI, const std::vector<ItemContainer*>& _containersToSave) {
		std::vector<ItemContainerRecord*> recordsToSave = BuildContainerRecords(_containersToSave);

		std::string csvOutput = BuildContainerCSVOutput(recordsToSave);

		std::ofstream itemOutputStream(_fileURI);
		itemOutputStream << csvOutput;

		itemOutputStream.close();
	}
}
