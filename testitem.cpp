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
	CPPUNIT_ASSERT(noArgsItemObject->GetItemName() == "");
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentBonus() >= 1 && noArgsItemObject->GetEnchantmentBonus() <= 5);
	CPPUNIT_ASSERT(noArgsItemObject->GetItemType() >= 1 && noArgsItemObject->GetItemType() <= 7);
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentType() >= 1 && noArgsItemObject->GetEnchantmentType() <= 9);
}

void TestItem::TestItemConstructor(void) {
	CPPUNIT_ASSERT(customItemObject->GetItemName() == "testItem");
	CPPUNIT_ASSERT(customItemObject->GetEnchantmentBonus() == 3);
	CPPUNIT_ASSERT(customItemObject->GetItemType() == Ring);
	CPPUNIT_ASSERT(customItemObject->GetEnchantmentType() == Strength);
}

void TestItem::TestGetEnchantmentBonus(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentBonus() >= 1 && noArgsItemObject->GetEnchantmentBonus() <= 5);

	CPPUNIT_ASSERT(customItemObject->GetEnchantmentBonus() == 3);
}

void TestItem::TestGetEnchantmentType(void) {
	CPPUNIT_ASSERT(noArgsItemObject->GetEnchantmentType() >= 1 && noArgsItemObject->GetEnchantmentType() <= 9);

	CPPUNIT_ASSERT(customItemObject->GetEnchantmentType() == Strength);
}
