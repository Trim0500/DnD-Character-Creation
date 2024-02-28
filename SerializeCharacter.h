#pragma once

#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace serializecharacter {

	bool SaveCharacter(Character::Character* t_character);
	CharacterRecord LoadCharacter(const std::string& filename);
}