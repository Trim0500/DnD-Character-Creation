/*!
* \file serializeItem.h
* \brief File that has the forward declarations for the serialization of the Items and Containers present in a campaign.
* 
* \author Tristan Lafleur (40245238)
*/

#pragma once

#include <string>
#include <vector>

#include "..\Item\item.h"
#include "..\Item\itemcontainer.h"

using namespace item;
using namespace itemcontainer;

/*!
* \namespace serializeItem
* \brief Namespace to encapsulate the serialization functionality for the Items and Containers
*/
namespace serializeItem {
	/*!
	* \struct ItemRecord
	* \brief Struct that represents the format of the items that are saved into csv files
	*/
	struct ItemRecord
	{
		int itemId;
		std::string itemName;
		int enchantmentBonus;
		ItemType itemtype;
		CharacterStats enchantmentType;
		float weight;
	};
	
	/*!
	* \struct ItemContainerRecord
	* \brief Struct that represents the format of the containers that are saved into csv files.
	*/
	struct ItemContainerRecord
	{
		int containerId;
		std::string itemName;
		ItemType itemtype;
		float weight;
		float capacity;
		std::vector<int> itemIDs;
	};

	/*!
	* \fn LoadItems
	* \brief Free function that takes an abcolute path to a file to load all items that a user created for their campaigns
	* 
	* \param _fileURI String that represents the absolute file path to the CSV file that contains the saved item data. 
	* 
	* \return Vector of dynamically allocated Item instance pointers representing the saved items loaded into memory
	* 
	* \throw invalid_argument
	*/
	std::vector<Item*> LoadItems(const std::string&);

	/*!
	* \fn LoadItemContainerRecords
	* \brief Free function that takes an abcolute path to a file to load all containers that a user created for their campaigns
	* 
	* \param _fileURI String that represents the absolute file path to the CSV file that contains the saved item data. 
	* 
	* \return Vector of dynamically allocated ItemContainerRecord instance pointers representing the saved records loaded into memory.
	* 
	* \throw invalid_argument
	*/
	std::vector<ItemContainerRecord*> LoadItemContainerRecords(const std::string&);

	/*!
	* \fn SaveItems
	* \brief Free function that takes an abcolute path to a file and a collection of Item instance pointers in memory to save to a CSV file
	* 
	* \param _fileURI String that represents the absolute file path to the CSV file that contains the saved item data
	* \param _itemsToSave Vector of Item instance pointers that represent all the items in memory to save to a CSV file 
	*/
	void SaveItems(const std::string&, const std::vector<Item*>&);
	
	/*!
	* \fn SaveItemContainers
	* \brief Free function that takes an abcolute path to a file and a collection of ItemContainer instance pointers in memory to save to a CSV file
	* 
	* \param _fileURI String that represents the absolute file path to the CSV file that contains the saved item data
	* \param _containersToSave Vector of ItemContainer instance pointers that represent all the items in memory to save to a CSV file 
	*/
	void SaveItemContainers(const std::string&, const std::vector<ItemContainer*>&);
}
