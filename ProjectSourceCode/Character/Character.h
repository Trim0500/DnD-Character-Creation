/*!! \file Character.h
* \brief Header file containing Character functionality definitions
* The character creation is based off of the 5th edition Dungeons & Dragons!
* Given the limited scope of assignment 1, several 5th edition specific features could not be implemented yet including
* but not limited to...
* 'Feats', 'Race', 'Class Features', 'Backgrounds', 'spells', 'skills', 'Armour, Weapon & tool proficiencies', 'Death saves', 'initiative' and 'saving throws'
*/
#pragma once
#include <bitset>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

#include "..\Dice\Dice.h"
#include "..\Item\item.h"
#include "..\Item\itemcontainer.h"
#include "..\Observer\Observable.h"
#include "..\Serialize\serializeItem.h"
#include "..\Decorator\abstractcomponent.h"
#include "..\Strategy\characteractionstrategy.h"
#include "..\Strategy\humanplayerstrategy.h"
#include "..\Strategy\aggressorstrategy.h"
#include "..\Strategy\friendlystrategy.h"
#include "..\Interactable\Interactable.h"

using namespace abstractcomponent;
using namespace characteractionstrategy;
using namespace humanplayerstrategy;
using namespace aggressorstrategy;
using namespace friendlystrategy;
using namespace observable;

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
		std::string inventory_container_path;
		int inventory_container_id;
		bool isPlayerControlled;
		std::string actionStrategy;
	};
}


/* \namespace Character
* \brief namespace used to encapsulate 'Character' class functionality
*/
namespace Character {

	/*! \Enum Character_Class
	*  \brief Enum used to index various fields from the Character class
	*/
	enum class Character_Class {
		Barbarian = 0,
		Bard = 1,
		Cleric = 2,
		Druid = 3,
		Fighter = 4,
		Monk = 5,
		Paladin = 6,
		Ranger = 7,
		Rogue = 8,
		Sorcerer = 9,
		Warlock = 10,
		Wizard = 11
	};

	constexpr std::bitset<12> isBarbarian{ 0b0000'0000'0001 };
	constexpr std::bitset<12> isBard{ 0b0000'0000'0010 };
	constexpr std::bitset<12> isCleric{ 0b0000'0000'0100 };
	constexpr std::bitset<12> isDruid{ 0b0000'0000'1000 };
	constexpr std::bitset<12> isFighter{ 0b0000'0001'0000 };
	constexpr std::bitset<12> isMonk{ 0b0000'0010'0000 };
	constexpr std::bitset<12> isPaladin{ 0b0000'0100'0000 };
	constexpr std::bitset<12> isRanger{ 0b0000'1000'0000 };
	constexpr std::bitset<12> isRogue{ 0b0001'0000'0000 };
	constexpr std::bitset<12> isSorcerer{ 0b0010'0000'0000 };
	constexpr std::bitset<12> isWarlock{ 0b0100'0000'0000 };
	constexpr std::bitset<12> isWizard{ 0b1000'0000'0000 };

	/*! \Enum Abilities_Stats
	*  \brief Enum used to index various fields from the Character class
	*/
	enum class Abilities_Stats {

		Strength = 0,
		Dexterity,
		Constitution,
		Intelligence,
		Wisdom,
		Charisma,
		ArmorClass,
		AttackBonus,
		DamageBonus,
		NA,
	};

	/*!
	*  \brief Unordered map used to map values from item::CharacterStats TO Character::Abilities_Stats
	*/
	static const std::unordered_map<item::CharacterStats, Abilities_Stats> item_stat_TO_character_stat{
		{item::CharacterStats::Strength,Abilities_Stats::Strength},
		{item::CharacterStats::Dexterity,Abilities_Stats::Dexterity},
		{item::CharacterStats::Constitution,Abilities_Stats::Constitution},
		{item::CharacterStats::Intelligence,Abilities_Stats::Intelligence},
		{item::CharacterStats::Wisdom,Abilities_Stats::Wisdom},
		{item::CharacterStats::Charisma,Abilities_Stats::Charisma},
		{item::CharacterStats::ArmorClass,Abilities_Stats::ArmorClass},
		{item::CharacterStats::AttackBonus,Abilities_Stats::AttackBonus},
		{item::CharacterStats::DamageBonus,Abilities_Stats::DamageBonus},
		{item::CharacterStats::NA,Abilities_Stats::NA},
	};

	/*! \Enum Equipment_Slots
	*  \brief Enum used to index to fields from the Character class
	*/
	enum class Equipment_Slots {
		Armor = 0,
		Shield,
		Weapon,
		Boots,
		Ring,
		Helmet,
		Belt,
		Bag,
	};

	const std::string HUMAN_PLAYER_STRATEGY_NAME = "human";
	const std::string AGGRESSOR_STRATEGY_NAME = "aggressor";
	const std::string FRIENDLY_STRATEGY_NAME = "friendly";
	const std::string EMPTY_CELL_COLOR = "blue";
	const std::string ATTACK_CELL_COLOR = "red";
	const std::string PICKUP_CELL_COLOR = "green";
	const std::string WALL_CELL_COLOR = "none";
	const std::string WALL_CELL_ACTION = "n/a";
	const std::string EMPTY_CELL_ACTION = "move";
	const std::string ATTACK_CELL_ACTION = "attack";
	const std::string PICKUP_CELL_ACTION = "pickup";
	const std::string DOOR_CELL_ACTION = "door";


	/*! \class Character
	* \brief Represents Character type entities
	*/
	class Character : public Observable, public AbstractComponent, public Interactable::Interactable {
	public:
		/*! \fn Character()
		*  \brief Default character constructor that generates a character with random values for level, ability scores and maximum
		* hit points (By default will only give levels in the 'Fighter' class)
		*/
		Character();
		/*! \fn Character()
		*  \brief copy character constructor
		*/
		Character(const Character& t_character);
		/*! \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class
		*  \param t_name: Name for the character
		*  \param t_class: Character class the character will be given a level for
		*/
		Character(std::string t_name, Character_Class t_class, bool _isPlayerControlled = true, CharacterActionStrategy* _actionStrategy = new HumanPlayerStrategy());
		/*! \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class. Sets ability scores randomly
		*  \param t_name: Name for the character
		*  \param t_class: Character class the character will be given a level for
		*/
		Character(Character_Class t_class, bool _isPlayerControlled = true, CharacterActionStrategy* _actionStrategy = new HumanPlayerStrategy());
		/*! \fn Character()
		*  \brief Character Constructor. Initializes the character with one level in a given character class
		*  \param t_name Name for the character
		*  \param t_class Character class the character will be given a level for
		*  \param t_ability_scores Set of desired ability scores {Strength,Dexterity,Constitution,Intelligence,Wisdom,Charisma}
		*/
		Character(std::string t_name, Character_Class t_class, const std::vector<int> &t_ability_scores, bool t_average_hp, bool _isPlayerControlled = true, CharacterActionStrategy* _actionStrategy = new HumanPlayerStrategy());
		Character(const serializecharacter::CharacterRecord& t_record);

		virtual ~Character() {};

		void Attach (Observer* _observer) override { observers.push_back(_observer); };

		void Detach (Observer* _observer) override { observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end()); };

		/*!
		* \fn Notify
		* \brief Implemented function that will use the list of this observers and call their update functions using the instances observer message
		*/
		void Notify() override;

		/*!
		* \fn CreateObserverMessage
		* \brief Function that will take in a message from a calling object and use it to notify the observers with that message
		* 
		* \param _message String representing the message to pass to the observers of this game instance. Default of "Empty"
		*/
		void CreateObserverMessage(std::string);

		std::vector<Observer*> GetObservers() { return observers; };

		void SetObservers(const std::vector<Observer*>& _observers) { observers = _observers; };

		std::string GetObserverMessage() { return observerMessage; };

		void SetObserverMessage(const std::string& _observerMessage) { observerMessage = _observerMessage; };

		/* \fn ID()
		*  \brief Unique Character ID
		*/
		const int ID() { return id; };
		/*! \fn Name()
		*  \brief Character name
		*/
		std::string Name() const { return this->name; };
		std::string Name(const std::string& t_name);
		/* \fn Print_Character_Sheet
		*  \brief Prints character data to consol
		*/
		void Print_Character_Sheet();
		/*! \fn Sum_Levels()
		*  \brief Returns sum total of all levels for this character
		*  \return Returns const sum of elements in 'level' vector array
		*/
		const int Sum_Levels();
		/*! \fn Levels()
		*  \brief Returns the number of levels a chracter has taken in a corresponding class
		*  \param t_class: Any value from the Character::Character_Class enum
		*/
		const int Levels(Character_Class t_class) { return level[(int)t_class]; };
		/*! \fn Classes()
		*  \brief Used to perform bitwise comparision with 'isBarbarian', 'isBard', 'isCleric', 'isDruid', 'isFighter', 'isMonk',
		* 'isPaladin', 'isRanger', 'isRogue', 'isSorcerer' and 'isWizard' constexpr bitsets
		*  \return Returns const bitset<11> of 'character_class' field
		*/
		const std::bitset<12> Classes() { return character_class; };
		/*! \fn Levelup()
		*  \brief Levels up the the character by one level in a given class. Note that ability score bonuses given
		*  by items are not considered when checking if a character is able to mult-class
		*  \param t_class: Enum of type 'Character_Class' indicating which class a character will take a level in
		*  \return Returns true if levelup was performed succesfully, false otherwise
		*/
		bool Levelup(Character_Class t_class, bool t_average_hp);
		/*! \fn Equip_Item()
		*  \brief Equips an item into the character's corresponding equipment slot. Item must be contained within the 'inventory'
		*  vector array to be equipped
		*  \param t_item: Item pointer to the object that the character will equip
		*  \return Returns true if equipping was performed succesfully, false otherwise
		*/
		bool Equip_Item(item::Item* t_item);

		/*!
		* \fn Equip_Item_Decorator
		*  \brief Equips an item into the character's corresponding equipment slot. Item must be contained within the 'inventory'
		*  vector array to be equipped
		* 
		*  \param _itemToEquip: Item pointer to the object that the character will equip
		* 
		*  \throw std::invalid_argument
		* \throw std::out_of_range
		*/
		void Equip_Item_Decorator(item::Item*);

		/*! \fn Unequip_Item()
		*  \brief Equips an item into the character's corresponding equipment slot. Item must be contained within the 'inventory'
		*  vector array to be equipped
		*  \param t_item: Item pointer to the object that the character will equip
		*  \return Returns 'true' if equipping was performed succesfully, 'false' otherwise
		*/
		void Unequip_Item(Equipment_Slots t_slot);

		/*!
		* \fn Unequip_Item_Decorator
		*  \brief Function that rebuilds the worn items decorator by excluding an item, unequiping it
		* 
		*  \param _itemToRemove Item pointer to the object that the character will remove
		* 
		*  \throw std::invalid_argument
		* \throw std::exception
		*/
		void Unequip_Item_Decorator(item::Item*);

		/*! \fn Max_Hit_Points()
		*  \return Returns const int to the maxium number of hitpoints for this character
		*/
		const int Max_Hit_Points() { return max_hit_points; };
		/*! \fn Hit_Points()
		*  \return Returns const int to the current number of hitpoints for this character
		*/
		const int Hit_Points() { return hit_points; };
		/*! \fn Receive_Damage()
		* \brief Inflict damage to character;
		* \param t_damage: amount of damage inflicted
		*/
		void Receive_Damage(int t_damage);
		/*! \fn Receive_Damage()
		* \brief Heal character;
		* \param t_damage: amount of hit points restored
		*/
		void Receive_Healing(int t_heal);
		/*! \fn Alive()
		* \brief Checks if cahracter is alive;
		* \return Returns 'true' if hp > 0, 'false' otherwise
		*/
		const bool Is_Alive();
		/*! \fn Modifier()
		*  \param t_ability: int/Ability enum indexing the desired modifier
		*  \return Returns const int to desired modifier. Modifier is detremined using ability scores and item bonuses
		*/
		const int Modifier(Abilities_Stats t_ability);

		int ModifierDecorator(int) override;

		/*!
		* \fn Ability_Score_Natural
		* \brief Overriden function that is meant to get the raw ability score of a character based on the parameter specified
		*
		* \param _abilityScore Integer that represents the ability score targeted
		*
		* \return Integer that represents the raw ability score of the character
		*/
		int Ability_Score_Natural(int t_ability, int t_attack_number) override;
		/*! \fn Ability_Score_Bonused()
		*  \param t_ability: int/Ability enum indexing the desired ability score
		*  \return Returns const int to desired ability score. Returned value does not take into account any item bonuses
		*/
		const int Ability_Score_Bonused(Abilities_Stats t_ability);
		/*! \fn Armour_Class()
		*  \brief Calculates and returns AC(armour class) based off a character's ability scores & equipped items
		*  \return Returns const int AC
		*/
		const int Armour_Class();
		/*! \fn Attack_Bonus()
		*  \brief Calculates and returns attack bonus based off a character's level, equipped items and attack number (1st attack, 2nd attack, etc...)
		*  \param t_attack_number: int representing 1st, 2nd, 3rd or 4th attack
		*  \return Returns const int to attack bonus
		*/
		const int Attack_Bonus(int t_attack_number);
		/*! \fn Proficiency_Bonus()
		*  \brief Calculates and returns proficiency bonus based off a character's cumulative levels
		*  \return Returns const int to proficiency bonus
		*/
		const int Proficiency_Bonus();
		/*! \fn Damage_Bonus()
		*  \brief Calculates and returns damage bonus based off a character's strength and equipped items
		*  \return Returns const int to damage bonus
		*/
		const int Damage_Bonus();
		/*! \fn Inventory()
		*  \return Returns refrence to ItemContainer type object corresponding to the character's inventory
		*/
		itemcontainer::ItemContainer& Inventory() { return inventory; };

		/*!
		* \fn TakeItems
		* \brief Method meant to implement a character action of taking a selection of items from an item container
		* \param _targetContainer Pointer to an ItemContainer instance representing the container to pull items from
		* \param _selectedItems Vector of Item instance pointers representing the items to transfer over
		* \param _destinationContainerID Integer representing the ItemContainer instance to put the items into 
		* \throw invalid_argument
		* \throw overflow_error
		*/
		void TakeItems(itemcontainer::ItemContainer*, const std::vector<Item*>&, const int&);

		/*!
		* \fn DropItems
		* \brief Method meant to implement a character action of dropping items from a given item container
		* \param _selectedItems Vector of Item instance pointers representing the items to drop
		* \param _targetContainerID Integer representing the ItemContainer instance to drop items from
		* \throw invalid_argument
		* \throw overflow_error
		*/
		void DropItems(const std::vector<Item*>&, const int&);

		/*! \fn Get_Equiped_Item()
		*  \return Returns pointer to item type object corresponding to the paramaters equipment slot. Retruns nullptr if no item is found
		*/
		const item::Item* Equipped_Items(Equipment_Slots t_item) { return equipment_slots.at(t_item); };

		AbstractComponent* GetWornItems() { return wornItems; };

		void SetWornItems(AbstractComponent* _wornItems) { wornItems = _wornItems; };

		/*! \fn Is_Multi_Classed()
		*  \brief Checks if the character is multi-classed with a particular character class
		*/
		bool Is_Multi_Classed(Character_Class t_class);
		/*! \fn Attacks_Per_Turn()
		*  \brief Return the number of attacks per turn based off level
		*/
		const int Attacks_Per_Turn();

		/*!
		* \fn GetDecoratorList
		* \brief Overriden function that is meant to simply create the vector of worn itens for decorators to push their pointers to
		* 
		* \return Empty vector of pointers to AbstractComponent instances that represent the list for decorators to update
		*/
		std::vector<AbstractComponent*> GetDecoratorList() override { std::vector<AbstractComponent*> initDecorators; return initDecorators; };

		bool passable() const { return true; };// can the MC pass through this cell

		std::string serialize();

		bool GetIsPlayerControlled() { return isPlayerControlled; };

		void SetIsPlayerControlled(bool _isPlayerControlled) { isPlayerControlled = _isPlayerControlled; };

		CharacterActionStrategy* GetActionStrategy() { return actionStrategy; };

		void SetActionStrategy(CharacterActionStrategy* _actionStrategy) { actionStrategy = _actionStrategy; };

		bool AttemptAttack(Character*);

		CellActionInfo DecideNPCAction(const std::vector<std::vector<Interactable*>>&, const int&, const int&);

		std::string Get_Class_String(Character_Class t_class);
		std::string Get_Class_String(int t_class);
		std::string Get_Abilities_String(Abilities_Stats t_abilities);
		std::string Get_Item_Type_String(item::ItemType t_type);
		std::string Get_Equipment_Slot_String(Equipment_Slots t_slot);

	private:
		/*!
		* \var observers
		* \brief Vector of pointers to Observer instances representing the attached objects that are to be notified of state changes
		*/
		std::vector<Observer*> observers;

		/*!
		* \var observerMessage
		* \brief String representing the message to pass to the observers
		*/
		std::string observerMessage;

		static inline unsigned int id_gen{ 0 };
		const int id = id_gen++;

		std::string name{ "Cirian" };
		std::bitset<12> character_class;
		/*!
		* Vector array corresponding to how many levels the character has taken in each class. Can be indexed using int/'Abilities' enum
		*/
		std::vector<int> level = std::vector<int>(12, 0);
		/*!
		* Vector array corresponding to a character's ability scores. Can be indexed using int/'Abilities' enum
		*/
		std::vector<int> ability_scores = std::vector<int>(6);
		int max_hit_points{ 0 };
		int hit_points{ 0 };

		std::unordered_map<Equipment_Slots, item::Item*> equipment_slots;

		itemcontainer::ItemContainer inventory = itemcontainer::ItemContainer("Inventory", Backpack, 30);



		/*! \fn setAttribute(Abilities_Stats t_ability, int t_val)
		* \private function that allows attribute values to be set without leveling up 
		*/
		int setAttribute(Abilities_Stats t_ability, int t_val);
		/*! \fn setMaxHitPoints(int t_val)
		* \private function that allows max HP to be set without leveling up
		*/
		int setMaxHitPoints(int t_val);
		/*! \fn setHitPoints(int t_val)
		* \private function that allows HP to be set without leveling up
		*/
		int setHitPoints(int t_val);
		/*! \fn setLevel(Character_Class t_class, int t_val)
		* \private function that allows a characters level to be set without going through leveling-up.
		*/
		int setLevel(Character_Class t_class, int t_val);

		bool Levelup_Barbarian(bool t_average_hp);
		bool Levelup_Bard(bool t_average_hp);
		bool Levelup_Cleric(bool t_average_hp);
		bool Levelup_Druid(bool t_average_hp);
		bool Levelup_Fighter(bool t_average_hp);
		bool Levelup_Monk(bool t_average_hp);
		bool Levelup_Paladin(bool t_average_hp);
		bool Levelup_Ranger(bool t_average_hp);
		bool Levelup_Rogue(bool t_average_hp);
		bool Levelup_Sorcerer(bool t_average_hp);
		bool Levelup_Warlock(bool t_average_hp);
		bool Levelup_Wizard(bool t_average_hp);

		/*!
		* \var wornItems
		* \brief A pointer to an AbstractComponent instance that represents the character's equipped items
		*/
		AbstractComponent* wornItems;

		/*!
		* \var isPlayerControlled
		* \brief Player character or NPC?
		*/
		bool isPlayerControlled;

		/*!
		* \var actionStrategy
		* \brief Pointer to a CharacterActionStrategy instance that represents the character's actions on a map
		*/
		CharacterActionStrategy* actionStrategy;
	};
}
/*! \namespace characterBuilder
* \brief namespace used to encapsulate 'characterBuilder' class functionality
*/
namespace characterBuilder {
	/*! \Enum Fighter_Sub_Class
	*  \brief Enum used to index to fields from Fighter subclasses
	*/
	enum class Fighter_Sub_Class {
		Bully,
		Nimble,
		Tank
	};
	/*! \fn Build_Fighter
	*  \brief Function that allows to build a Fighter class character based off a Fighter subclass
	*/
	Character::Character Build_Fighter(characterBuilder::Fighter_Sub_Class t_subclass);

}