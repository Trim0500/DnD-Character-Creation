#include <iostream>
#include <string>
#include <sstream>

#include "testCharacter.h"

void TestCharacter::setUp(void)
{
	noArgsCharacterObject = new Character::Character();
	customCharacterObject = new Character::Character("Testaniel Unitoph",Character::Character_Class::Fighter);
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
}

void TestCharacter::TestCharacterConstructor(void)
{
	CPPUNIT_ASSERT(customCharacterObject->ID() >= 0);
	CPPUNIT_ASSERT(customCharacterObject->Name() == "Testaniel Unitoph");
	CPPUNIT_ASSERT(customCharacterObject->Classes() == Character::isFighter);
	CPPUNIT_ASSERT(customCharacterObject->Levels(Character::Character_Class::Fighter) == 1);
	CPPUNIT_ASSERT(customCharacterObject->Max_Hit_Points() > 0);
	CPPUNIT_ASSERT(customCharacterObject->Max_Hit_Points() <= 14);
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

	ItemContainer characterInventory = customCharacterObject->Inventory();
	characterInventory.AddNewItem(helmetObject);
	characterInventory.AddNewItem(shieldObject);
	characterInventory.AddNewItem(ringObject);
	characterInventory.AddNewItem(beltObject);
	characterInventory.AddNewItem(bootsObject);
	characterInventory.AddNewItem(weaponObject);

	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(helmetObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(shieldObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(ringObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(beltObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(bootsObject));
	CPPUNIT_ASSERT_NO_THROW(customCharacterObject->Equip_Item_Decorator(weaponObject));

	std::ostringstream excMessage;
	excMessage << "[Character/Equip_Item_Decorator] -- Can't equip another " << itemTypeStrings[helmetObject->GetItemType() - 1];
	CPPUNIT_ASSERT_THROW_MESSAGE(excMessage.str(), customCharacterObject->Equip_Item_Decorator(helmetObject), std::exception);

	delete notInInventoryObject;
	delete helmetObject;
	delete ringObject;
	delete beltObject;
	delete bootsObject;
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
	Item* ringObject = new Item("testRing", 1, Ring, Wisdom, 0.5);
	Item* beltObject = new Item("testBelt", 1, Belt, Strength, 4.5);
	Item* bootsObject = new Item("testBoots", 2, Boots, Dexterity, 5);

	ItemContainer characterInventory = customCharacterObject->Inventory();
	characterInventory.AddNewItem(helmetObject);
	characterInventory.AddNewItem(ringObject);
	characterInventory.AddNewItem(beltObject);
	characterInventory.AddNewItem(bootsObject);

	customCharacterObject->Equip_Item_Decorator(helmetObject);
	customCharacterObject->Equip_Item_Decorator(ringObject);
	customCharacterObject->Equip_Item_Decorator(beltObject);
	customCharacterObject->Equip_Item_Decorator(bootsObject);

	AbstractComponent* wornItems = customCharacterObject->GetWornItems();
	int currentWornItemsSize = wornItems->GetDecoratorList().size();

	customCharacterObject->Unequip_Item_Decorator(helmetObject);

	CPPUNIT_ASSERT(helmetObject->GetWrappee() == nullptr);

	CPPUNIT_ASSERT_EQUAL(currentWornItemsSize - 1, (int)wornItems->GetDecoratorList().size());

	delete helmetObject;
	delete ringObject;
	delete beltObject;
	delete bootsObject;
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