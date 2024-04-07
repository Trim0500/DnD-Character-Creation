#include <iostream>
#include <string>
#include <sstream>

#include "testCharacter.h"
#include "..\Interactable\Interactable.h"
#include "..\Interactable\EmptyCell.h"
#include "..\Interactable\Wall.h"
#include "..\Strategy\characteractionstrategy.h"

#define CHEST_ITEM_SIZE 250

using namespace characteractionstrategy;

void TestCharacter::setUp(void)
{
	noArgsCharacterObject = new Character::Character();
	customCharacterObject = new Character::Character("Testaniel Unitoph",Character::Character_Class::Fighter, false, new AggressorStrategy());
}

void TestCharacter::tearDown(void)
{
	delete noArgsCharacterObject;
	delete customCharacterObject;
}

void TestCharacter::TestNoArgsCharacterConstructor(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->ID() >= 0);
	CPPUNIT_ASSERT(noArgsCharacterObject->Name() == "Cirian");
	CPPUNIT_ASSERT(noArgsCharacterObject->Classes() == Character::isFighter);
	CPPUNIT_ASSERT(noArgsCharacterObject->Levels(Character::Character_Class::Fighter) >= 1);
	CPPUNIT_ASSERT(noArgsCharacterObject->Levels(Character::Character_Class::Fighter) <= 20);
	CPPUNIT_ASSERT(noArgsCharacterObject->Max_Hit_Points() > 0);
	CPPUNIT_ASSERT(noArgsCharacterObject->Max_Hit_Points() <= 280);
	CPPUNIT_ASSERT(noArgsCharacterObject->GetIsPlayerControlled());
	CPPUNIT_ASSERT(dynamic_cast<HumanPlayerStrategy*>(noArgsCharacterObject->GetActionStrategy()));
}

void TestCharacter::TestCharacterConstructor(void)
{
	CPPUNIT_ASSERT(customCharacterObject->ID() >= 0);
	CPPUNIT_ASSERT(customCharacterObject->Name() == "Testaniel Unitoph");
	CPPUNIT_ASSERT(customCharacterObject->Classes() == Character::isFighter);
	CPPUNIT_ASSERT(customCharacterObject->Levels(Character::Character_Class::Fighter) == 1);
	CPPUNIT_ASSERT(customCharacterObject->Max_Hit_Points() > 0);
	CPPUNIT_ASSERT(customCharacterObject->Max_Hit_Points() <= 14);
	CPPUNIT_ASSERT(!customCharacterObject->GetIsPlayerControlled());
	CPPUNIT_ASSERT(dynamic_cast<AggressorStrategy*>(customCharacterObject->GetActionStrategy()));
}

void TestCharacter::TestGetCharacterID(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->ID() >= 0);
	CPPUNIT_ASSERT(customCharacterObject->ID() >= 1);
	CPPUNIT_ASSERT(noArgsCharacterObject->ID() != customCharacterObject->ID());
}

void TestCharacter::TestGetCharacterName(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Name() == "Cirian");
	CPPUNIT_ASSERT(customCharacterObject->Name() == "Testaniel Unitoph");
}

void TestCharacter::TestSumLevels(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Sum_Levels() > 0);
	CPPUNIT_ASSERT(noArgsCharacterObject->Sum_Levels() <= 20);

	CPPUNIT_ASSERT(customCharacterObject->Sum_Levels() == 1);
}

void TestCharacter::TestLevels(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Levels(Character::Character_Class::Fighter) > 0);
	CPPUNIT_ASSERT(noArgsCharacterObject->Levels(Character::Character_Class::Fighter) <= 20);

	CPPUNIT_ASSERT(customCharacterObject->Levels(Character::Character_Class::Fighter) == 1);
}

void TestCharacter::TestClasses(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Classes() == Character::isFighter);

	CPPUNIT_ASSERT(customCharacterObject->Classes() == Character::isFighter);
}

void TestCharacter::TestEquipItem(void)
{
	item::Item* testItem1 = new item::Item();
	item::Item* testItem2 = new item::Item();

	//testItemCurrentId += 1;

	noArgsCharacterObject->Inventory().AddNewItem(testItem1);
	CPPUNIT_ASSERT(noArgsCharacterObject->Equip_Item(testItem1));

	
	customCharacterObject->Inventory().AddNewItem(testItem2);
	CPPUNIT_ASSERT(customCharacterObject->Equip_Item(testItem2));

	delete testItem1;
	testItem1 = nullptr;
	delete testItem2;
	testItem2 = nullptr;
}

void TestCharacter::TestEquipItemDecorator(void) {
	Item* notInInventoryObject = new Item("lostItem", 2, Weapon, AttackBonus, 3);

	CPPUNIT_ASSERT_THROW_MESSAGE("[Character/Equip_Item_Decorator] -- Failed to find the item in the inventory to equip",
									customCharacterObject->Equip_Item_Decorator(notInInventoryObject), std::invalid_argument);

	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence, 5);
	Item* shieldObject = new Item("testShield", 2, Shield, ArmorClass, 10);
	Item* ringObject = new Item("testRing", 1, Ring, Wisdom, 0.5);
	Item* beltObject = new Item("testBelt", 1, Belt, Strength, 4.5);
	Item* bootsObject = new Item("testBoots", 2, Boots, Dexterity, 5);
	Item* weaponObject = new Item("testWeapon", 2, Weapon, AttackBonus, 3);

	customCharacterObject->Inventory().AddNewItem(helmetObject);
	customCharacterObject->Inventory().AddNewItem(shieldObject);
	customCharacterObject->Inventory().AddNewItem(ringObject);
	customCharacterObject->Inventory().AddNewItem(beltObject);
	customCharacterObject->Inventory().AddNewItem(bootsObject);
	customCharacterObject->Inventory().AddNewItem(weaponObject);

	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(helmetObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(shieldObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(ringObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(beltObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(bootsObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(weaponObject));

	std::ostringstream excMessage;
	excMessage << "[Character/Equip_Item_Decorator] -- Can't equip another " << itemTypeStrings[helmetObject->GetItemType() - 1];
	CPPUNIT_ASSERT_THROW_MESSAGE(excMessage.str(), customCharacterObject->Equip_Item_Decorator(helmetObject), std::invalid_argument);

	delete notInInventoryObject;
	delete helmetObject;
	delete shieldObject;
	delete ringObject;
	delete beltObject;
	delete bootsObject;
	delete weaponObject;
}

void TestCharacter::TestUnequipItem(void)
{
	item::Item* testItem = new item::Item("testItem", 3, item::ItemType::Ring, item::CharacterStats::Strength, 0.5);
	//testItemCurrentId += 1;
	Character::Equipment_Slots testItemSlot;

	noArgsCharacterObject->Inventory().AddNewItem(testItem);
	noArgsCharacterObject->Equip_Item(testItem);
	noArgsCharacterObject->Unequip_Item(Character::Equipment_Slots::Ring);
	CPPUNIT_ASSERT(noArgsCharacterObject->Equipped_Items(Character::Equipment_Slots::Ring) == nullptr);

	customCharacterObject->Inventory().AddNewItem(testItem);
	customCharacterObject->Equip_Item(testItem);
	customCharacterObject->Unequip_Item(Character::Equipment_Slots::Ring);
	CPPUNIT_ASSERT(customCharacterObject->Equipped_Items(Character::Equipment_Slots::Ring) == nullptr);

	delete testItem;
	testItem = nullptr;
}

void TestCharacter::TestUnequipItemDecorator(void) {
	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence, 5);
	Item* shieldObject = new Item("testShield", 2, Shield, ArmorClass, 10);
	Item* ringObject = new Item("testRing", 1, Ring, Wisdom, 0.5);
	Item* beltObject = new Item("testBelt", 1, Belt, Strength, 4.5);
	Item* bootsObject = new Item("testBoots", 2, Boots, Dexterity, 5);
	Item* weaponObject = new Item("testWeapon", 2, Weapon, AttackBonus, 3);

	customCharacterObject->Inventory().AddNewItem(helmetObject);
	customCharacterObject->Inventory().AddNewItem(shieldObject);
	customCharacterObject->Inventory().AddNewItem(ringObject);
	customCharacterObject->Inventory().AddNewItem(beltObject);
	customCharacterObject->Inventory().AddNewItem(bootsObject);
	customCharacterObject->Inventory().AddNewItem(weaponObject);

	customCharacterObject->Equip_Item_Decorator(helmetObject);
	customCharacterObject->Equip_Item_Decorator(shieldObject);
	customCharacterObject->Equip_Item_Decorator(ringObject);
	customCharacterObject->Equip_Item_Decorator(beltObject);
	customCharacterObject->Equip_Item_Decorator(bootsObject);
	customCharacterObject->Equip_Item_Decorator(weaponObject);

	AbstractComponent* wornItems = customCharacterObject->GetWornItems();
	int currentWornItemsSize = wornItems->GetDecoratorList().size();

	customCharacterObject->Unequip_Item_Decorator(helmetObject);

	CPPUNIT_ASSERT(helmetObject->GetWrappee() == nullptr);

	CPPUNIT_ASSERT_EQUAL(currentWornItemsSize - 1, (int)wornItems->GetDecoratorList().size());

	delete helmetObject;
	delete shieldObject;
	delete ringObject;
	delete beltObject;
	delete bootsObject;
	delete weaponObject;
}

void TestCharacter::TestMaxHitPoints(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Max_Hit_Points() > 0);
	CPPUNIT_ASSERT(noArgsCharacterObject->Max_Hit_Points() <= 280);

	CPPUNIT_ASSERT(customCharacterObject->Max_Hit_Points() > 0);
	CPPUNIT_ASSERT(customCharacterObject->Max_Hit_Points() <= 14);
}

void TestCharacter::TestHitPoints(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Max_Hit_Points() == noArgsCharacterObject->Hit_Points());

	CPPUNIT_ASSERT(customCharacterObject->Max_Hit_Points() == customCharacterObject->Hit_Points());
}

void TestCharacter::TestAbilityScore(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Strength) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Strength) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Dexterity) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Dexterity) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Wisdom) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Wisdom) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Constitution) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Constitution) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Intelligence) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Intelligence) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Charisma) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Charisma) <= 18);

	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Strength) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Strength) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Dexterity) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Dexterity) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Wisdom) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Wisdom) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Constitution) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Constitution) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Intelligence) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Intelligence) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Charisma) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score_Bonused(Character::Abilities_Stats::Charisma) <= 18);
}

void TestCharacter::TestArmourClass(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Armour_Class() <= 14);
	CPPUNIT_ASSERT(noArgsCharacterObject->Armour_Class() >= 3);

	CPPUNIT_ASSERT(customCharacterObject->Armour_Class() <= 14);
	CPPUNIT_ASSERT(customCharacterObject->Armour_Class() >= 3);
}

void TestCharacter::TestAttackBonus(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Attack_Bonus(1) <= 10);
	CPPUNIT_ASSERT(noArgsCharacterObject->Attack_Bonus(1) >= -2);

	CPPUNIT_ASSERT(customCharacterObject->Attack_Bonus(1) <= 6);
	CPPUNIT_ASSERT(customCharacterObject->Attack_Bonus(1) >= -2);
}

void TestCharacter::TestProficiencyBonus(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Proficiency_Bonus() <= 6);
	CPPUNIT_ASSERT(noArgsCharacterObject->Proficiency_Bonus() >= 2);

	CPPUNIT_ASSERT(customCharacterObject->Proficiency_Bonus() == 2);
}

void TestCharacter::TestDamageBonus(void)
{
	CPPUNIT_ASSERT(noArgsCharacterObject->Damage_Bonus() <= 4);
	CPPUNIT_ASSERT(noArgsCharacterObject->Damage_Bonus() >= -4);

	CPPUNIT_ASSERT(customCharacterObject->Damage_Bonus() <= 4);
	CPPUNIT_ASSERT(customCharacterObject->Damage_Bonus() >= -4);
}

void TestCharacter::TestActionStrategy(void) {
	std::vector<std::vector<Interactable::Interactable*>> testGrid;

	ItemContainer* chestObject = new ItemContainer("testChest", TreasureChest, CHEST_ITEM_SIZE);

	float chestItemWeightTotal = 0.0;
	while (true) {
		if (chestItemWeightTotal >= CHEST_ITEM_SIZE / 2) {
			break;
		}

		Item* newitem = new Item();
		chestObject->AddNewItem(newitem);
		chestItemWeightTotal += newitem->GetItemWeight();
	}

	for (int i = 0; i < 3; ++i)
	{
		std::vector<Interactable::Interactable*> testRow;

		for (int j = 0; j < 3; ++j)
		{
			Interactable::Interactable* testInteractable;

			if ((i == 0 && j == 0) || (i == 2 && j == 2)) {
				testInteractable = new Wall();
			}
			else if (i == 1 && j == 1) {
				testInteractable = noArgsCharacterObject;
			}
			else if (i == 1 && j == 0) {
				testInteractable = chestObject;
			}
			else if (i == 1 && j == 2) {
				testInteractable = customCharacterObject;
			}
			else {
				testInteractable = new EmptyCell();
			}

			testRow.push_back(testInteractable);
		}

		testGrid.push_back(testRow);
	}
	
	CharacterActionStrategy* playerActionStrategy = noArgsCharacterObject->GetActionStrategy();
	std::vector<CellActionInfo> playerActionInfo = playerActionStrategy->UseMovementStrategy(testGrid, 2, 2);
	CPPUNIT_ASSERT_EQUAL(4, (int)playerActionInfo.size());

	CellActionInfo upCellInfo = playerActionInfo[0];
	CPPUNIT_ASSERT_EQUAL(1, upCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(2, upCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::EMPTY_CELL_COLOR, upCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::EMPTY_CELL_ACTION, upCellInfo.actionName);
	
	CellActionInfo rightCellInfo = playerActionInfo[1];
	CPPUNIT_ASSERT_EQUAL(2, rightCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(3, rightCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::ATTACK_CELL_COLOR, rightCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::ATTACK_CELL_ACTION, rightCellInfo.actionName);
	
	CellActionInfo downCellInfo = playerActionInfo[2];
	CPPUNIT_ASSERT_EQUAL(3, downCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(2, downCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::EMPTY_CELL_COLOR, downCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::EMPTY_CELL_ACTION, downCellInfo.actionName);
	
	CellActionInfo leftCellInfo = playerActionInfo[3];
	CPPUNIT_ASSERT_EQUAL(2, leftCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(1, leftCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::PICKUP_CELL_COLOR, leftCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::PICKUP_CELL_ACTION, leftCellInfo.actionName);
	
	CharacterActionStrategy* hostileActionStrategy = customCharacterObject->GetActionStrategy();
	std::vector<CellActionInfo> hostileActionInfo = hostileActionStrategy->UseMovementStrategy(testGrid, 2, 3);
	CPPUNIT_ASSERT_EQUAL(3, (int)hostileActionInfo.size());

	upCellInfo = hostileActionInfo[0];
	CPPUNIT_ASSERT_EQUAL(1, upCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(3, upCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::EMPTY_CELL_COLOR, upCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::EMPTY_CELL_ACTION, upCellInfo.actionName);
	
	downCellInfo = hostileActionInfo[1];
	CPPUNIT_ASSERT_EQUAL(3, downCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(3, downCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::WALL_CELL_COLOR, downCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::WALL_CELL_ACTION, downCellInfo.actionName);
	
	leftCellInfo = hostileActionInfo[2];
	CPPUNIT_ASSERT_EQUAL(2, leftCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(2, leftCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::ATTACK_CELL_COLOR, leftCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::ATTACK_CELL_ACTION, leftCellInfo.actionName);

	customCharacterObject->SetActionStrategy(new FriendlyStrategy());
	CharacterActionStrategy* friendlyActionStrategy = customCharacterObject->GetActionStrategy();
	std::vector<CellActionInfo> friendlyActionInfo = friendlyActionStrategy->UseMovementStrategy(testGrid, 2, 3);
	CPPUNIT_ASSERT_EQUAL(3, (int)friendlyActionInfo.size());

	upCellInfo = friendlyActionInfo[0];
	CPPUNIT_ASSERT_EQUAL(1, upCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(3, upCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::EMPTY_CELL_COLOR, upCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::EMPTY_CELL_ACTION, upCellInfo.actionName);
	
	downCellInfo = friendlyActionInfo[1];
	CPPUNIT_ASSERT_EQUAL(3, downCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(3, downCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::WALL_CELL_COLOR, downCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::WALL_CELL_ACTION, downCellInfo.actionName);
	
	leftCellInfo = friendlyActionInfo[2];
	CPPUNIT_ASSERT_EQUAL(2, leftCellInfo.row);
	CPPUNIT_ASSERT_EQUAL(2, leftCellInfo.col);
	CPPUNIT_ASSERT_EQUAL(Character::WALL_CELL_COLOR, leftCellInfo.cellColor);
	CPPUNIT_ASSERT_EQUAL(Character::WALL_CELL_ACTION, leftCellInfo.actionName);

	testGrid.clear();
	delete chestObject;
}