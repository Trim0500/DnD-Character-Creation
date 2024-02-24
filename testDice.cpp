#include <iostream>
#include <string>
#include <sstream>

#include "testDice.h"

void TestDice::setUp(void){
	easy_query = "2d4";
	hard_query = "16d20+100";
	invalid_query = "1z20";
	just_add_query = "0d10+3";
	just_subtract_query = "0d20-4";
}

void TestDice::tearDown(void) {

}

int testRollMin(string query, int count){
	int i = 1;
	int r;
	int min_rolled;
	min_rolled = Dice::roll(query);
	while (i< count) {
		r = Dice::roll(query);
		min_rolled = min(min_rolled, r);
		i++;
	}
	return min_rolled;
}

int testRollMin(Dice &d, int count){
	int i = 1;
	int r;
	int min_rolled;
	min_rolled = d.roll();
	while (i< count) {
		r = d.roll();
		min_rolled = min(min_rolled, r);
		i++;
	}

	return min_rolled;
}

int testRollMax(string query, int count){
	int i = 1;
	int r;
	int max_rolled;
	max_rolled = Dice::roll(query);
	while (i< count) {
		r = Dice::roll(query);
		max_rolled = max(max_rolled, r);
		i++;
	}
	return max_rolled;
}

int testRollMax(Dice &d, int count){
	int i = 1;
	int r;
	int max_rolled;
	max_rolled  = d.roll();
	while (i< count) {
		r = d.roll();
		max_rolled = max(max_rolled, r);
		i++;
	}
	return max_rolled;
}

void TestDice::TestConstructor(void){
	Dice d1,d2,d3,d4;
	d1 = Dice(easy_query);
	d2 = Dice(hard_query);
	d3 = Dice(just_add_query);
	d4 = Dice(just_subtract_query);

	CPPUNIT_ASSERT(d1.get_leading_multiplier() == 2);
	CPPUNIT_ASSERT(d2.get_leading_multiplier() == 16);
	CPPUNIT_ASSERT(d3.get_leading_multiplier() == 0);
	CPPUNIT_ASSERT(d4.get_leading_multiplier() == 0);

	CPPUNIT_ASSERT(d1.get_die_sides() == 4);
	CPPUNIT_ASSERT(d2.get_die_sides() == 20);
	CPPUNIT_ASSERT(d3.get_die_sides() == 10);
	CPPUNIT_ASSERT(d4.get_die_sides() == 20);

	CPPUNIT_ASSERT(d1.get_addition() == 0);
	CPPUNIT_ASSERT(d2.get_addition() == 100);
	CPPUNIT_ASSERT(d3.get_addition() == 3);
	CPPUNIT_ASSERT(d4.get_addition() == -4);

}

void TestDice::TestFullRoll(void){
	int test[2];
	test[0] = testRollMin(easy_query, 10000);
	test[1] = testRollMax(easy_query, 10000);
	CPPUNIT_ASSERT(test[0] >= 2);
	CPPUNIT_ASSERT(test[1] <= 8);
	
	test[0] = testRollMin(just_add_query, 10000);
	test[1] = testRollMax(just_add_query, 10000);
	CPPUNIT_ASSERT(test[0] == 3);
	CPPUNIT_ASSERT(test[1] == 3);

	test[0] = testRollMin(hard_query, 10000);
	test[1] = testRollMax(hard_query, 10000);
	CPPUNIT_ASSERT(test[0] >= 116);
	CPPUNIT_ASSERT(test[1] <= 420);

	test[0] = testRollMin(just_subtract_query, 10000);
	test[1] = testRollMax(just_subtract_query, 10000);
	CPPUNIT_ASSERT(test[0] == -4);
	CPPUNIT_ASSERT(test[1] == -4);
}

void TestDice::TestStaticRoll(void){
	int r = Dice::roll(easy_query);
	CPPUNIT_ASSERT(2 <= r && r <= 8);
}

void TestDice::TestAddDice(void){
	Dice d1 = Dice(easy_query);
	d1.add_die();
	CPPUNIT_ASSERT(d1.get_leading_multiplier() == 3);
	d1.add_die(2);
	CPPUNIT_ASSERT(d1.get_leading_multiplier() == 5);
	d1.add_die(-3);
	CPPUNIT_ASSERT(d1.get_leading_multiplier() == 2);
}

void TestDice::TestInvalidQuery(void){
	//CPPUNIT_ASSERT_THROW(Dice(invalid_query), std::invalid_argument);

	//CPPUNIT_ASSERT_THROW(Dice("10d3"), std::invalid_argument);
	//CPPUNIT_ASSERT_THROW(Dice("10d13"), std::invalid_argument);
	//CPPUNIT_ASSERT_THROW(Dice("1d49"), std::invalid_argument);
	//CPPUNIT_ASSERT_THROW(Dice::roll(invalid_query), std::invalid_argument);
}

void TestDice::TestRollNoAddition(void) {

}


void TestDice::TestAllDice(void){
	Dice d4, d6, d8, d10, d12, d20, d100;
	d4 = Dice("1d4");
	d6 = Dice("1d6");
	d8 = Dice("1d8");
	d10 = Dice("1d10");
	d12 = Dice("1d12");
	d20 = Dice("1d20");
	d100 = Dice("1d100");

	int test[2];
	test[0] = testRollMin(d4, 10000);
	test[1] = testRollMax(d4, 10000);
	CPPUNIT_ASSERT(test[0] >= 1);
	CPPUNIT_ASSERT(test[1] <= 4);

	test[0] = testRollMin(d6, 10000);
	test[1] = testRollMax(d6, 10000);
	CPPUNIT_ASSERT(test[0] >= 1);
	CPPUNIT_ASSERT(test[1] <= 6);

	test[0] = testRollMin(d8, 10000);
	test[1] = testRollMax(d8, 10000);
	CPPUNIT_ASSERT(test[0] >= 1);
	CPPUNIT_ASSERT(test[1] <= 8);

	test[0] = testRollMin(d10, 10000);
	test[1] = testRollMax(d10, 10000);
	CPPUNIT_ASSERT(test[0] >= 1);
	CPPUNIT_ASSERT(test[1] <= 10);

	test[0] = testRollMin(d12, 10000);
	test[1] = testRollMax(d12, 10000);
	CPPUNIT_ASSERT(test[0] >= 1);
	CPPUNIT_ASSERT(test[1] <= 12);

	test[0] = testRollMin(d20, 10000);
	test[1] = testRollMax(d20, 10000);
	CPPUNIT_ASSERT(test[0] >= 1);
	CPPUNIT_ASSERT(test[1] <= 20);

	test[0] = testRollMin(d100, 10000);
	test[1] = testRollMax(d100, 10000);
	CPPUNIT_ASSERT(test[0] >= 1);
	CPPUNIT_ASSERT(test[1] <= 100);

}

void TestDice::TestAdditionNoRoll(){
	int test[2];

	test[0] = testRollMin(just_add_query, 10000);
	test[1] = testRollMax(just_add_query, 10000);
	CPPUNIT_ASSERT(test[0] == 3);
	CPPUNIT_ASSERT(test[1] == 3);

	Dice d1 = Dice(just_add_query);

	test[0] = testRollMin(d1, 10000);
	test[1] = testRollMax(d1, 10000);
	CPPUNIT_ASSERT(test[0] == 3);
	CPPUNIT_ASSERT(test[1] == 3);

	Dice d2 = Dice("0d12");

	test[0] = testRollMin(d2, 10000);
	test[1] = testRollMax(d2, 10000);
	CPPUNIT_ASSERT(test[0] == 0);
	CPPUNIT_ASSERT(test[1] == 0);

	Dice d3 = Dice("0d12+10");

	test[0] = testRollMin(d3, 10000);
	test[1] = testRollMax(d3, 10000);
	CPPUNIT_ASSERT(test[0] == 10);
	CPPUNIT_ASSERT(test[1] == 10);
}

void TestDice::TestSubtractionNoRoll(){
	int test[2] = {0,0};
	test[0] = testRollMin(just_subtract_query, 10000);
	test[1] = testRollMax(just_subtract_query, 10000);
	CPPUNIT_ASSERT(test[0] == -4);
	CPPUNIT_ASSERT(test[1] == -4);

	Dice d1 = Dice(just_subtract_query);
	test[0] = testRollMin(d1, 10000);
	test[1] = testRollMax(d1, 10000);
	CPPUNIT_ASSERT(test[0] == -4);
	CPPUNIT_ASSERT(test[1] == -4);

	Dice d2 = Dice("0d12");
	test[0] = testRollMin(d2, 10000);
	test[1] = testRollMax(d2, 10000);
	CPPUNIT_ASSERT(test[0] == 0);
	CPPUNIT_ASSERT(test[1] == 0);
	Dice d3 = Dice("0d12-10");
	test[0] = testRollMin(d3, 10000);
	test[1] = testRollMax(d3, 10000);
	CPPUNIT_ASSERT(test[0] == -10);
	CPPUNIT_ASSERT(test[1] == -10);
}