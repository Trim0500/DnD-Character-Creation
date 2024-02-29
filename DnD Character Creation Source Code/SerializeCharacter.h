#pragma once

#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

namespace serializecharacter {

	bool SaveCharacter(Character::Character* t_character,const std::string& t_path);
	CharacterRecord LoadCharacter(const std::string& filename);
	std::string FindCharacterFile(int character_id, std::filesystem::path t_path);
}