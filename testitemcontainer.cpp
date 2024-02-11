/*
* \file testitemcontainer.cpp
* \brief Test implementation for Item
*/

#include <iostream>
#include <vector>

#include "testitemcontainer.h"

#define BACKPACK_ITEM_SIZE 10
#define WORN_ITEMS_SIZE 7
#define CHEST_ITEM_SIZE 20
#define WORN_ITEMS_PLUS_ONE_ITEMS_SIZE 2
#define WORN_ITEMS_PLUS_TWO_ITEMS_SIZE 4
#define WORN_ITEMS_PLUS_THREE_ITEMS_SIZE 1
#define WORN_ITEMS_PLUS_FOUR_ITEMS_SIZE 0
#define WORN_ITEMS_PLUS_FIVE_ITEMS_SIZE 0

using namespace std;

void TestItemContainer::setUp(void)
{
	backpackObject = new ItemContainer("testBackpack", Backpack, BACKPACK_ITEM_SIZE);

	for (int i = 0; i < BACKPACK_ITEM_SIZE - 1; i++)
	{
		Item* newItem = new Item();
		backpackObject->AddNewItem(*newItem);
	}

	wornItemsObject = new ItemContainer("testWornItems", WornItems, WORN_ITEMS_SIZE);

	Item* helmetObject = new Item("testHelmet", 2, Helmet, Intelligence);
	Item* armorObject = new Item("testArmor", 3, Armor, ArmorClass);
	Item* shieldObject = new Item("testShield", 2, Shield, ArmorClass);
	Item* ringObject = new Item("testRing", 1, Ring, Wisdom);
	Item* beltObject = new Item("testBelt", 1, Belt, Strength);
	Item* bootsObject = new Item("testBoots", 2, Boots, Dexterity);
	Item* weaponObject = new Item("testWeapon", 2, Weapon, AttackBonus);

	wornItemsObject->AddNewItem(*helmetObject);
	wornItemsObject->AddNewItem(*armorObject);
	wornItemsObject->AddNewItem(*shieldObject);
	wornItemsObject->AddNewItem(*ringObject);
	wornItemsObject->AddNewItem(*beltObject);
	wornItemsObject->AddNewItem(*bootsObject);
	wornItemsObject->AddNewItem(*weaponObject);

	chestObject = new ItemContainer("testChest", TreasureChest, CHEST_ITEM_SIZE);

	for (int i = 0; i < CHEST_ITEM_SIZE - 2; i++)
	{
		Item* newItem = new Item();
		chestObject->AddNewItem(*newItem);
	}
}

void TestItemContainer::tearDown(void)
{
	backpackObject->GetAllItems().clear();

	delete backpackObject;

	wornItemsObject->GetAllItems().clear();

	delete wornItemsObject;

	chestObject->GetAllItems().clear();

	delete chestObject;
}

void TestItemContainer::TestCustomConstructor(void) {
	CPPUNIT_ASSERT(backpackObject->GetItemName() == "testBackpack");
	CPPUNIT_ASSERT(backpackObject->GetItemType() == Backpack);

	CPPUNIT_ASSERT(wornItemsObject->GetItemName() == "testWornItems");
	CPPUNIT_ASSERT(wornItemsObject->GetItemType() == WornItems);

	CPPUNIT_ASSERT(chestObject->GetItemName() == "testChest");
	CPPUNIT_ASSERT(chestObject->GetItemType() == TreasureChest);
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

	Item* nullPointer = wornItemsObject->GetItem(8);
	CPPUNIT_ASSERT(nullPointer == nullptr);
}

void TestItemContainer::TestAddNewItem(void) {
	int backpackItemSize = backpackObject->GetAllItems().size();

	int wornItemsSize = wornItemsObject->GetAllItems().size();

	int chestItemSize = chestObject->GetAllItems().size();

	Item* newItem = new Item("newItem", 4, Shield, ArmorClass);

	backpackObject->AddNewItem(*newItem);
	int currentBackpackItemSize = backpackObject->GetAllItems().size();
	CPPUNIT_ASSERT(currentBackpackItemSize == backpackItemSize + 1 && currentBackpackItemSize == BACKPACK_ITEM_SIZE);
	CPPUNIT_ASSERT(backpackObject->GetAllItems().back() == *newItem);

	wornItemsObject->AddNewItem(*newItem);
	int currentWornItemSize = wornItemsObject->GetAllItems().size();
	CPPUNIT_ASSERT(currentWornItemSize == wornItemsSize + 1 && currentWornItemSize >= WORN_ITEMS_SIZE);
	CPPUNIT_ASSERT(wornItemsObject->GetAllItems().back() == *newItem);

	chestObject->AddNewItem(*newItem);
	int currentChestItemSize = chestObject->GetAllItems().size();
	CPPUNIT_ASSERT(currentChestItemSize == chestItemSize + 1 && currentChestItemSize <= CHEST_ITEM_SIZE);
	CPPUNIT_ASSERT(chestObject->GetAllItems().back() == *newItem);
}

void TestItemContainer::TestGetAllItems(void) {
	vector<Item> backpackItems = backpackObject->GetAllItems();
	CPPUNIT_ASSERT(backpackItems.size() == BACKPACK_ITEM_SIZE - 1);
	
	vector<Item> wornItems = wornItemsObject->GetAllItems();
	CPPUNIT_ASSERT(wornItems.size() == WORN_ITEMS_SIZE);
	
	vector<Item> chestItems = chestObject->GetAllItems();
	CPPUNIT_ASSERT(chestItems.size() == CHEST_ITEM_SIZE - 2);
}

void TestItemContainer::TestGetItemsByBonus(void) {
	vector<Item> backpackPlusOneItems = backpackObject->GetItemsByEnchantmentBonus(1);
	int returnedPlusOneBackPackItemVectorSize = backpackPlusOneItems.size();
	CPPUNIT_ASSERT(returnedPlusOneBackPackItemVectorSize >= 0 && returnedPlusOneBackPackItemVectorSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> backpackPlusTwoItems = backpackObject->GetItemsByEnchantmentBonus(2);
	int returnedPlusTwoBackPackItemVectorSize = backpackPlusTwoItems.size();
	CPPUNIT_ASSERT(returnedPlusTwoBackPackItemVectorSize >= 0 && returnedPlusTwoBackPackItemVectorSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> backpackPlusThreeItems = backpackObject->GetItemsByEnchantmentBonus(3);
	int returnedPlusThreeBackpackItemVectorSize = backpackPlusThreeItems.size();
	CPPUNIT_ASSERT(returnedPlusThreeBackpackItemVectorSize >= 0 && returnedPlusThreeBackpackItemVectorSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> backpackPlusFourItems = backpackObject->GetItemsByEnchantmentBonus(4);
	int returnedPlusFourBackpackItemVectorSize = backpackPlusFourItems.size();
	CPPUNIT_ASSERT(returnedPlusFourBackpackItemVectorSize >= 0 && returnedPlusFourBackpackItemVectorSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> backpackPlusFiveItems = backpackObject->GetItemsByEnchantmentBonus(5);
	int returnedPlusFiveBackpackItemVectorSize = backpackPlusFiveItems.size();
	CPPUNIT_ASSERT(returnedPlusFiveBackpackItemVectorSize >= 0 && returnedPlusFiveBackpackItemVectorSize <= BACKPACK_ITEM_SIZE);

	vector<Item> plusOneWornItems = wornItemsObject->GetItemsByEnchantmentBonus(1);
	CPPUNIT_ASSERT(plusOneWornItems.size() == WORN_ITEMS_PLUS_ONE_ITEMS_SIZE);

	vector<Item> plusTwoWornItems = wornItemsObject->GetItemsByEnchantmentBonus(2);
	CPPUNIT_ASSERT(plusTwoWornItems.size() == WORN_ITEMS_PLUS_TWO_ITEMS_SIZE);
	
	vector<Item> plusThreeWornItems = wornItemsObject->GetItemsByEnchantmentBonus(3);
	CPPUNIT_ASSERT(plusThreeWornItems.size() == WORN_ITEMS_PLUS_THREE_ITEMS_SIZE);
	
	vector<Item> plusFourWornItems = wornItemsObject->GetItemsByEnchantmentBonus(4);
	CPPUNIT_ASSERT(plusFourWornItems.size() == WORN_ITEMS_PLUS_FOUR_ITEMS_SIZE);
	
	vector<Item> plusFiveWornItems = wornItemsObject->GetItemsByEnchantmentBonus(5);
	CPPUNIT_ASSERT(plusFiveWornItems.size() == WORN_ITEMS_PLUS_FIVE_ITEMS_SIZE);

	vector<Item> chestPlusOneItems = chestObject->GetItemsByEnchantmentBonus(1);
	int returnedPlusOneChestItemVectorSize = chestPlusOneItems.size();
	CPPUNIT_ASSERT(returnedPlusOneChestItemVectorSize >= 0 && returnedPlusOneChestItemVectorSize <= CHEST_ITEM_SIZE);

	vector<Item> chestPlusTwoItems = chestObject->GetItemsByEnchantmentBonus(2);
	int returnedPlusTwoChestItemVectorSize = chestPlusTwoItems.size();
	CPPUNIT_ASSERT(returnedPlusTwoChestItemVectorSize >= 0 && returnedPlusTwoChestItemVectorSize <= CHEST_ITEM_SIZE);

	vector<Item> chestPlusThreeItems = chestObject->GetItemsByEnchantmentBonus(3);
	int returnedPlusThreeChestItemVectorSize = chestPlusThreeItems.size();
	CPPUNIT_ASSERT(returnedPlusThreeChestItemVectorSize >= 0 && returnedPlusThreeChestItemVectorSize <= CHEST_ITEM_SIZE);

	vector<Item> chestPlusFourItems = chestObject->GetItemsByEnchantmentBonus(4);
	int returnedPlusFourChestItemVectorSize = chestPlusFourItems.size();
	CPPUNIT_ASSERT(returnedPlusFourChestItemVectorSize >= 0 && returnedPlusFourChestItemVectorSize <= CHEST_ITEM_SIZE);

	vector<Item> chestPlusFiveItems = chestObject->GetItemsByEnchantmentBonus(5);
	int returnedPlusFiveChestItemVectorSize = chestPlusFiveItems.size();
	CPPUNIT_ASSERT(returnedPlusFiveChestItemVectorSize >= 0 && returnedPlusFiveChestItemVectorSize <= CHEST_ITEM_SIZE);
}

void TestItemContainer::TestGetItemsByType(void) {
	vector<Item> helmetBackpackItems = backpackObject->GetItemsByItemType(Helmet);
	int helmetBackpackItemsSize = helmetBackpackItems.size();
	CPPUNIT_ASSERT(helmetBackpackItemsSize >= 0 && helmetBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> armorBackpackItems = backpackObject->GetItemsByItemType(Armor);
	int armorBackpackItemsSize = armorBackpackItems.size();
	CPPUNIT_ASSERT(armorBackpackItemsSize >= 0 && armorBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> shieldBackpackItems = backpackObject->GetItemsByItemType(Shield);
	int shieldBackpackItemsSize = shieldBackpackItems.size();
	CPPUNIT_ASSERT(shieldBackpackItemsSize >= 0 && shieldBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> ringBackpackItems = backpackObject->GetItemsByItemType(Ring);
	int ringBackpackItemsSize = ringBackpackItems.size();
	CPPUNIT_ASSERT(ringBackpackItemsSize >= 0 && ringBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> beltBackpackItems = backpackObject->GetItemsByItemType(Belt);
	int beltBackpackItemsSize = beltBackpackItems.size();
	CPPUNIT_ASSERT(beltBackpackItemsSize >= 0 && beltBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> bootsBackpackItems = backpackObject->GetItemsByItemType(Boots);
	int bootsBackpackItemsSize = bootsBackpackItems.size();
	CPPUNIT_ASSERT(bootsBackpackItemsSize >= 0 && bootsBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> weaponBackpackItems = backpackObject->GetItemsByItemType(Weapon);
	int weaponBackpackItemsSize = weaponBackpackItems.size();
	CPPUNIT_ASSERT(weaponBackpackItemsSize >= 0 && weaponBackpackItemsSize <= BACKPACK_ITEM_SIZE);

	vector<Item> helmetWornItems = wornItemsObject->GetItemsByItemType(Helmet);
	CPPUNIT_ASSERT(helmetWornItems.size() == 1);
	
	vector<Item> armorWornItems = wornItemsObject->GetItemsByItemType(Armor);
	CPPUNIT_ASSERT(armorWornItems.size() == 1);
	
	vector<Item> shieldWornItems = wornItemsObject->GetItemsByItemType(Shield);
	CPPUNIT_ASSERT(armorWornItems.size() == 1);
	
	vector<Item> ringWornItems = wornItemsObject->GetItemsByItemType(Ring);
	CPPUNIT_ASSERT(ringWornItems.size() == 1);
	
	vector<Item> beltWornItems = wornItemsObject->GetItemsByItemType(Belt);
	CPPUNIT_ASSERT(beltWornItems.size() == 1);
	
	vector<Item> bootsWornItems = wornItemsObject->GetItemsByItemType(Boots);
	CPPUNIT_ASSERT(bootsWornItems.size() == 1);
	
	vector<Item> weaponWornItems = wornItemsObject->GetItemsByItemType(Weapon);
	CPPUNIT_ASSERT(weaponWornItems.size() == 1);

	vector<Item> helmetChestItems = chestObject->GetItemsByItemType(Helmet);
	int helmetChestItemsSize = helmetChestItems.size();
	CPPUNIT_ASSERT(helmetChestItemsSize >= 0 && helmetChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> armorChestItems = chestObject->GetItemsByItemType(Armor);
	int armorChestItemsSize = armorChestItems.size();
	CPPUNIT_ASSERT(armorChestItemsSize >= 0 && armorChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> shieldChestItems = chestObject->GetItemsByItemType(Shield);
	int shieldChestItemsSize = shieldChestItems.size();
	CPPUNIT_ASSERT(shieldChestItemsSize >= 0 && shieldChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> ringChestItems = chestObject->GetItemsByItemType(Ring);
	int ringChestItemsSize = ringChestItems.size();
	CPPUNIT_ASSERT(ringChestItemsSize >= 0 && ringChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> beltChestItems = chestObject->GetItemsByItemType(Belt);
	int beltChestItemsSize = beltChestItems.size();
	CPPUNIT_ASSERT(beltChestItemsSize >= 0 && beltChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> bootsChestItems = chestObject->GetItemsByItemType(Boots);
	int bootsChestItemsSize = bootsChestItems.size();
	CPPUNIT_ASSERT(bootsChestItemsSize >= 0 && bootsChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> weaponChestItems = chestObject->GetItemsByItemType(Weapon);
	int weaponChestItemsSize = weaponChestItems.size();
	CPPUNIT_ASSERT(weaponChestItemsSize >= 0 && weaponChestItemsSize <= CHEST_ITEM_SIZE);
}

void TestItemContainer::TestGetItemsByStat(void) {
	vector<Item> strengthBackpackItems = backpackObject->GetItemsByStat(Strength);
	int strengthBackpackItemsSize = strengthBackpackItems.size();
	CPPUNIT_ASSERT(strengthBackpackItemsSize >= 0 && strengthBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> dexterityBackpackItems = backpackObject->GetItemsByStat(Dexterity);
	int dexterityBackpackItemsSize = dexterityBackpackItems.size();
	CPPUNIT_ASSERT(dexterityBackpackItemsSize >= 0 && dexterityBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> constitutionBackpackItems = backpackObject->GetItemsByStat(Constitution);
	int constitutionBackpackItemsSize = constitutionBackpackItems.size();
	CPPUNIT_ASSERT(constitutionBackpackItemsSize >= 0 && constitutionBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> intelligenceBackpackItems = backpackObject->GetItemsByStat(Intelligence);
	int intelligenceBackpackItemsSize = intelligenceBackpackItems.size();
	CPPUNIT_ASSERT(intelligenceBackpackItemsSize >= 0 && intelligenceBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> wisdomBackpackItems = backpackObject->GetItemsByStat(Wisdom);
	int wisdomBackpackItemsSize = wisdomBackpackItems.size();
	CPPUNIT_ASSERT(wisdomBackpackItemsSize >= 0 && wisdomBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> charismaBackpackItems = backpackObject->GetItemsByStat(Charisma);
	int charismaBackpackItemsSize = charismaBackpackItems.size();
	CPPUNIT_ASSERT(charismaBackpackItemsSize >= 0 && charismaBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> armorClassBackpackItems = backpackObject->GetItemsByStat(ArmorClass);
	int armorClassBackpackItemsSize = armorClassBackpackItems.size();
	CPPUNIT_ASSERT(armorClassBackpackItemsSize >= 0 && armorClassBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> attackBonusBackpackItems = backpackObject->GetItemsByStat(AttackBonus);
	int attackBonusBackpackItemsSize = attackBonusBackpackItems.size();
	CPPUNIT_ASSERT(attackBonusBackpackItemsSize >= 0 && attackBonusBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> dmgBonusBackpackItems = backpackObject->GetItemsByStat(DamageBonus);
	int dmgBonusBackpackItemsSize = dmgBonusBackpackItems.size();
	CPPUNIT_ASSERT(dmgBonusBackpackItemsSize >= 0 && dmgBonusBackpackItemsSize <= BACKPACK_ITEM_SIZE);
	
	vector<Item> strengthWornItems = wornItemsObject->GetItemsByStat(Strength);
	CPPUNIT_ASSERT(strengthWornItems.size() == 1);
	
	vector<Item> dexterityWornItems = wornItemsObject->GetItemsByStat(Dexterity);
	CPPUNIT_ASSERT(dexterityWornItems.size() == 1);
	
	vector<Item> constitutionWornItems = wornItemsObject->GetItemsByStat(Constitution);
	CPPUNIT_ASSERT(constitutionWornItems.size() == 0);
	
	vector<Item> intelligenceWornItems = wornItemsObject->GetItemsByStat(Intelligence);
	CPPUNIT_ASSERT(intelligenceWornItems.size() == 1);
	
	vector<Item> wisdomWornItems = wornItemsObject->GetItemsByStat(Wisdom);
	CPPUNIT_ASSERT(wisdomWornItems.size() == 1);
	
	vector<Item> charismaWornItems = wornItemsObject->GetItemsByStat(Charisma);
	CPPUNIT_ASSERT(charismaWornItems.size() == 0);
	
	vector<Item> armorClassWornItems = wornItemsObject->GetItemsByStat(ArmorClass);
	CPPUNIT_ASSERT(armorClassWornItems.size() == 2);
	
	vector<Item> attackBonusWornItems = wornItemsObject->GetItemsByStat(AttackBonus);
	CPPUNIT_ASSERT(attackBonusWornItems.size() == 1);
	
	vector<Item> dmgBonusWornItems = wornItemsObject->GetItemsByStat(DamageBonus);
	CPPUNIT_ASSERT(dmgBonusWornItems.size() == 0);

	vector<Item> strengthChestItems = chestObject->GetItemsByStat(Strength);
	int strengthChestItemsSize = strengthChestItems.size();
	CPPUNIT_ASSERT(strengthChestItemsSize >= 0 && strengthChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> dexterityChestItems = chestObject->GetItemsByStat(Dexterity);
	int dexterityChestItemsSize = dexterityChestItems.size();
	CPPUNIT_ASSERT(dexterityChestItemsSize >= 0 && dexterityChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> constitutionChestItems = chestObject->GetItemsByStat(Constitution);
	int constitutionChestItemsSize = constitutionChestItems.size();
	CPPUNIT_ASSERT(constitutionChestItemsSize >= 0 && constitutionChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> intelligenceChestItems = chestObject->GetItemsByStat(Intelligence);
	int intelligenceChestItemsSize = intelligenceChestItems.size();
	CPPUNIT_ASSERT(intelligenceChestItemsSize >= 0 && intelligenceChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> wisdomChestItems = chestObject->GetItemsByStat(Wisdom);
	int wisdomChestItemsSize = wisdomChestItems.size();
	CPPUNIT_ASSERT(wisdomChestItemsSize >= 0 && wisdomChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> charismaChestItems = chestObject->GetItemsByStat(Charisma);
	int charismaChestItemsSize = charismaChestItems.size();
	CPPUNIT_ASSERT(charismaChestItemsSize >= 0 && charismaChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> armorClassChestItems = chestObject->GetItemsByStat(ArmorClass);
	int armorClassChestItemsSize = armorClassChestItems.size();
	CPPUNIT_ASSERT(armorClassChestItemsSize >= 0 && armorClassChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> attackBonusChestItems = chestObject->GetItemsByStat(AttackBonus);
	int attackBonusChestItemsSize = attackBonusChestItems.size();
	CPPUNIT_ASSERT(attackBonusChestItemsSize >= 0 && attackBonusChestItemsSize <= CHEST_ITEM_SIZE);

	vector<Item> dmgBonusChestItems = chestObject->GetItemsByStat(DamageBonus);
	int dmgBonusChestItemsSize = dmgBonusChestItems.size();
	CPPUNIT_ASSERT(dmgBonusChestItemsSize >= 0 && dmgBonusChestItemsSize <= CHEST_ITEM_SIZE);
}
