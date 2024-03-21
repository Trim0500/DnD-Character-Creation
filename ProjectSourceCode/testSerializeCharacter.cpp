#include "testSerializeCharacter.h"

void TestSerializeCharacter::setUp(void)
{
	characterObject = new Character::Character();
}

void TestSerializeCharacter::tearDown(void)
{
	delete characterObject;
	characterObject = nullptr;
}

void TestSerializeCharacter::TestSaveCharacter(void)
{
	CPPUNIT_ASSERT(serializecharacter::SaveCharacter(characterObject, ""));
}

void TestSerializeCharacter::TestLoadCharacter(void)
{

	serializecharacter::SaveCharacter(characterObject, "");
	filename = serializecharacter::FindCharacterFile(characterObject->ID(), "");
	serializecharacter::CharacterRecord record = serializecharacter::LoadCharacter(filename);
	CPPUNIT_ASSERT(record.id == characterObject->ID());
	CPPUNIT_ASSERT(record.name == characterObject->Name());
	CPPUNIT_ASSERT(record.max_hit_points == characterObject->Max_Hit_Points());
	CPPUNIT_ASSERT(record.hit_points == characterObject->Hit_Points());
	for (int i{ 0 };i < record.level.size();i++) {
		CPPUNIT_ASSERT(record.level.at(i) == characterObject->Levels((Character::Character_Class)i));
	}
	for (int i{ 0 }; i < record.ability_scores.size(); i++) {
		CPPUNIT_ASSERT(record.ability_scores.at(i) == characterObject->Ability_Score_Natural(i, 0));
	}

}

void TestSerializeCharacter::TestFindCharacterFile(void)
{
	serializecharacter::SaveCharacter(characterObject, "");
	std::string testName = "Character_" + std::to_string(characterObject->ID()) + ".csv";
	filename = serializecharacter::FindCharacterFile(characterObject->ID(),"");
	CPPUNIT_ASSERT(testName.compare(filename));
}
