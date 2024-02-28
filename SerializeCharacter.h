#pragma once

#include "Character.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace serializecharacter {

	struct CharacterRecord {
		int id;
		std::string name;
		std::vector<int> ability_scores = std::vector<int>(6, 0);
		std::vector<int> level = std::vector<int>(12, 0);
		int max_hit_points{ 0 };
		int hit_points{ 0 };
		std::vector<int> inventory_item_ids;
		std::vector<int> equipped_item_ids;
	};

	bool SaveCharacter(Character::Character* t_character);
	bool LoadCharacter(Character::Character& t_character, std::string_view filename);
}