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
		max_hit_points += (rd() % 10 + 1)+Modifier(Abilities::Constitution);
	}
	hit_points = max_hit_points;

}

Character::Character::Character(const Character& t_character)
{
	name = t_character.name;
	for (int i = 0;i<level.size(); i++) {
		level.at(i) = t_character.level.at(i);
		if (level.at(i) > 0) {
			character_class.set(i);
		}
	}
	for (int i = 0; i < ability_scores.size(); i++) {
		ability_scores[i] = t_character.ability_scores[i];
	}
	max_hit_points = t_character.max_hit_points;
	hit_points = t_character.hit_points;
}

Character::Character::Character(std::string t_name, Character_Class t_class)
{
	std::random_device rd;

	name = t_name;
	//Set level
	level.at((int)t_class) = 1;
	//Set character_classes
	character_class.set((int)t_class);
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//roll 3d6 for each ability score
		for (int j{ 0 }; j < 3; j++) {
			ability_scores[i] += rd() % 6 + 1;
		}
	}
	//Generate hit points
	max_hit_points += (rd() % 10 + 1) + Modifier(Abilities::Constitution);
	hit_points = max_hit_points;
}

Character::Character::Character(Character_Class t_class)
{
	std::random_device rd;

	//Set level
	level.at((int)t_class) = 1;
	//Set character_classes
	character_class.set((int)t_class);
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//roll 3d6 for each ability score
		for (int j{ 0 }; j < 3; j++) {
			ability_scores[i] += rd() % 6 + 1;
		}
	}
	//Generate hit points
	max_hit_points = (rd() % 10 + 1) + Modifier(Abilities::Constitution);
	hit_points = max_hit_points;
}

Character::Character::Character(std::string t_name, Character_Class t_class, const std::vector<int>& t_ability_scores)
{
	std::random_device rd;

	name = t_name;
	//Set level
	level.at((int)t_class) = 1;
	//Set character_classes
	character_class.set((int)t_class);
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		ability_scores[i] = t_ability_scores[i];
	}
	//Generate hit points
	max_hit_points = (rd() % 10 + 1) + Modifier(Abilities::Constitution);
	hit_points = max_hit_points;
}

Character::Character::Character(std::string t_name, Character_Class t_class, const std::vector<int>& t_ability_scores, int t_max_hit_points)
{
	name = t_name;
	//Set level
	level.at((int)t_class) = 1;
	//Set character_classes
	character_class.set((int)t_class);
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		ability_scores[i] = t_ability_scores[i];
	}
	//Generate hit points
	max_hit_points = t_max_hit_points;
	hit_points = max_hit_points;
}

const std::string& Character::Character::Name(std::string t_name)
{
	name = t_name;
	return name;
}

void Character::Character::Print_Character_Sheet()
{
	std::cout << std::right << std::setw(25) << "Name: " << name<<" (ID: "<<ID()<<")"<<std::endl;
	std::cout << std::right << std::setw(25) << "Class: ";
	for (int i = 0; i < 11; i++) {
		if (character_class.test(i)) {
			std::cout << Get_Class_Name(i) <<"("<<level[i]<< "), ";
		}
	}
	std::cout << std::endl;
	std::cout << std::right << std::setw(25) << "Level: " << Sum_Levels() << std::endl;
	std::cout << std::right << std::setw(25) << "HP: " << Hit_Points()<<"/"<<Max_Hit_Points() << std::endl;
	std::cout << std::right << std::setw(25) << "Proficiency Bonus: " << Proficiency_Bonus() << std::endl;
	std::cout << std::right << std::setw(25) << "Armour Class: " << Armour_Class() << std::endl;
	std::cout << std::right << std::setw(25) << "Attack Bonus: " << Attack_Bonus() << std::endl;
	std::cout << std::right << std::setw(25) << "Damage Bonus: " << Damage_Bonus() << std::endl;
	std::cout << std::string(70, '-') << std::endl;
	std::cout << std::right << std::setw(40) << "ABILITY SCORES" << std::endl;
	std::cout << std::right << std::setw(20) << "Ability" << " | " << std::left << std::setw(20) << "Score"
	<< " | " << std::left << std::setw(20) << "Modifier" << std::endl;
	std::cout << std::string(70, '-') << std::endl;
	std::cout << std::right << std::setw(20) << "Strength" <<" | "<< std::left << std::setw(20) << Ability_Score(Abilities::Strength)<<" | "<<std::right<<std::setw(2) << Modifier(Abilities::Strength) << std::endl;
	std::cout << std::right << std::setw(20) << "Dexterity" << " | " << std::left << std::setw(20) << Ability_Score(Abilities::Dexterity) <<" | " << std::right << std::setw(2) << Modifier(Abilities::Dexterity) << std::endl;
	std::cout << std::right << std::setw(20) << "Constitution" << " | " << std::left << std::setw(20) << Ability_Score(Abilities::Constitution) <<" | " << std::right << std::setw(2) << Modifier(Abilities::Constitution) << std::endl;
	std::cout << std::right << std::setw(20) << "Intelligence" << " | " << std::left << std::setw(20) << Ability_Score(Abilities::Intelligence) << " | " << std::right << std::setw(2) << Modifier(Abilities::Intelligence) << std::endl;
	std::cout << std::right << std::setw(20) << "Wisdom" << " | " << std::left << std::setw(20) << Ability_Score(Abilities::Wisdom) << std::left <<" | " << std::right << std::setw(2) << Modifier(Abilities::Wisdom) << std::endl;
	std::cout << std::right << std::setw(20) << "Charisma" << " | " << std::left << std::setw(20) << Ability_Score(Abilities::Charisma) << " | " << std::right << std::setw(2) << Modifier(Abilities::Charisma) << std::endl;
	std::cout << std::string(70, '-') << std::endl;
	std::cout << std::right << std::setw(40) << "EQUIPPED ITEMS" << std::endl;
	std::cout << std::right << std::setw(20) << "Equipment slot"<<" | " << std::left<<std::setw(20) << "Name(ID)" 
	<< " | "  << std::left << std::setw(20) << "Enchantment" << std::endl;
	std::cout << std::string(70, '-') << std::endl;
	for (auto i : equipment_slots) {
		if (i.second != nullptr) {
			std::cout << std::right << std::setw(20) << Get_Equipment_Slot_Name(i.first) << " | "
			<< std::left << std::setw(20) << i.second->GetItemName() << std::right << std::setw(3) << " | ";
			if (i.second->GetEnchantmentBonus() > 0) {
				std::cout << "+";
			}
			std::cout << i.second->GetEnchantmentBonus()<<" ";
			std::cout << Get_Abilities_Name(item_stat_TO_character_abilities.at(i.second->GetEnchantmentType())) << std::endl;
		}
	}
	std::cout << std::string(70, '-') << std::endl;
	std::cout << std::right << std::setw(38) << "INVENTORY" << std::endl;
	std::cout << std::right << std::setw(20) << "Name(ID)" << " | " << std::left << std::setw(20) << "Type"
	<< " | " << std::left << std::setw(20) << "Enchantment" << std::endl;
	std::cout << std::string(70, '-') << std::endl;
	for (int i = 0; i < inventory.GetAllItems().size(); i++) {
		if (&inventory.GetAllItems().at(i) != nullptr) {
			std::cout << std::right << std::setw(20) << inventory.GetAllItems().at(i).GetItemName() << " | "
			<< std::left << std::setw(20) << Get_Item_Type_Name(inventory.GetAllItems().at(i).GetItemType()) << " | ";
			if (inventory.GetAllItems().at(i).GetEnchantmentBonus() > 0) {
				std::cout << "+";
			}
			std::cout<< inventory.GetAllItems().at(i).GetEnchantmentBonus() << " " 
			<< Get_Abilities_Name(item_stat_TO_character_abilities.at(inventory.GetAllItems().at(i).GetEnchantmentType())) << std::endl;
		}
	}
	std::cout << std::string(70, '-') << std::endl;
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
		equipment_slots[Equipment_Slots::Helmet] = t_item;
		break;
	case Armor:
		equipment_slots[Equipment_Slots::Armor] = t_item;
		break;
	case Shield:
		equipment_slots[Equipment_Slots::Shield] = t_item;
		break;
	case Ring:
		equipment_slots[Equipment_Slots::Ring] = t_item;
		break;
	case Belt:
		equipment_slots[Equipment_Slots::Belt] = t_item;
		break;
	case Boots:
		equipment_slots[Equipment_Slots::Boots] = t_item;
		break;
	case Weapon:
		equipment_slots[Equipment_Slots::Weapon] = t_item;
		break;
	case Backpack:
		equipment_slots[Equipment_Slots::Bag] = t_item;
		break;
	default:
		std::cerr << "Could not equipe '" << t_item->GetItemName() << "'. No corresponding equipment slot" << std::endl;
		return false;
	}
	return true;
}

void Character::Character::Unequip_Item(Equipment_Slots t_slot)
{
	equipment_slots.at(t_slot) = nullptr;
	return;
}

const int Character::Character::Modifier(Abilities t_ability)
{
	try {
		return std::floor(((float)(ability_scores[(int)t_ability] - 10) / 2));
	}
	catch (std::exception& e) {
		std::cerr << &e << std::endl;
		return 0;
	}
}

const int Character::Character::Ability_Score(Abilities t_ability)
{
	int score;
	try {
		score = ability_scores[(int)t_ability];
	}
	catch (std::exception& e) {
		std::cerr << &e << std::endl;
		return 0;
	}
	for (auto i : equipment_slots) {
		if (i.second != nullptr && item_stat_TO_character_abilities.at(i.second->GetEnchantmentType()) == t_ability) {
			score += i.second->GetEnchantmentBonus();
		}
	}
	return score;
}

const int Character::Character::Armour_Class()
{
	int armour_class = 10 + Modifier(Abilities::Dexterity);
	for (auto &i : equipment_slots) {
		// add any AC enchantments from other equipped items
		if (i.second != nullptr && i.second->GetEnchantmentType() == CharacterStats::ArmorClass) {
			armour_class += i.second->GetEnchantmentBonus();
		}
	}
	return armour_class;
}

const int Character::Character::Attack_Bonus()
{
	int t_mod{ 0 };
	if (Modifier(Abilities::Dexterity) > Modifier(Abilities::Strength))
		t_mod = Modifier(Abilities::Dexterity);
	else{
		t_mod = Modifier(Abilities::Strength);
	}
	int attack_bonus = t_mod + Proficiency_Bonus();
	for (auto& i : equipment_slots) {
		// add any attack_bonus enchantments from other equipped items
		if (i.second != nullptr && i.second->GetEnchantmentType() == CharacterStats::AttackBonus) {
			attack_bonus += i.second->GetEnchantmentBonus();
		}
	}
	return attack_bonus;
}

const int Character::Character::Proficiency_Bonus()
{
	return std::ceil((double)(Sum_Levels() / 4.0)) + 1;	
}

const int Character::Character::Damage_Bonus()
{
	int damage_bonus = Modifier(Abilities::Strength);
	for (auto& i : equipment_slots) {
		// add any damage_bonus enchantments from other equipped items
		if (i.second != nullptr && i.second->GetEnchantmentType() == CharacterStats::DamageBonus) {
			damage_bonus += i.second->GetEnchantmentBonus();
		}
	}
	return damage_bonus;
}

std::string Character::Character::Get_Abilities_Name(Abilities t_abilities)
{
	switch (t_abilities)
	{
	case Abilities::Strength:
		return "Strength";
	case Abilities::Dexterity:
		return "Dexterity";
	case Abilities::Constitution:
		return "Constitution";
	case Abilities::Intelligence:
		return "Intelligence";
	case Abilities::Wisdom:
		return "Wisdom";
	case Abilities::Charisma:
		return "Charisma";
	case Abilities::ArmorClass:
		return "Armor Class";
	case Abilities::AttackBonus:
		return "Attack Bonus";
	case Abilities::DamageBonus:
		return "Damage Bonus";
	case Abilities::NA:
		return "NA";
	default:
		return "";
	}
}

std::string Character::Character::Get_Item_Type_Name(item::ItemType t_type)
{
	switch (t_type)
	{
	case item::Helmet:
		return "Helmet";
	case item::Armor:
		return "Armor";
	case item::Shield:
		return "Shield";
	case item::Ring:
		return "Ring";
	case item::Belt:
		return "Belt";
	case item::Boots:
		return "Boots";
	case item::Weapon:
		return "Weapon";
	case item::Backpack:
		return "Backpack";
	case item::WornItems:
		return "WornItems";
	case item::TreasureChest:
		return "TreasureChest";
	default:
		return "NA";
	}
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
		return "NA";
		break;
	}

}



