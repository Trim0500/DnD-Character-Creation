#include "Character.h"

Character::Character::Character(){
	//create random number generator
	std::random_device rd;

	//Baseline class for assignment 1 is FIGHTER
	//Generate level
	level.at(FIGHTER) = rd() % 20 + 1;
	//Set character_classes
	for (int i = 0 ; i<level.size();i++) {
		if (level[i] > 0) {
			character_class.set(i);
		}
	}
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//roll 3d6 for each ability score
		for (int j{ 0 }; j < 3; j++) {
			ability_scores[i] += rd() % 6 + 1;
		}
	}
	//Generate ability modifiers
	for (int i{ 0 }; i < 6; i++) {
		ability_modifiers[i] = std::floor(((float)(ability_scores[i] - 10) / 2));
	}
	//Generate hit points
	for (int i{ 0 }; i < Sum_Levels(); i++) {
		hit_points += (rd() % 10 + 1)+ability_modifiers[CONSTITUTION];
	}
	//Generate proficiency_bonus
	proficiency_bonus = std::ceil((double)(Sum_Levels() / 4.0)) + 1;
	//Generate damage_bonus(assume_unarmed by default therefor 0)
	damage_bonus = 0;
}

void Character::Character::Print_Character_Sheet()
{
	std::cout << std::right << std::setw(25) << "Name: " << name<<std::endl;
	std::cout << std::right << std::setw(25) << "Class: ";
	for (int i = 0; i < 11; i++) {
		if (character_class.test(i)) {
			std::cout << Get_Class_Name(i) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << std::right << std::setw(25) << "Level: " << Sum_Levels() << std::endl;
	std::cout << std::right << std::setw(25) << "Proficiency Bonus : " << proficiency_bonus << std::endl;
	std::cout << std::right << std::setw(25) << "Attack Bonus : " << Get_Attack_Bonus() << std::endl;
	std::cout << std::endl << std::right << std::setw(20) << "Ability Scores: " << std::endl << std::endl;
	std::cout << std::right << std::setw(20) << "Strength: " << std::left << std::setw(8) <<ability_scores[STRENGTH] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[STRENGTH] << std::endl;
	std::cout << std::right << std::setw(20) << "Dexterity: " << std::left << std::setw(8) << ability_scores[DEXTERITY] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[DEXTERITY] << std::endl;
	std::cout << std::right << std::setw(20) << "Constitution: " << std::left << std::setw(8) << ability_scores[CONSTITUTION] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[CONSTITUTION] << std::endl;
	std::cout << std::right << std::setw(20) << "Intelligence: " << std::left << std::setw(8) << ability_scores[INTELLIGENCE] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[INTELLIGENCE] << std::endl;
	std::cout << std::right << std::setw(20) << "Wisdom: " << std::left << std::setw(8) << ability_scores[WISDOM] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[WISDOM] << std::endl;
	std::cout << std::right << std::setw(20) << "Charisma: " << std::left << std::setw(8) << ability_scores[CHARISMA] << std::left << std::setw(1) << "Modifier: " << ability_modifiers[CHARISMA] << std::endl;

}

const int Character::Character::Sum_Levels()
{
	int sum{ 0 };
	for (int i{ 0 };i<level.size();i++) {
		sum += level[i];
	}
	return sum;
}

bool Character::Character::Levelup(Character_Class t_class)
{
	switch (t_class)
	{
	case BARBARIAN:
		return true;
		break;
	case BARD:
		return true;
		break;
	case CLERIC:
		return true;
		break;
	case DRUID:
		return true;
		break;
	case FIGHTER:
		return true;
		break;
	case MONK:
		return true;
		break;
	case PALADIN:
		return true;
		break;
	case RANGER:
		return true;
		break;
	case ROGUE:
		return true;
		break;
	case SORCERER:
		return true;
		break;
	case WIZARD:
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool Character::Character::Equipe_Item(item::Item* t_item) {

	/*if (inventory.GetItem(t_item->GetItemName()) == inventory.GetAllItems().end()) {
		std::cerr << "Could not find '" << t_item->GetItemName() << "' in inventory" << std::endl;
		return false;
	}*/

	item::Item* test = inventory.GetItem(t_item->GetItemName());
	if (test == nullptr) {
		cout << "Failed to find the item with name: " << t_item->GetItemName() << endl;
		
		return false;
	}

	switch (t_item->GetItemType())
	{
	case Hemlet:
		equipment_slots[helmet] = t_item;
		break;
	case Armor:
		equipment_slots[armor] = t_item;
		break;
	case Shield:
		equipment_slots[shield] = t_item;
		break;
	case Ring:
		equipment_slots[ring] = t_item;
		break;
	case Belt:
		equipment_slots[belt] = t_item;
		break;
	case Boots:
		equipment_slots[boots] = t_item;
		break;
	case Weapon:
		equipment_slots[weapon] = t_item;
		break;
	case Backpack:
		equipment_slots[bag] = t_item;
		break;
	default:
		std::cerr << "Could not equipe '" << t_item->GetItemName() << "'. No corresponding equipment slot" << std::endl;
		return false;
	}
	return true;
}

const int Character::Character::Get_Armour_Class()
{
	int nat_AC{ 0 };
	if (equipment_slots[Character::armor] == nullptr) {
		// if no armour is equipped
		nat_AC = 10 + ability_modifiers[DEXTERITY];
	}
	else{
		// get equipped armour AC
		nat_AC = equipment_slots[Character::armor]->GetEnchantmentBonus() + ability_modifiers[DEXTERITY];
	}
	for (auto &i : equipment_slots) {
		// add any AC enchantments from other equipped items
		if (i != nullptr && i->GetEnchantmentType() == ArmorClass && i->GetEnchantmentType() != ArmorClass) {
			nat_AC += i->GetEnchantmentBonus();
		}
	}
	return nat_AC;
}

const int Character::Character::calculate_proficiency()
{
	return proficiency_bonus = std::ceil((double)(Sum_Levels() / 4.0)) + 1;;
}

const int Character::Character::Get_Attack_Bonus()
{
	int attack_bonus = ability_modifiers[STRENGTH] + proficiency_bonus;;
	for (auto& i : equipment_slots) {
		// add any attack_bonus enchantments from other equipped items
		if (i != nullptr && i->GetEnchantmentType() == item::Weapon && i->GetEnchantmentType() != item::Weapon) {
			attack_bonus += i->GetEnchantmentBonus();
		}
	}
	return attack_bonus;
}

std::string Character::Character::Get_Class_Name(Character_Class t_class)
{
	switch (t_class)
	{
	case BARBARIAN:
		return "Barbarian";
	case BARD:
		return "Bard";
	case CLERIC:
		return "Cleric";
	case DRUID:
		return "Druid";
	case FIGHTER:
		return "Fighter";
	case MONK:
		return "Monk";
	case PALADIN:
		return "Paladin";
	case RANGER:
		return "Ranger";
	case ROGUE:
		return "Rogue";
	case SORCERER:
		return "Sorcerer";
	case WIZARD:
		return "Wizard";
	default:
		return "Unknown Class";
	}
	
}

std::string Character::Character::Get_Class_Name(int t_class)
{
	switch (t_class)
	{
	case 0:
		return "Barbarian";
	case 1:
		return "Bard";
	case 2:
		return "Cleric";
	case 3:
		return "Druid";
	case 4:
		return "Fighter";
	case 5:
		return "Monk";
	case 6:
		return "Paladin";
	case 7:
		return "Ranger";
	case 8:
		return "Rogue";
	case 9:
		return "Sorcerer";
	case 10:
		return "Wizard";
	default:
		return "Unknown Class";
	}

}

