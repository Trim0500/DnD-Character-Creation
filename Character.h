#pragma once

enum CharacterClass{
	barbarian,
	bard,
	cleric,
	druid,
	fighter,
	monk,
	paladin,
	ranger,
	rogue,
	sorcerer,
	wizard
};

enum Abilities {

	strength = 0,
	dexterity = 1,
	constitution = 2,
	intelligence = 3,
	wisdom = 4,
	charisma = 5,
};

struct EquipmentSlots {
	// Equiped items must be changed to the item data type
	int armor{};
	int shield{};
	int weapon{};
	int boots{};
	int ring{};
	int helmet{};
};

class Character {
public:
	Character(int level, CharacterClass c_class);

private:
	CharacterClass character_class{};
	int level;
	//Can use 'Ability' enum to index to the right ability score
	int ability_scores[6]{};
	int ability_modifiers[6]{};
	EquipmentSlots equipment_slots{};
	int hit_points{};
	int armour_class{}; 
	int attack_bonus{};
	int damage_bonus{};
};