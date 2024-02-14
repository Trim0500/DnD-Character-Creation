/*!
* \file testitem.cpp
* \brief Test implementation for Item
*/

#include <iostream>
#include <string>
#include <sstream>

#include "testitem.h"

using namespace std;

void TestItem::setUp(void)
{
	noArgsItemObject = new Item();

	customItemObject = new Item("testItem", 3, Ring, Strength);

	//testItemCurrentId += 2;
}

void TestItem::tearDown(void)
{
	delete noArgsItemObject;

	delete customItemObject;
}

void TestItem::TestNoArgsItemConstructor(void) {
	//CPPUNIT_ASSERT(noArgsItemObject->GetItemId() == testItemCurrentId - 1);
	ostringstream name;
	name << noArgsItemObject->itemTypeStrings[noArgsItemObject->GetItemType() - 1]
			<< " +"
			<< to_string(noArgsItemObject->GetEnchantmentBonus())
			<< " ("
			<< noArgsItemObject->statStrings[noArgsItemObject->GetEnchantmentType()] << ")";
	CPPUNIT_ASSERT(noArgsItemObject->GetItemName() == name.str());
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentBonus() >= 1 && noArgsItemObject->GetEnchantmentBonus() <= 5);
	CPPUNIT_ASSERT(noArgsItemObject->GetItemType() >= Helmet && noArgsItemObject->GetItemType() <= Weapon);
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentType() >= Strength && noArgsItemObject->GetEnchantmentType() <= DamageBonus);
}

void TestItem::TestItemConstructor(void) {
	//CPPUNIT_ASSERT(customItemObject->GetItemId() == testItemCurrentId);
	CPPUNIT_ASSERT(customItemObject->GetItemName() == "testItem");
	CPPUNIT_ASSERT(customItemObject->GetEnchantmentBonus() == 3);
	CPPUNIT_ASSERT(customItemObject->GetItemType() == Ring);
	CPPUNIT_ASSERT(customItemObject->GetEnchantmentType() == Strength);
}

void TestItem::TestGetItemId(void) {
	//CPPUNIT_ASSERT(noArgsItemObject->GetItemId() == testItemCurrentId - 1);
	
	//CPPUNIT_ASSERT(customItemObject->GetItemId() == testItemCurrentId);
}

void TestItem::TestGetItemName(void) {
	ostringstream name;
	name << noArgsItemObject->itemTypeStrings[noArgsItemObject->GetItemType() - 1]
		<< " +"
		<< to_string(noArgsItemObject->GetEnchantmentBonus())
		<< " ("
		<< noArgsItemObject->statStrings[noArgsItemObject->GetEnchantmentType()] << ")";
	CPPUNIT_ASSERT(noArgsItemObject->GetItemName() == name.str());

	CPPUNIT_ASSERT(customItemObject->GetItemName() == "testItem");
}

void TestItem::TestGetEnchantmentBonus(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentBonus() >= 1 && noArgsItemObject->GetEnchantmentBonus() <= 5);

	CPPUNIT_ASSERT(customItemObject->GetEnchantmentBonus() == 3);
}

void TestItem::TestGetItemType(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetItemType() >= Helmet && noArgsItemObject->GetItemType() <= Weapon);

	CPPUNIT_ASSERT(customItemObject->GetItemType() == Ring);
}

void TestItem::TestGetEnchantmentType(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentType() >= Strength && noArgsItemObject->GetEnchantmentType() <= DamageBonus);

	CPPUNIT_ASSERT(customItemObject->GetEnchantmentType() == Strength);
}
