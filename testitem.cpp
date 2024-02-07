/*
* \file testitem.cpp
* \brief Test implementation for Item
*/

#include <iostream>

#include "testitem.h"

using namespace std;

void TestItem::setUp(void)
{
	noArgsItemObject = new Item();

	customItemObject = new Item("testItem", 3, 4, 1);
}

void TestItem::tearDown(void)
{
	delete noArgsItemObject;

	delete customItemObject;
}

void TestItem::TestNoArgsItemConstructor(void) {
	CPPUNIT_ASSERT(noArgsItemObject->itemName == "");
	CPPUNIT_ASSERT(noArgsItemObject->enchantmentBonus >= 1 && noArgsItemObject->enchantmentBonus <= 5);
	CPPUNIT_ASSERT(noArgsItemObject->itemType >= 1 && noArgsItemObject->itemType <= 7);
	CPPUNIT_ASSERT(noArgsItemObject->enchantmentType >= 1 && noArgsItemObject->enchantmentBonus <= 9);
}

void TestItem::TestItemConstructor(void) {
	CPPUNIT_ASSERT(customItemObject->itemName == "testItem");
	CPPUNIT_ASSERT(customItemObject->enchantmentBonus == 3);
	CPPUNIT_ASSERT(customItemObject->itemType == Ring);
	CPPUNIT_ASSERT(customItemObject->enchantmentType == Strength);
}

void TestItem::TestGetEnchantmentBonus(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentBonus() >= 1 && noArgsItemObject->GetEnchantmentBonus() <= 5);

	CPPUNIT_ASSERT(customItemObject->GetEnchantmentBonus() == 3);
}

void TestItem::TestGetEnchantmentType(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentType() >= 1 && noArgsItemObject->GetEnchantmentType() <= 9);

	CPPUNIT_ASSERT(customItemObject->GetEnchantmentType() == Strength);
}
