#include "Character.h"

Character::Character::Character(){
	//create random number generator
	std::random_device rd;
	//Generate level
	/*
	int num_levels = rd() % 20 + 1;
	while (num_levels > 1) {
		int _take = rd() % num_levels;
		num_levels -= _take;
		level.at(rd() % 10) += _take;
	}
	if (num_levels == 1) {
		level.at(rd() % 10) += 1;
	}
	*/
	level.at((int)Character_Class::Fighter) = rd() % 20 + 1;
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
	//Generate hit points
	for (int i{ 0 }; i < Sum_Levels(); i++) {
		max_hit_points += (rd() % 10 + 1)+Get_Modifier(Constitution);
	}
	hit_points = max_hit_points;
}

void Character::Character::Print_Character_Sheet()
{
	std::cout << std::right << std::setw(25) << "Name: " << name<<" (ID: "<<Get_ID()<<")"<<std::endl;
	std::cout << std::right << std::setw(25) << "Class: ";
	for (int i = 0; i < 11; i++) {
		if (character_class.test(i)) {
			std::cout << Get_Class_Name(i) <<"("<<level[i]<< "), ";
		}
	}
	std::cout << std::endl;
	std::cout << std::right << std::setw(25) << "Level: " << Sum_Levels() << std::endl;
	std::cout << std::right << std::setw(25) << "Proficiency Bonus : " << Get_Proficiency_Bonus() << std::endl;
	std::cout << std::right << std::setw(25) << "Armour Class : " << Get_Armour_Class() << std::endl;
	std::cout << std::right << std::setw(25) << "Attack Bonus : " << Get_Attack_Bonus() << std::endl;
	std::cout << std::right << std::setw(25) << "Damage Bonus : " << Get_Damage_Bonus() << std::endl;
	std::cout << std::endl << std::right << std::setw(20) << "Ability Scores: " << std::endl << std::endl;
	std::cout << std::right << std::setw(20) << "Strength: " << std::left << std::setw(8) <<ability_scores[Strength] << std::left << std::setw(1) << "Modifier: " << Get_Modifier(Strength) << std::endl;
	std::cout << std::right << std::setw(20) << "Dexterity: " << std::left << std::setw(8) << ability_scores[Dexterity] << std::left << std::setw(1) << "Modifier: " << Get_Modifier(Dexterity) << std::endl;
	std::cout << std::right << std::setw(20) << "Constitution: " << std::left << std::setw(8) << ability_scores[Constitution] << std::left << std::setw(1) << "Modifier: " << Get_Modifier(Constitution) << std::endl;
	std::cout << std::right << std::setw(20) << "Intelligence: " << std::left << std::setw(8) << ability_scores[Intelligence] << std::left << std::setw(1) << "Modifier: " << Get_Modifier(Intelligence) << std::endl;
	std::cout << std::right << std::setw(20) << "Wisdom: " << std::left << std::setw(8) << ability_scores[Wisdom] << std::left << std::setw(1) << "Modifier: " << Get_Modifier(Wisdom) << std::endl;
	std::cout << std::right << std::setw(20) << "Charisma: " << std::left << std::setw(8) << ability_scores[Charisma] << std::left << std::setw(1) << "Modifier: " << Get_Modifier(Charisma) << std::endl;
	std::cout << std::endl << std::right << std::setw(20) << "Equipment: " << std::endl << std::endl;
	for (int i = 0; i < equipment_slots.size(); i++) {
		if(equipment_slots[i] != nullptr)
			std::cout << std::right << std::setw(20)<< Get_Equipment_Slot_Name((Equipment_Slots)i)<<": " << equipment_slots[i]->GetItemName()
			<< std::endl;
	}

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
	case Character_Class::Barbarian:
		return true;
		break;
	case Character_Class::Bard:
		return true;
		break;
	case Character_Class::Cleric:
		return true;
		break;
	case Character_Class::Druid:
		return true;
		break;
	case Character_Class::Fighter:
		return true;
		break;
	case Character_Class::Monk:
		return true;
		break;
	case Character_Class::Paladin:
		return true;
		break;
	case Character_Class::Ranger:
		return true;
		break;
	case Character_Class::Rogue:
		return true;
		break;
	case Character_Class::Sorcerer:
		return true;
		break;
	case Character_Class::Wizard:
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool Character::Character::Equip_Item(item::Item* t_item) {

	if (inventory.GetItem(t_item->GetItemName()) == nullptr) {
		cout << "Could not equipe '" << t_item->GetItemName() << "'. Item could not be found in inventory" << endl;
		return false;
	}
	switch (t_item->GetItemType())
	{
	case Helmet:
		equipment_slots[(int)Equipment_Slots::Helmet] = t_item;
		break;
	case Armor:
		equipment_slots[(int)Equipment_Slots::Armor] = t_item;
		break;
	case Shield:
		equipment_slots[(int)Equipment_Slots::Shield] = t_item;
		break;
	case Ring:
		equipment_slots[(int)Equipment_Slots::Ring] = t_item;
		break;
	case Belt:
		equipment_slots[(int)Equipment_Slots::Belt] = t_item;
		break;
	case Boots:
		equipment_slots[(int)Equipment_Slots::Boots] = t_item;
		break;
	case Weapon:
		equipment_slots[(int)Equipment_Slots::Weapon] = t_item;
		break;
	case Backpack:
		equipment_slots[(int)Equipment_Slots::Bag] = t_item;
		break;
	default:
		std::cerr << "Could not equipe '" << t_item->GetItemName() << "'. No corresponding equipment slot" << std::endl;
		return false;
	}
	return true;
}


const int Character::Character::Get_Modifier(int t_ability)
{
	return std::floor(((float)(ability_scores[t_ability] - 10) / 2));
}

const int Character::Character::Get_Armour_Class()
{
	int armour_class = 10 + Get_Modifier(Dexterity);
	for (auto &i : equipment_slots) {
		// add any AC enchantments from other equipped items
		if (i != nullptr && i->GetEnchantmentType() == ArmorClass) {
			armour_class += i->GetEnchantmentBonus();
		}
	}
	return armour_class;
}

const int Character::Character::Get_Attack_Bonus()
{
	int t_mod{ 0 };
	if (Get_Modifier(Dexterity) > Get_Modifier(Strength))
		t_mod = Get_Modifier(Dexterity);
	else
	{
		t_mod = Get_Modifier(Strength);
	}
	int attack_bonus = t_mod + Get_Proficiency_Bonus();
	for (auto& i : equipment_slots) {
		// add any attack_bonus enchantments from other equipped items
		if (i != nullptr && i->GetEnchantmentType() == CharacterStats::AttackBonus) {
			attack_bonus += i->GetEnchantmentBonus();
		}
	}
	return attack_bonus;
}

const int Character::Character::Get_Proficiency_Bonus()
{
	return std::ceil((double)(Sum_Levels() / 4.0)) + 1;	
}

const int Character::Character::Get_Damage_Bonus()
{
	int damage_bonus = Get_Modifier(Strength);
	for (auto& i : equipment_slots) {
		// add any damage_bonus enchantments from other equipped items
		if (i != nullptr && i->GetEnchantmentType() == CharacterStats::DamageBonus) {
			damage_bonus += i->GetEnchantmentBonus();
		}
	}
	return damage_bonus;
}

std::string Character::Character::Get_Class_Name(Character_Class t_class)
{
	switch (t_class)
	{
	case Character_Class::Barbarian:
		return "Barbarian";
	case Character_Class::Bard:
		return "Bard";
	case Character_Class::Cleric:
		return "Cleric";
	case Character_Class::Druid:
		return "Druid";
	case Character_Class::Fighter:
		return "Fighter";
	case Character_Class::Monk:
		return "Monk";
	case Character_Class::Paladin:
		return "Paladin";
	case Character_Class::Ranger:
		return "Ranger";
	case Character_Class::Rogue:
		return "Rogue";
	case Character_Class::Sorcerer:
		return "Sorcerer";
	case Character_Class::Wizard:
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

std::string Character::Character::Get_Equipment_Slot_Name(Equipment_Slots t_slot)
{
	switch (t_slot)
	{
	case Equipment_Slots::Armor:
		return "Armour";
		break;
	case Equipment_Slots::Shield:
		return "Shield";
		break;
	case Equipment_Slots::Weapon:
		return "Weapon";
		break;
	case Equipment_Slots::Boots:
		return "Boots";
		break;
	case Equipment_Slots::Ring:
		return "Ring";
		break;
	case Equipment_Slots::Helmet:
		return "Helmet";
		break;
	case Equipment_Slots::Belt:
		return "Belt";
		break;
	case Equipment_Slots::Bag:
		return "Bag";
		break;
	default:
		break;
	}
	return "";
}



