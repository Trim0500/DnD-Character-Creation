#include "Character.h"

Character::Character::Character(){
	//create random number generator
	std::random_device rd;

	int t_num_levels = rd() % 20 + 1;
	//First level & class
	Levelup(Character_Class::Fighter);
	t_num_levels--;

	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//roll 3d6 for each ability score
		for (int j{ 0 }; j < 3; j++) {
			ability_scores[i] += rd() % 6 + 1;
		}
	}

	//Take Subsequent levels & classes
	bool t_level_taken{ false };
	for (int i{ 0 }; i < t_num_levels; i++) {

		while (!t_level_taken) {
			t_level_taken = Levelup(Character_Class::Fighter);
		}
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
	Levelup(t_class);
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//roll 3d6 for each ability score
		for (int j{ 0 }; j < 3; j++) {
			ability_scores[i] += rd() % 6 + 1;
		}
	}

	hit_points = max_hit_points;
}

Character::Character::Character(Character_Class t_class)
{
	std::random_device rd;

	//Set level & class
	Levelup(t_class);
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//roll 3d6 for each ability score
		for (int j{ 0 }; j < 3; j++) {
			ability_scores[i] += rd() % 6 + 1;
		}
	}

	hit_points = max_hit_points;
}

Character::Character::Character(std::string t_name, Character_Class t_class, const std::vector<int>& t_ability_scores)
{
	std::random_device rd;

	name = t_name;
	//Set level & class
	Levelup(t_class);
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		ability_scores[i] = t_ability_scores[i];
	}

	hit_points = max_hit_points;
}

void Character::Character::Print_Character_Sheet()
{
	std::cout << std::right << std::setw(25) << "Name: " << name<<" (ID: "<<ID()<<")"<<std::endl;
	std::cout << std::right << std::setw(25) << "Class: ";
	for (int i = 0; i < 11; i++) {
		if (character_class.test(i)) {
			std::cout << Get_Class_String(i) <<"("<<level[i]<< "), ";
		}
	}
	std::cout << std::endl;
	std::cout << std::right << std::setw(25) << "Level: " << Sum_Levels() << std::endl;
	std::cout << std::right << std::setw(25) << "HP: " << Hit_Points()<<"/"<<Max_Hit_Points() << std::endl;
	std::cout << std::right << std::setw(25) << "Proficiency Bonus: " << Proficiency_Bonus() << std::endl;
	std::cout << std::right << std::setw(25) << "Armour Class: " << Armour_Class() << std::endl;
	std::cout << std::right << std::setw(25) << "Attack Bonus: " << Attack_Bonus() << std::endl;
	std::cout << std::right << std::setw(25) << "Damage Bonus: " << Damage_Bonus() << std::endl;
	std::cout << std::string(100, '-') << std::endl;
	std::cout << std::right << std::setw(65) << "ABILITY SCORES" << std::endl;
	std::cout << std::right << std::setw(35) << "Ability" << " | " << std::left << std::setw(35) << "Score"
	<< " | " << std::left << std::setw(35) << "Modifier" << std::endl;
	std::cout << std::string(100, '-') << std::endl;
	std::cout << std::right << std::setw(35) << "Strength" <<" | "<< std::left << std::setw(35) << Ability_Score(Abilities_Stats::Strength)<<" | "<<std::right<<std::setw(2) << Modifier(Abilities_Stats::Strength) << std::endl;
	std::cout << std::right << std::setw(35) << "Dexterity" << " | " << std::left << std::setw(35) << Ability_Score(Abilities_Stats::Dexterity) <<" | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Dexterity) << std::endl;
	std::cout << std::right << std::setw(35) << "Constitution" << " | " << std::left << std::setw(35) << Ability_Score(Abilities_Stats::Constitution) <<" | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Constitution) << std::endl;
	std::cout << std::right << std::setw(35) << "Intelligence" << " | " << std::left << std::setw(35) << Ability_Score(Abilities_Stats::Intelligence) << " | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Intelligence) << std::endl;
	std::cout << std::right << std::setw(35) << "Wisdom" << " | " << std::left << std::setw(35) << Ability_Score(Abilities_Stats::Wisdom) << std::left <<" | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Wisdom) << std::endl;
	std::cout << std::right << std::setw(35) << "Charisma" << " | " << std::left << std::setw(35) << Ability_Score(Abilities_Stats::Charisma) << " | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Charisma) << std::endl;
	std::cout << std::string(100, '-') << std::endl;
	std::cout << std::right << std::setw(65) << "EQUIPPED ITEMS" << std::endl;
	std::cout << std::right << std::setw(35) << "Equipment slot"<<" | " << std::left<<std::setw(35) << " Name (ID)" 
	<< " | "  << std::left << std::setw(35) << "Enchantment" << std::endl;
	std::cout << std::string(100, '-') << std::endl;
	for (auto i : equipment_slots) {
		if (i.second != nullptr) {
			std::cout << std::right << std::setw(35) << Get_Equipment_Slot_String(i.first) << " | "
			<< std::left << std::setw(35) << i.second->GetItemName() << " (" << i.second->GetItemId() << ") " << std::right << std::setw(3) << " | ";
			if (i.second->GetEnchantmentBonus() > 0) {
				std::cout << "+";
			}
			std::cout << i.second->GetEnchantmentBonus()<<" ";
			std::cout << Get_Abilities_String(item_stat_TO_character_stat.at(i.second->GetEnchantmentType())) << std::endl;
		}
	}
	std::cout << std::string(100, '-') << std::endl;
	std::cout << std::right << std::setw(63) << "INVENTORY" << std::endl;
	std::cout << std::right << std::setw(35) << "Name(ID)" << " | " << std::left << std::setw(35) << "Type"
	<< " | " << std::left << std::setw(35) << "Enchantment" << std::endl;
	std::cout << std::string(100, '-') << std::endl;
	for (int i = 0; i < inventory.GetAllItems().size(); i++) {
		if (&inventory.GetAllItems().at(i) != nullptr) {
			std::cout << std::right << std::setw(35) << inventory.GetAllItems().at(i).GetItemName() << " | "
			<< std::left << std::setw(35) << Get_Item_Type_String(inventory.GetAllItems().at(i).GetItemType()) << " | ";
			if (inventory.GetAllItems().at(i).GetEnchantmentBonus() > 0) {
				std::cout << "+";
			}
			std::cout<< inventory.GetAllItems().at(i).GetEnchantmentBonus() << " " 
			<< Get_Abilities_String(item_stat_TO_character_stat.at(inventory.GetAllItems().at(i).GetEnchantmentType())) << std::endl;
		}
	}
	std::cout << std::string(100, '-') << std::endl;
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
	if (Sum_Levels() <= 20) {
		switch (t_class)
		{
		case Character_Class::Barbarian:
			return Levelup_Barbarian();
		case Character_Class::Bard:
			return Levelup_Bard();
		case Character_Class::Cleric:
			return Levelup_Cleric();
		case Character_Class::Druid:
			return Levelup_Druid();
		case Character_Class::Fighter:
			return Levelup_Fighter();
		case Character_Class::Monk:
			return Levelup_Monk();
		case Character_Class::Paladin:
			return Levelup_Paladin();
		case Character_Class::Ranger:
			return Levelup_Ranger();
		case Character_Class::Rogue:
			return Levelup_Rogue();
		case Character_Class::Sorcerer:
			return Levelup_Sorcerer();
		case Character_Class::Warlock:
			return Levelup_Warlock();
		case Character_Class::Wizard:
			return Levelup_Wizard();
		default:
			std::cerr << "Could not take a level in '" << Get_Class_String(t_class) << "'" << std::endl;
			return false;
		}
	}
	return false;
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

void Character::Character::Receive_Damage(int t_damage)
{
	if (t_damage >= hit_points) {
		hit_points = 0;
	}
	else {
		hit_points -= t_damage;
	}
}

void Character::Character::Receive_Healing(int t_heal)
{
	if (t_heal + max_hit_points >= hit_points) {
		hit_points = max_hit_points;
	}
	else {
		hit_points += t_heal;
	}
}

const bool Character::Character::Alive()
{
	if (hit_points <= 0) {
		return false;
	}
	else {
		return true;
	}
}

const int Character::Character::Modifier(Abilities_Stats t_ability)
{
	int modifier{ 0 };
	try {
		modifier = std::floor(((float)(Ability_Score(t_ability) - 10) / 2));
	}
	catch (std::exception& e) {
		std::cerr << &e << std::endl;
		return 0;
	}
	return modifier;
}

const int Character::Character::Ability_Score(Abilities_Stats t_ability)
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
		try {
			if (i.second != nullptr && item_stat_TO_character_stat.at(i.second->GetEnchantmentType()) == t_ability) {
				score += i.second->GetEnchantmentBonus();
			}
		}
		catch (std::exception &e) {
			std::cerr << &e << std::endl;
		}
	}
	return score;
}

const int Character::Character::Armour_Class()
{
	int armour_class = 10 + Modifier(Abilities_Stats::Dexterity);
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
	if (Modifier(Abilities_Stats::Dexterity) > Modifier(Abilities_Stats::Strength))
		t_mod = Modifier(Abilities_Stats::Dexterity);
	else{
		t_mod = Modifier(Abilities_Stats::Strength);
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
	int damage_bonus = Modifier(Abilities_Stats::Strength);
	for (auto& i : equipment_slots) {
		// add any damage_bonus enchantments from other equipped items
		if (i.second != nullptr && i.second->GetEnchantmentType() == CharacterStats::DamageBonus) {
			damage_bonus += i.second->GetEnchantmentBonus();
		}
	}
	return damage_bonus;
}

std::string Character::Character::Get_Abilities_String(Abilities_Stats t_abilities)
{
	switch (t_abilities)
	{
	case Abilities_Stats::Strength:
		return "Strength";
	case Abilities_Stats::Dexterity:
		return "Dexterity";
	case Abilities_Stats::Constitution:
		return "Constitution";
	case Abilities_Stats::Intelligence:
		return "Intelligence";
	case Abilities_Stats::Wisdom:
		return "Wisdom";
	case Abilities_Stats::Charisma:
		return "Charisma";
	case Abilities_Stats::ArmorClass:
		return "Armor Class";
	case Abilities_Stats::AttackBonus:
		return "Attack Bonus";
	case Abilities_Stats::DamageBonus:
		return "Damage Bonus";
	case Abilities_Stats::NA:
		return "NA";
	default:
		return "";
	}
}

std::string Character::Character::Get_Item_Type_String(item::ItemType t_type)
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

bool Character::Character::Is_Multi_Classed(Character_Class t_class)
{
	bool t_class_one{ false };
	if (Sum_Levels() == 0) {
		return false;
	}
	for (int i{ 0 }; i < level.size(); i++) {
		if (level.at(i) > 0 && (int)t_class != i) {
			return true;
		}
	}
	return false;
}

std::string Character::Character::Get_Class_String(Character_Class t_class)
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
	case Character_Class::Warlock:
		return "Warlock";
	case Character_Class::Wizard:
		return "Wizard";
	default:
		return "Unknown Class";
	}
	
}

std::string Character::Character::Get_Class_String(int t_class)
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
		return "Warlock";
	case 11:
		return "Wizard";
	default:
		return "Unknown Class";
	}

}

std::string Character::Character::Get_Equipment_Slot_String(Equipment_Slots t_slot)
{
	switch (t_slot)
	{
	case Equipment_Slots::Armor:
		return "Armour";
	case Equipment_Slots::Shield:
		return "Shield";
	case Equipment_Slots::Weapon:
		return "Weapon";
	case Equipment_Slots::Boots:
		return "Boots";
	case Equipment_Slots::Ring:
		return "Ring";
	case Equipment_Slots::Helmet:
		return "Helmet";
	case Equipment_Slots::Belt:
		return "Belt";
	case Equipment_Slots::Bag:
		return "Bag";
	default:
		return "NA";
	}

}

bool Character::Character::Levelup_Barbarian()
{
	Character_Class t_class = Character_Class::Barbarian;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Strength] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (12 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (12 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (7 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Bard()
{
	Character_Class t_class = Character_Class::Bard;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Charisma] >= 13 ) {
				//minimum requierments to multiclass pass!
				max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Cleric()
{
	Character_Class t_class = Character_Class::Cleric;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Wisdom] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Druid()
{
	Character_Class t_class = Character_Class::Druid;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Wisdom] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Fighter()
{
	Character_Class t_class = Character_Class::Fighter;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Strength] >= 13 || ability_scores[(int)Abilities_Stats::Dexterity] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (10 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (10 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Monk()
{
	Character_Class t_class = Character_Class::Monk;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Wisdom] >= 13 && ability_scores[(int)Abilities_Stats::Dexterity] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Paladin()
{
	Character_Class t_class = Character_Class::Paladin;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Charisma] >= 13 && ability_scores[(int)Abilities_Stats::Strength] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (10 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (10 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Ranger()
{
	Character_Class t_class = Character_Class::Ranger;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Dexterity] >= 13 && ability_scores[(int)Abilities_Stats::Wisdom] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (10 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (10 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Rogue()
{
	Character_Class t_class = Character_Class::Rogue;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Dexterity] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Sorcerer()
{
	Character_Class t_class = Character_Class::Sorcerer;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Charisma] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (4 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Warlock()
{
	Character_Class t_class = Character_Class::Warlock;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Charisma] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}

bool Character::Character::Levelup_Wizard()
{
	Character_Class t_class = Character_Class::Wizard;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Intelligence] >= 13) {
				//minimum requierments to multiclass pass!
				max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (4 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		return true;
	}
}
