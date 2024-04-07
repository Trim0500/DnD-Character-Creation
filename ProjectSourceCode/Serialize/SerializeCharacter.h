#pragma once

#include "..\Character\Character.h"
#include "..\Item\item.h"
#include "..\Item\itemcontainer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

/*! \namespace serializecharacter
	*  \brief namespace used to encapsulate character serrialization
	*/
namespace serializecharacter {
	/*! \fn SaveCharacter(Character::Character* t_character,const std::string& t_path)
	*  \brief Saves a character entity to a CSV file
	*  \param t_character: pointer to character object to be saved
	*  \param t_path: std::filesystem::path type parameter to specify where there character is to be saved
	*/
	bool SaveCharacter(Character::Character* t_character,const std::string& t_path);
	/*! \fn LoadCharacter(const std::string& filename)
	*  \brief Loads a character entity from a CSV file into a CharacterRecord type struct
	*  \param filename: name of the file you would like to load
	*/
	CharacterRecord LoadCharacter(const std::string& filename);
	/*! \fn FindCharacterFile(int character_id, std::filesystem::path t_path)
	*  \brief Finds a character .csv file given an id and path to a directory
	*  \param character_id: id of the character to be queried 
	*  \param t_path: path to the sub-directory that you would like to query into (leave blank to query within the same directory as the executable)
	*/
	std::string FindCharacterFile(int character_id, std::filesystem::path t_path);
}