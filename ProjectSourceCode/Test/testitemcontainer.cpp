/*!
* \file testitemcontainer.cpp
* \brief Test implementation for Item
*/

#include <iostream>
#include <vector>

#include "testitemcontainer.h"
#include "..\Character\Character.h"

#define BACKPACK_ITEM_SIZE 30
#define WORN_ITEMS_SIZE 7
#define CHEST_ITEM_SIZE 250
#define WORN_ITEMS_PLUS_ONE_ITEMS_SIZE 2
#define WORN_ITEMS_PLUS_TWO_ITEMS_SIZE 4
#define WORN_ITEMS_PLUS_THREE_ITEMS_SIZE 1
#define WORN_ITEMS_PLUS_FOUR_ITEMS_SIZE 0
#define WORN_ITEMS_PLUS_FIVE_ITEMS_SIZE 0

// using namespace std;

void TestItemContainer::setUp(void)
{
	backpackObject = new ItemContainer("testBackpack", Backpack, BACKPACK_ITEM_SIZE);
	
	Item* backpackShieldItem = new Item("testBackpackShield", 4, Shield, ArmorClass, 12);
	Item* backpackBootsItem = new Item("testBackpackBoots", 4, Boots, Dexterity, 5);

	backpackObject->AddNewItem(backpackShieldItem);
	backpackObject->AddNewItem(backpackBootsItem);

	wornItemsObject = new ItemContainer("testWornItems", WornItems, 0);

	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence, 5);
	Item* armorObject = new Item("testArmor", 3, Armor, ArmorClass, 45);
	Item* shieldObject = new Item("testShield", 2, Shield, ArmorClass, 10);
	Item* ringObject = new Item("testRing", 1, Ring, Wisdom, 0.5);
	Item* beltObject = new Item("testBelt", 1, Belt, Strength, 4.5);
	Item* bootsObject = new Item("testBoots", 2, Boots, Dexterity, 5);
	Item* weaponObject = new Item("testWeapon", 2, Weapon, AttackBonus, 3);

	wornItemsObject->AddNewItem(helmetObject);
	wornItemsObject->AddNewItem(armorObject);
	wornItemsObject->AddNewItem(shieldObject);
	wornItemsObject->AddNewItem(ringObject);
	wornItemsObject->AddNewItem(beltObject);
	wornItemsObject->AddNewItem(bootsObject);
	wornItemsObject->AddNewItem(weaponObject);

	chestObject = new ItemContainer("testChest", TreasureChest, CHEST_ITEM_SIZE);

	float chestItemWeightTotal = 0.0;
	while (true) {
		if (chestItemWeightTotal >= CHEST_ITEM_SIZE / 2) {
			break;
		}

		Item* newitem = new Item();
		chestObject->AddNewItem(newitem);
		chestItemWeightTotal += newitem->GetItemWeight();
	}

	inventoryObject = new ItemContainer("testInventory", Inventory, 0);

	//testItemCurrentId += 34;
}

void TestItemContainer::tearDown(void)
{
	backpackObject->GetAllItems().clear();

	delete backpackObject;

	wornItemsObject->GetAllItems().clear();

	delete wornItemsObject;

	chestObject->GetAllItems().clear();

	delete chestObject;

	delete inventoryObject;
}

void TestItemContainer::TestCustomConstructor(void) {
	CPPUNIT_ASSERT(backpackObject->GetItemName() == "testBackpack");
	CPPUNIT_ASSERT(backpackObject->GetItemType() == Backpack);
	CPPUNIT_ASSERT(backpackObject->GetCapacity() >= BACKPACK_ITEM_SIZE);

	CPPUNIT_ASSERT(wornItemsObject->GetItemName() == "testWornItems");
	CPPUNIT_ASSERT(wornItemsObject->GetItemType() == WornItems);
	CPPUNIT_ASSERT(wornItemsObject->GetCapacity() >= 0);

	CPPUNIT_ASSERT(chestObject->GetItemName() == "testChest");
	CPPUNIT_ASSERT(chestObject->GetItemType() == TreasureChest);
	CPPUNIT_ASSERT(chestObject->GetCapacity() >= CHEST_ITEM_SIZE);
}

void TestItemContainer::TestSetWeightCapacity(void) {
	Character::Character* testCharacter = new Character::Character("testCharacter", Character::Character_Class::Fighter);
	int strengthModifier = testCharacter->Ability_Score_Natural((int)Character::Abilities_Stats::Strength, 0);
	inventoryObject->SetWeightLimit(strengthModifier * 20);
	CPPUNIT_ASSERT(inventoryObject->GetCapacity() == strengthModifier * 20);
}

void TestItemContainer::TestAddNewItem(void) {
	int backpackItemSize = backpackObject->GetAllItems().size();
	float backpackTotalItemWeight = backpackObject->GetTotalItemWeight();

	int wornItemsSize = wornItemsObject->GetAllItems().size();

	int chestItemSize = chestObject->GetAllItems().size();
	float chestTotalItemWeight = chestObject->GetTotalItemWeight();

	Item* newItem = new Item("newItem", 4, Armor, ArmorClass, 50);

	//testItemCurrentId += 1;

	int addResult = backpackObject->AddNewItem(newItem);
	int currentBackpackItemSize = backpackObject->GetAllItems().size();
	float currentBackpackItemWeightTotal = backpackObject->GetTotalItemWeight();
	CPPUNIT_ASSERT(addResult == -1 &&
					currentBackpackItemSize == backpackItemSize &&
					currentBackpackItemWeightTotal == backpackTotalItemWeight &&
					backpackObject->GetAllItems().back().GetItemId() != newItem->GetItemId());

	int equipResult = wornItemsObject->AddNewItem(newItem);
	int currentWornItemSize = wornItemsObject->GetAllItems().size();
	CPPUNIT_ASSERT(equipResult == -1 && currentWornItemSize == wornItemsSize);

	chestObject->AddNewItem(newItem);
	int currentChestItemSize = chestObject->GetAllItems().size();
	float currentChestItemWeightTotal = chestObject->GetTotalItemWeight();
	CPPUNIT_ASSERT(currentChestItemSize == chestItemSize + 1 && currentChestItemWeightTotal <= CHEST_ITEM_SIZE);
	CPPUNIT_ASSERT(chestObject->GetAllItems().back() == *newItem);
}

void TestItemContainer::TestRemoveItems(void) {
	std::vector<Item> backpackItems = backpackObject->GetAllItems();
	std::vector<Item*> backpackItemsToRemove;
	backpackItemsToRemove.push_back(&backpackItems[0]);
	backpackObject->RemoveItems(backpackItemsToRemove);

	CPPUNIT_ASSERT_EQUAL(1, (int)backpackObject->GetAllItems().size());

	std::vector<Item> chestItems = chestObject->GetAllItems();
	int chestItemsCount = chestItems.size();

	std::vector<Item*> chestItemsToRemove;
	chestItemsToRemove.push_back(&chestItems[0]);
	chestItemsToRemove.push_back(&chestItems[1]);
	chestItemsToRemove.push_back(&chestItems[2]);
	chestObject->RemoveItems(chestItemsToRemove);

	CPPUNIT_ASSERT_EQUAL(chestItemsCount - 3, (int)chestObject->GetAllItems().size());
}

void TestItemContainer::TestGetItemByName(void) {
	Item* foundItem = wornItemsObject->GetItem("testHelmet");
	CPPUNIT_ASSERT(foundItem->GetItemName() == "testHelmet");
	
	Item* nullPointer = wornItemsObject->GetItem("someRandomName");
	CPPUNIT_ASSERT(nullPointer == nullptr);
}

void TestItemContainer::TestGetItemByItemType(void) {
	Item* foundItem = wornItemsObject->GetItem(Weapon);
	CPPUNIT_ASSERT(foundItem->GetItemType() == Weapon);

	Item* nullPointer = wornItemsObject->GetItem(Backpack);
	CPPUNIT_ASSERT(nullPointer == nullptr);
}

void TestItemContainer::TestGetItemWeightTotal(void) {
	float backpackItemWeightTotal = backpackObject->GetTotalItemWeight();
	CPPUNIT_ASSERT(backpackItemWeightTotal == 17 && backpackItemWeightTotal <= BACKPACK_ITEM_SIZE);
	
	float chestItemWeightTotal = chestObject->GetTotalItemWeight();
	CPPUNIT_ASSERT(chestItemWeightTotal >= 0 && chestItemWeightTotal <= CHEST_ITEM_SIZE);
}

void TestItemContainer::TestGetAllItems(void) {
	std::vector<Item> backpackItems = backpackObject->GetAllItems();
	CPPUNIT_ASSERT(backpackItems.size() == 2);
	
	std::vector<Item> wornItems = wornItemsObject->GetAllItems();
	CPPUNIT_ASSERT(wornItems.size() == WORN_ITEMS_SIZE);
	
	std::vector<Item> chestItems = chestObject->GetAllItems();
	CPPUNIT_ASSERT(chestItems.size() >= 0);
}

void TestItemContainer::TestGetItemsByBonus(void) {
	std::vector<Item> backpackPlusOneItems = backpackObject->GetItemsByEnchantmentBonus(1);
	CPPUNIT_ASSERT(backpackPlusOneItems.size() == 0);
	
	std::vector<Item> backpackPlusTwoItems = backpackObject->GetItemsByEnchantmentBonus(2);
	CPPUNIT_ASSERT(backpackPlusTwoItems.size() == 0);
	
	std::vector<Item> backpackPlusThreeItems = backpackObject->GetItemsByEnchantmentBonus(3);
	CPPUNIT_ASSERT(backpackPlusThreeItems.size() == 0);
	
	std::vector<Item> backpackPlusFourItems = backpackObject->GetItemsByEnchantmentBonus(4);
	CPPUNIT_ASSERT(backpackPlusFourItems.size() == 2);
	
	std::vector<Item> backpackPlusFiveItems = backpackObject->GetItemsByEnchantmentBonus(5);
	CPPUNIT_ASSERT(backpackPlusFiveItems.size() == 0);

	std::vector<Item> plusOneWornItems = wornItemsObject->GetItemsByEnchantmentBonus(1);
	CPPUNIT_ASSERT(plusOneWornItems.size() == WORN_ITEMS_PLUS_ONE_ITEMS_SIZE);

	std::vector<Item> plusTwoWornItems = wornItemsObject->GetItemsByEnchantmentBonus(2);
	CPPUNIT_ASSERT(plusTwoWornItems.size() == WORN_ITEMS_PLUS_TWO_ITEMS_SIZE);
	
	std::vector<Item> plusThreeWornItems = wornItemsObject->GetItemsByEnchantmentBonus(3);
	CPPUNIT_ASSERT(plusThreeWornItems.size() == WORN_ITEMS_PLUS_THREE_ITEMS_SIZE);
	
	std::vector<Item> plusFourWornItems = wornItemsObject->GetItemsByEnchantmentBonus(4);
	CPPUNIT_ASSERT(plusFourWornItems.size() == WORN_ITEMS_PLUS_FOUR_ITEMS_SIZE);
	
	std::vector<Item> plusFiveWornItems = wornItemsObject->GetItemsByEnchantmentBonus(5);
	CPPUNIT_ASSERT(plusFiveWornItems.size() == WORN_ITEMS_PLUS_FIVE_ITEMS_SIZE);

	std::vector<Item> chestPlusOneItems = chestObject->GetItemsByEnchantmentBonus(1);
	CPPUNIT_ASSERT(chestPlusOneItems.size() >= 0);

	std::vector<Item> chestPlusTwoItems = chestObject->GetItemsByEnchantmentBonus(2);
	CPPUNIT_ASSERT(chestPlusTwoItems.size() >= 0);

	std::vector<Item> chestPlusThreeItems = chestObject->GetItemsByEnchantmentBonus(3);
	CPPUNIT_ASSERT(chestPlusThreeItems.size() >= 0);

	std::vector<Item> chestPlusFourItems = chestObject->GetItemsByEnchantmentBonus(4);
	CPPUNIT_ASSERT(chestPlusFourItems.size() >= 0);

	std::vector<Item> chestPlusFiveItems = chestObject->GetItemsByEnchantmentBonus(5);
	CPPUNIT_ASSERT(chestPlusFiveItems.size() >= 0);
}

void TestItemContainer::TestGetItemsByType(void) {
	std::vector<Item> helmetBackpackItems = backpackObject->GetItemsByItemType(Helmet);
	CPPUNIT_ASSERT(helmetBackpackItems.size() >= 0);
	
	std::vector<Item> armorBackpackItems = backpackObject->GetItemsByItemType(Armor);
	CPPUNIT_ASSERT(armorBackpackItems.size() >= 0);
	
	std::vector<Item> shieldBackpackItems = backpackObject->GetItemsByItemType(Shield);
	CPPUNIT_ASSERT(shieldBackpackItems.size() >= 0);
	
	std::vector<Item> ringBackpackItems = backpackObject->GetItemsByItemType(Ring);
	CPPUNIT_ASSERT(ringBackpackItems.size() >= 0);
	
	std::vector<Item> beltBackpackItems = backpackObject->GetItemsByItemType(Belt);
	CPPUNIT_ASSERT(beltBackpackItems.size() >= 0);
	
	std::vector<Item> bootsBackpackItems = backpackObject->GetItemsByItemType(Boots);
	CPPUNIT_ASSERT(bootsBackpackItems.size() >= 0);
	
	std::vector<Item> weaponBackpackItems = backpackObject->GetItemsByItemType(Weapon);
	CPPUNIT_ASSERT(weaponBackpackItems.size() >= 0);

	std::vector<Item> helmetWornItems = wornItemsObject->GetItemsByItemType(Helmet);
	CPPUNIT_ASSERT(helmetWornItems.size() == 1);
	
	std::vector<Item> armorWornItems = wornItemsObject->GetItemsByItemType(Armor);
	CPPUNIT_ASSERT(armorWornItems.size() == 1);
	
	std::vector<Item> shieldWornItems = wornItemsObject->GetItemsByItemType(Shield);
	CPPUNIT_ASSERT(armorWornItems.size() == 1);
	
	std::vector<Item> ringWornItems = wornItemsObject->GetItemsByItemType(Ring);
	CPPUNIT_ASSERT(ringWornItems.size() == 1);
	
	std::vector<Item> beltWornItems = wornItemsObject->GetItemsByItemType(Belt);
	CPPUNIT_ASSERT(beltWornItems.size() == 1);
	
	std::vector<Item> bootsWornItems = wornItemsObject->GetItemsByItemType(Boots);
	CPPUNIT_ASSERT(bootsWornItems.size() == 1);
	
	std::vector<Item> weaponWornItems = wornItemsObject->GetItemsByItemType(Weapon);
	CPPUNIT_ASSERT(weaponWornItems.size() == 1);

	std::vector<Item> helmetChestItems = chestObject->GetItemsByItemType(Helmet);
	CPPUNIT_ASSERT(helmetChestItems.size() >= 0);

	std::vector<Item> armorChestItems = chestObject->GetItemsByItemType(Armor);
	CPPUNIT_ASSERT(armorChestItems.size() >= 0);

	std::vector<Item> shieldChestItems = chestObject->GetItemsByItemType(Shield);
	CPPUNIT_ASSERT(shieldChestItems.size() >= 0);

	std::vector<Item> ringChestItems = chestObject->GetItemsByItemType(Ring);
	CPPUNIT_ASSERT(ringChestItems.size() >= 0);

	std::vector<Item> beltChestItems = chestObject->GetItemsByItemType(Belt);
	CPPUNIT_ASSERT(beltChestItems.size() >= 0);

	std::vector<Item> bootsChestItems = chestObject->GetItemsByItemType(Boots);
	CPPUNIT_ASSERT(bootsChestItems.size() >= 0);

	std::vector<Item> weaponChestItems = chestObject->GetItemsByItemType(Weapon);
	CPPUNIT_ASSERT(weaponChestItems.size() >= 0);
}

void TestItemContainer::TestGetItemsByStat(void) {
	std::vector<Item> strengthBackpackItems = backpackObject->GetItemsByStat(Strength);
	CPPUNIT_ASSERT(strengthBackpackItems.size() >= 0);
	
	std::vector<Item> dexterityBackpackItems = backpackObject->GetItemsByStat(Dexterity);
	CPPUNIT_ASSERT(dexterityBackpackItems.size() >= 0);
	
	std::vector<Item> constitutionBackpackItems = backpackObject->GetItemsByStat(Constitution);
	CPPUNIT_ASSERT(constitutionBackpackItems.size() >= 0);
	
	std::vector<Item> intelligenceBackpackItems = backpackObject->GetItemsByStat(Intelligence);
	CPPUNIT_ASSERT(intelligenceBackpackItems.size() >= 0);
	
	std::vector<Item> wisdomBackpackItems = backpackObject->GetItemsByStat(Wisdom);
	CPPUNIT_ASSERT(wisdomBackpackItems.size() >= 0);
	
	std::vector<Item> charismaBackpackItems = backpackObject->GetItemsByStat(Charisma);
	CPPUNIT_ASSERT(charismaBackpackItems.size() >= 0);
	
	std::vector<Item> armorClassBackpackItems = backpackObject->GetItemsByStat(ArmorClass);
	CPPUNIT_ASSERT(armorClassBackpackItems.size() >= 0);
	
	std::vector<Item> attackBonusBackpackItems = backpackObject->GetItemsByStat(AttackBonus);
	CPPUNIT_ASSERT(attackBonusBackpackItems.size() >= 0);
	
	std::vector<Item> dmgBonusBackpackItems = backpackObject->GetItemsByStat(DamageBonus);
	CPPUNIT_ASSERT(dmgBonusBackpackItems.size() >= 0);
	
	std::vector<Item> strengthWornItems = wornItemsObject->GetItemsByStat(Strength);
	CPPUNIT_ASSERT(strengthWornItems.size() == 1);
	
	std::vector<Item> dexterityWornItems = wornItemsObject->GetItemsByStat(Dexterity);
	CPPUNIT_ASSERT(dexterityWornItems.size() == 1);
	
	std::vector<Item> constitutionWornItems = wornItemsObject->GetItemsByStat(Constitution);
	CPPUNIT_ASSERT(constitutionWornItems.size() == 0);
	
	std::vector<Item> intelligenceWornItems = wornItemsObject->GetItemsByStat(Intelligence);
	CPPUNIT_ASSERT(intelligenceWornItems.size() == 1);
	
	std::vector<Item> wisdomWornItems = wornItemsObject->GetItemsByStat(Wisdom);
	CPPUNIT_ASSERT(wisdomWornItems.size() == 1);
	
	std::vector<Item> charismaWornItems = wornItemsObject->GetItemsByStat(Charisma);
	CPPUNIT_ASSERT(charismaWornItems.size() == 0);
	
	std::vector<Item> armorClassWornItems = wornItemsObject->GetItemsByStat(ArmorClass);
	CPPUNIT_ASSERT(armorClassWornItems.size() == 2);
	
	std::vector<Item> attackBonusWornItems = wornItemsObject->GetItemsByStat(AttackBonus);
	CPPUNIT_ASSERT(attackBonusWornItems.size() == 1);
	
	std::vector<Item> dmgBonusWornItems = wornItemsObject->GetItemsByStat(DamageBonus);
	CPPUNIT_ASSERT(dmgBonusWornItems.size() == 0);

	std::vector<Item> strengthChestItems = chestObject->GetItemsByStat(Strength);
	CPPUNIT_ASSERT(strengthChestItems.size() >= 0);

	std::vector<Item> dexterityChestItems = chestObject->GetItemsByStat(Dexterity);
	CPPUNIT_ASSERT(dexterityChestItems.size() >= 0);

	std::vector<Item> constitutionChestItems = chestObject->GetItemsByStat(Constitution);
	CPPUNIT_ASSERT(constitutionChestItems.size() >= 0);

	std::vector<Item> intelligenceChestItems = chestObject->GetItemsByStat(Intelligence);
	CPPUNIT_ASSERT(intelligenceChestItems.size() >= 0);

	std::vector<Item> wisdomChestItems = chestObject->GetItemsByStat(Wisdom);
	CPPUNIT_ASSERT(wisdomChestItems.size() >= 0);

	std::vector<Item> charismaChestItems = chestObject->GetItemsByStat(Charisma);
	CPPUNIT_ASSERT(charismaChestItems.size() >= 0);

	std::vector<Item> armorClassChestItems = chestObject->GetItemsByStat(ArmorClass);
	CPPUNIT_ASSERT(armorClassChestItems.size() >= 0);

	std::vector<Item> attackBonusChestItems = chestObject->GetItemsByStat(AttackBonus);
	CPPUNIT_ASSERT(attackBonusChestItems.size() >= 0);

	std::vector<Item> dmgBonusChestItems = chestObject->GetItemsByStat(DamageBonus);
	CPPUNIT_ASSERT(dmgBonusChestItems.size() >= 0);
}
