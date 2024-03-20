#include <sstream>
#include <string>

#include "Character.h"

Character::Character::Character(){
	//create random number generator
	std::random_device rd;

	int t_num_levels = rd() % 20 + 1;
	//First level & class
	Levelup(Character_Class::Fighter,true);
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
			t_level_taken = Levelup(Character_Class::Fighter,true);
		}
	}
	hit_points = max_hit_points;
	wornItems = this;
	isPlayerControlled = true;
	actionStrategy = new HumanPlayerStrategy();
}

Character::Character::Character(const Character& t_character) : id(t_character.id)
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
	wornItems = t_character.wornItems;
	isPlayerControlled = t_character.isPlayerControlled;
	actionStrategy = t_character.actionStrategy;
}

Character::Character::Character(std::string t_name, Character_Class t_class, bool _isPlayerControlled, CharacterActionStrategy* _actionStrategy)
{
	std::random_device rd;

	name = t_name;

	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//roll 3d6 for each ability score
		for (int j{ 0 }; j < 3; j++) {
			ability_scores[i] += rd() % 6 + 1;
		}
	}
	//Set level
	Levelup(t_class, true);
	hit_points = max_hit_points;
	wornItems = this;
	isPlayerControlled = _isPlayerControlled;
	actionStrategy = _actionStrategy;
}

Character::Character::Character(Character_Class t_class, bool _isPlayerControlled, CharacterActionStrategy* _actionStrategy)
{
	std::random_device rd;
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		//roll 3d6 for each ability score
		for (int j{ 0 }; j < 3; j++) {
			ability_scores[i] += rd() % 6 + 1;
		}
	}
	//Set level & class
	Levelup(t_class,true);


	hit_points = max_hit_points;
	wornItems = this;
	isPlayerControlled = _isPlayerControlled;
	actionStrategy = _actionStrategy;
}

Character::Character::Character(std::string t_name, Character_Class t_class, const std::vector<int>& t_ability_scores, bool t_average_hp, bool _isPlayerControlled, CharacterActionStrategy* _actionStrategy)
{
	std::random_device rd;

	name = t_name;
	//Generate ability scores
	for (int i{ 0 }; i < 6; i++) {
		ability_scores[i] = t_ability_scores[i];
	}
	//Set level & class
	Levelup(t_class, t_average_hp);


	hit_points = max_hit_points;
	wornItems = this;
	isPlayerControlled = _isPlayerControlled;
	actionStrategy = _actionStrategy;
}

Character::Character::Character(const serializecharacter::CharacterRecord& t_record) : id(t_record.id)
{
	this->name = t_record.name;
	for (int i{ 0 }; i < ability_scores.size(); i++) {
		this->ability_scores[i] = t_record.ability_scores[i];
	}
	for (int i{ 0 }; i < t_record.level.size(); i++) {
		for (int j{ 0 }; j < t_record.level.at(i); j++) {
			Levelup((Character_Class)i,true);
		}
	}
	this->hit_points = t_record.hit_points;
	this->max_hit_points = t_record.max_hit_points;
	std::vector<item::Item*> item_container_record = serializeItem::LoadItems(t_record.inventory_container_path);
	for (auto t_items : item_container_record) {
		this->Inventory().AddNewItem(t_items);
	}
	for (int i{ 0 }; i < t_record.equipped_item_ids.size(); i++) {
		bool found = false;
		for (int j{ 0 }; j < this->Inventory().GetAllItems().size(); j++) {
			if (this->Inventory().GetAllItems().at(j).GetItemId() == t_record.equipped_item_ids.at(i)) {
				this->Equip_Item_Decorator(&this->Inventory().GetAllItems().at(j));
				found = true;
			}
		}
	}

}


std::string Character::Character::Name(const std::string& t_name)
{
	name = t_name;
	this->notify();
	return name;
}

void Character::Character::Print_Character_Sheet()
{
	std::cout << std::right << std::setw(25) << "Name: " << name<<" (ID: "<<ID()<<")"<<std::endl;
	std::cout << std::right << std::setw(25) << "Class: ";
	for (int i = 0; i < 12; i++) {
		if (character_class.test(i)) {
			std::cout << Get_Class_String(i) <<"("<<level[i]<< "), ";
		}
	}
	std::cout << std::endl;
	std::cout << std::right << std::setw(25) << "Level: " << Sum_Levels() << std::endl;
	std::cout << std::right << std::setw(25) << "HP: " << Hit_Points()<<"/"<<Max_Hit_Points() << std::endl;
	std::cout << std::right << std::setw(25) << "Proficiency Bonus: " << Proficiency_Bonus() << std::endl;
	std::cout << std::right << std::setw(25) << "Armour Class: " << Armour_Class() << std::endl;
	std::cout << std::right << std::setw(25) << "Attack Bonus: ";
	for (int i{ 1 }; i <= Attacks_Per_Turn(); i++) {
		std::cout << Attack_Bonus(i);
		if (i != Attacks_Per_Turn()) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << std::right << std::setw(25) << "Damage Bonus: " << Damage_Bonus() << std::endl;
	std::cout << std::string(100, '-') << std::endl;
	std::cout << std::right << std::setw(65) << "ABILITY SCORES" << std::endl;
	std::cout << std::right << std::setw(35) << "Ability" << " | " << std::left << std::setw(35) << "Score"
	<< " | " << std::left << std::setw(35) << "Modifier" << std::endl;
	std::cout << std::string(100, '-') << std::endl;
	std::cout << std::right << std::setw(35) << "Strength" <<" | "<< std::left << std::setw(35) << Ability_Score_Bonused(Abilities_Stats::Strength)<<" | "<<std::right<<std::setw(2) << Modifier(Abilities_Stats::Strength) << std::endl;
	std::cout << std::right << std::setw(35) << "Dexterity" << " | " << std::left << std::setw(35) << Ability_Score_Bonused(Abilities_Stats::Dexterity) <<" | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Dexterity) << std::endl;
	std::cout << std::right << std::setw(35) << "Constitution" << " | " << std::left << std::setw(35) << Ability_Score_Bonused(Abilities_Stats::Constitution) <<" | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Constitution) << std::endl;
	std::cout << std::right << std::setw(35) << "Intelligence" << " | " << std::left << std::setw(35) << Ability_Score_Bonused(Abilities_Stats::Intelligence) << " | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Intelligence) << std::endl;
	std::cout << std::right << std::setw(35) << "Wisdom" << " | " << std::left << std::setw(35) << Ability_Score_Bonused(Abilities_Stats::Wisdom) << std::left <<" | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Wisdom) << std::endl;
	std::cout << std::right << std::setw(35) << "Charisma" << " | " << std::left << std::setw(35) << Ability_Score_Bonused(Abilities_Stats::Charisma) << " | " << std::right << std::setw(2) << Modifier(Abilities_Stats::Charisma) << std::endl;
	std::cout << std::string(100, '-') << std::endl;
	std::cout << std::right << std::setw(65) << "EQUIPPED ITEMS" << std::endl;
	std::cout << std::right << std::setw(35) << "Equipment slot"<<" | " << std::left<<std::setw(35) << " Name (ID)" 
	<< " | "  << std::left << std::setw(35) << "Enchantment" << std::endl;
	std::cout << std::string(100, '-') << std::endl;
	for (auto i : equipment_slots) {
		if (i.second != nullptr) {
			std::cout << std::right << std::setw(35) << Get_Equipment_Slot_String(i.first) << " | ";
			std::cout << std::left << std::setw(35) << i.second->GetItemName() <<" ("<<i.second->GetItemId()<<")";
			std::cout<< std::right << std::setw(3) << " | ";
			if (i.second->GetEnchantmentBonus() > 0) {
				std::cout << "+";
			}
			std::cout << i.second->GetEnchantmentBonus()<<" ";
			std::cout << Get_Abilities_String(item_stat_TO_character_stat.at(i.second->GetEnchantmentType())) << std::endl;
		}
	}
	std::cout << std::string(100, '-') << std::endl;
	std::cout << std::right << std::setw(63) << "INVENTORY" << std::endl;
	std::cout << std::right << std::setw(35) << "Name" << " | " << std::left << std::setw(35) << "Type"
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

bool Character::Character::Levelup(Character_Class t_class, bool t_average_hp)
{
	if (Sum_Levels() < 20) {
		switch (t_class)
		{
		case Character_Class::Barbarian:
			return Levelup_Barbarian(t_average_hp);
		case Character_Class::Bard:
			return Levelup_Bard(t_average_hp);
		case Character_Class::Cleric:
			return Levelup_Cleric(t_average_hp);
		case Character_Class::Druid:
			return Levelup_Druid(t_average_hp);
		case Character_Class::Fighter:
			return Levelup_Fighter(t_average_hp);
		case Character_Class::Monk:
			return Levelup_Monk(t_average_hp);
		case Character_Class::Paladin:
			return Levelup_Paladin(t_average_hp);
		case Character_Class::Ranger:
			return Levelup_Ranger(t_average_hp);
		case Character_Class::Rogue:
			return Levelup_Rogue(t_average_hp);
		case Character_Class::Sorcerer:
			return Levelup_Sorcerer(t_average_hp);
		case Character_Class::Warlock:
			return Levelup_Warlock(t_average_hp);
		case Character_Class::Wizard:
			return Levelup_Wizard(t_average_hp);
		default:
			std::cerr << "Could not take a level in '" << Get_Class_String(t_class) << "'" << std::endl;
			return false;
		}
	}
	return false;
}

bool Character::Character::Equip_Item(item::Item* t_item) {
	
	if (inventory.GetItem(t_item->GetItemName()) == nullptr) {
		std::cout << "Could not equipe '" << t_item->GetItemName() << "'. Item could not be found in inventory" << std::endl;
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
	this->notify();
	return true;
}

void Character::Character::Equip_Item_Decorator(item::Item* _itemToEquip) {
	if (inventory.GetItem(_itemToEquip->GetItemId()) == nullptr) {
		throw std::invalid_argument("[Character/Equip_Item_Decorator] -- Failed to find the item in the inventory to equip");
	}

	std::vector<AbstractComponent*> decoratorList = wornItems->GetDecoratorList();
	int decoratorListSize = decoratorList.size();
	if (decoratorListSize == 7) {
		throw std::out_of_range("[Character/Equip_Item_Decorator] -- Can't equip another item!");
	}

	for (int i = 0; i < (int)decoratorList.size(); ++i)
	{
		Item* equippedItem = dynamic_cast<Item*>(decoratorList.at(i));

		if (_itemToEquip->GetItemType() == equippedItem->GetItemType()) {
			std::ostringstream excMessage;
			excMessage << "[Character/Equip_Item_Decorator] -- Can't equip another " << itemTypeStrings[_itemToEquip->GetItemType() - 1];
			throw std::invalid_argument(excMessage.str().c_str());
		}
	}
	

	_itemToEquip->SetWrappee(wornItems);	
	wornItems = _itemToEquip;
}

void Character::Character::Unequip_Item(Equipment_Slots t_slot)
{
	equipment_slots.at(t_slot) = nullptr;
	this->notify();
}

void Character::Character::Unequip_Item_Decorator(item::Item* _itemToRemove) {
	std::vector<AbstractComponent*> decoratorList = wornItems->GetDecoratorList();
	
	wornItems = this;

	for (int i = 0; i < (int)decoratorList.size(); ++i)
	{
		Item* decoratorItem = dynamic_cast<Item*>(decoratorList.at(i));
		if (_itemToRemove->GetItemId() == decoratorItem->GetItemId()) {
			_itemToRemove->SetWrappee(nullptr);

			continue;
		}

		decoratorItem->SetWrappee(wornItems);	
		wornItems = decoratorItem;
	}
}

void Character::Character::Receive_Damage(int t_damage)
{
	if (t_damage >= hit_points) {
		hit_points = 0;
	}
	else {
		hit_points -= t_damage;
	}
	this->notify();
}

void Character::Character::Receive_Healing(int t_heal)
{
	if (t_heal + hit_points >= max_hit_points) {
		hit_points = max_hit_points;
	}
	else {
		hit_points += t_heal;
	}
	this->notify();
}

const bool Character::Character::Is_Alive()
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
		modifier = std::floor(((float)(Ability_Score_Bonused(t_ability) - 10) / 2));
	}
	catch (std::exception& e) {
		std::cerr << &e << std::endl;
		return 0;
	}
	return modifier;
}

int Character::Character::Ability_Score_Natural(int t_ability, int t_attack_number)
{
	int score;
	try {
		if (t_ability > 5) {
			switch (t_ability) {
				case 6:
					score = 10;

					break;
				case 7:
					if (t_attack_number == 1) {
						score = Sum_Levels();
					}
					else {
						score = Sum_Levels() - ((t_attack_number - 1) * 5);
					}

					break;
				case 8:
					/*
					COMP345-A3-64:
						Returning 0 as a baseline for dmg here because it is actually just the
						strength stat w/modifiers for both strength and dmg bonus. Therefore, a call with the paraemter for dmg
						is simply decorated if worn items match the type, and add that to a call for strength.
					*/
					score = 0;

					break;
			}
		}
		else {
			score = ability_scores[(int)t_ability];
		}
	}
	catch (std::exception& e) {
		std::cerr << &e << std::endl;
		return 0;
	}
	return score;
}

const int Character::Character::Ability_Score_Bonused(Abilities_Stats t_ability)
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
		catch (std::exception& e) {
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

const int Character::Character::Attack_Bonus(int t_attack_number)
{
	//Bonus for an attack number that character does not have yet
	if (t_attack_number > Attacks_Per_Turn()) {
		return 0;
	}
	int attack_bonus = 0;
	if (t_attack_number == 1) {
		attack_bonus = Sum_Levels();
	}
	else {
		attack_bonus = Sum_Levels() - ((t_attack_number - 1) * 5);;
	}
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

const int Character::Character::Attacks_Per_Turn()
{
	int sum_level = 0;
	for (auto i : level) {
		sum_level += i;
	}
	int num_attacks = std::ceil((double)(sum_level / 5.0));
	return num_attacks;
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

int Character::Character::setAttribute(Abilities_Stats t_ability, int t_val)
{
	this->ability_scores.at((int)t_ability) = t_val;
	this->notify();
	return t_val;
}

int Character::Character::setMaxHitPoints(int t_val)
{
	this->max_hit_points = t_val;
	this->notify();
	return t_val;
}

int Character::Character::setHitPoints(int t_val)
{
	this->hit_points = t_val;
	this->notify();
	return t_val;
}

int Character::Character::setLevel(Character_Class t_class, int t_val)
{
	this->level.at((int)t_class) = t_val;
	this->notify();
	return t_val;
}

bool Character::Character::Levelup_Barbarian(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!"<<std::endl;
				std::cout << "Minimum multi-class requirement: "<<"Strength >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (12 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (7 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Bard(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<<"Charisma >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Cleric(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: " << "Wisdom >= 13"<< std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Druid(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<< "Wisdom >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Fighter(bool t_average_hp)
{
	Character_Class t_class = Character_Class::Fighter;
	//If first level of class
	if (level.at((int)t_class) == 0) {
		//If first level of multi-class
		if (Is_Multi_Classed(t_class)) {
			if (ability_scores[(int)Abilities_Stats::Strength] >= 13 || ability_scores[(int)Abilities_Stats::Dexterity] >= 13) {
				//minimum requierments to multiclass pass!
				int base_hp_increase = 10;
				if (!t_average_hp) {
					base_hp_increase = Dice::roll("1d10");
				}
				max_hit_points += (base_hp_increase + Modifier(Abilities_Stats::Constitution));
				level.at((int)t_class) = 1;
				character_class.set((int)t_class);
				hit_points = max_hit_points;
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<< "Strength >= 13 OR Dexterity >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			int base_hp_increase = 10;
			if (!t_average_hp) {
				base_hp_increase = Dice::roll("1d10");
			}
			max_hit_points += (base_hp_increase + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		int base_hp_increase = 5;
		if (!t_average_hp) {
			base_hp_increase = Dice::roll("1d10");
		}
		max_hit_points += (base_hp_increase + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Monk(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<<"Wisdom >= 13 AND Dexterity >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Paladin(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<< "Charisma >= 13 AND Strength >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (10 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Ranger(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<<"Dexterity >= 13 AND Wisdom >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (10 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Rogue(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<<"Dexterity >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Sorcerer(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<<"Charisma >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (4 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Warlock(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<<"Charisma >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (8 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (5 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

bool Character::Character::Levelup_Wizard(bool t_average_hp)
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
				this->notify();
				return true;
			}
			else
			{
				//Don't meet minimum requierments to multiclass
				std::cout << "Could not take a level in " << Get_Class_String(t_class) << "!" << std::endl;
				std::cout << "Minimum multi-class requirement: "<<"Intelligence >= 13" << std::endl;
				return false;
			}
		}
		else {
			//First level
			max_hit_points += (6 + Modifier(Abilities_Stats::Constitution));
			level.at((int)t_class) = 1;
			character_class.set((int)t_class);
			hit_points = max_hit_points;
			this->notify();
			return true;
		}
	}
	else {
		//Not first level in this class! Taking an additional one
		level.at((int)t_class) += 1;
		max_hit_points += (4 + Modifier(Abilities_Stats::Constitution));
		hit_points = max_hit_points;
		this->notify();
		return true;
	}
}

Character::Character characterBuilder::Build_Fighter(characterBuilder::Fighter_Sub_Class t_subclass)
{
	std::vector<int> generated_attributes = std::vector<int>(6);
	for (int i{ 0 }; i < 6;i++) {
		generated_attributes.at(i) = Dice::roll("3d6");
	}
	std::sort(generated_attributes.begin(), generated_attributes.end());
	std::vector<int> assigned_attributes = std::vector<int>(6);
	std::string assigned_name = "";
	switch (t_subclass)
	{
	case characterBuilder::Fighter_Sub_Class::Bully:
	{
		assigned_attributes.at((int)Character::Abilities_Stats::Strength) = generated_attributes.at(5);
		assigned_attributes.at((int)Character::Abilities_Stats::Constitution) = generated_attributes.at(4);
		assigned_attributes.at((int)Character::Abilities_Stats::Dexterity) = generated_attributes.at(3);
		assigned_attributes.at((int)Character::Abilities_Stats::Intelligence) = generated_attributes.at(2);
		assigned_attributes.at((int)Character::Abilities_Stats::Charisma) = generated_attributes.at(1);
		assigned_attributes.at((int)Character::Abilities_Stats::Wisdom) = generated_attributes.at(0);
		assigned_name = "Bully";
	}break;
	case characterBuilder::Fighter_Sub_Class::Nimble:
	{
		assigned_attributes.at((int)Character::Abilities_Stats::Dexterity) = generated_attributes.at(5);
		assigned_attributes.at((int)Character::Abilities_Stats::Constitution) = generated_attributes.at(4);
		assigned_attributes.at((int)Character::Abilities_Stats::Strength) = generated_attributes.at(3);
		assigned_attributes.at((int)Character::Abilities_Stats::Intelligence) = generated_attributes.at(2);
		assigned_attributes.at((int)Character::Abilities_Stats::Charisma) = generated_attributes.at(1);
		assigned_attributes.at((int)Character::Abilities_Stats::Wisdom) = generated_attributes.at(0);
		assigned_name = "Nimble";
	}break;
	case characterBuilder::Fighter_Sub_Class::Tank:
	{
		assigned_attributes.at((int)Character::Abilities_Stats::Constitution) = generated_attributes.at(5);
		assigned_attributes.at((int)Character::Abilities_Stats::Dexterity) = generated_attributes.at(4);
		assigned_attributes.at((int)Character::Abilities_Stats::Strength) = generated_attributes.at(3);
		assigned_attributes.at((int)Character::Abilities_Stats::Intelligence) = generated_attributes.at(2);
		assigned_attributes.at((int)Character::Abilities_Stats::Charisma) = generated_attributes.at(1);
		assigned_attributes.at((int)Character::Abilities_Stats::Wisdom) = generated_attributes.at(0);
		assigned_name = "Tank";
	}
	}
	return Character::Character(assigned_name, Character::Character_Class::Fighter, assigned_attributes, false);
}
