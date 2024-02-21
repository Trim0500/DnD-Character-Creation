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
	item::Item* testItem = new item::Item();

	//testItemCurrentId += 1;

	noArgsCharacterObject->Inventory().AddNewItem(testItem);
	CPPUNIT_ASSERT(noArgsCharacterObject->Equip_Item(testItem));
	
	customCharacterObject->Inventory().AddNewItem(testItem);
	CPPUNIT_ASSERT(customCharacterObject->Equip_Item(testItem));

	delete testItem;
	testItem = nullptr;
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
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Strength) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Strength) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Dexterity) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Dexterity) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Wisdom) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Wisdom) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Constitution) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Constitution) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Intelligence) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Intelligence) <= 18);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Charisma) >= 3);
	CPPUNIT_ASSERT(noArgsCharacterObject->Ability_Score(Character::Abilities_Stats::Charisma) <= 18);

	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Strength) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Strength) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Dexterity) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Dexterity) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Wisdom) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Wisdom) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Constitution) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Constitution) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Intelligence) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Intelligence) <= 18);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Charisma) >= 3);
	CPPUNIT_ASSERT(customCharacterObject->Ability_Score(Character::Abilities_Stats::Charisma) <= 18);
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
	CPPUNIT_ASSERT(noArgsCharacterObject->Attack_Bonus() <= 10);
	CPPUNIT_ASSERT(noArgsCharacterObject->Attack_Bonus() >= -2);

	CPPUNIT_ASSERT(customCharacterObject->Attack_Bonus() <= 6);
	CPPUNIT_ASSERT(customCharacterObject->Attack_Bonus() >= -2);
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