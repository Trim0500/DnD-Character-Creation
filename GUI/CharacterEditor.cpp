#include <iostream>
#include <FL/fl_ask.H>
#include "CharacterEditor.h"

namespace CampaignEditor
{
	CharacterEditor::CharacterEditor(int x, int y, int w, int h) : BaseEditor(x, y, w, h) {

		const int margin = 100;
		const int width = 100;
		const int height = 40;
		const int padding = 50;

		g->begin();

		idInput = new Fl_Int_Input(0, 0, w, height, "Id");
		idInput->readonly(true);
		nameInput = new Fl_Input(0, 0, w, height, "name");
		characterClassInput = new Fl_Input_Choice(0, 0, w, height, "class");
		Fl_Input* _temp = characterClassInput->input();
		_temp->readonly(true);
		int s = 12;
		for (int i = 0; i < s; i++)
		{
			characterClassInput->add(current_character->Get_Class_String((Character::Character_Class)i).c_str());
		}
		hpInput = new Fl_Int_Input(0, 0, w, height, "HP");
		levelInput = new Fl_Int_Input(0, 0, w, height, "level");
		strInput = new Fl_Int_Input(0, 0, w, height, "Strength");
		dexInput = new Fl_Int_Input(0, 0, w, height, "Dexterity");
		consInput = new Fl_Int_Input(0, 0, w, height, "Constitution");
		intInput = new Fl_Int_Input(0, 0, w, height, "Intelligence");
		wisInput = new Fl_Int_Input(0, 0, w, height, "Wisdom");
		charInput = new Fl_Int_Input(0, 0, w, height, "Charisma");
		inventoryIDChoice = new Fl_Input_Choice(0, 0, w, height, "Inventory ID");
		inventoryIDChoice->input()->readonly(true);
		isPlayableChoice = new Fl_Input_Choice(0, 0, w, height, "Is Playable");
		isPlayableChoice->add(std::to_string(true).c_str());
		isPlayableChoice->add(std::to_string(false).c_str());


		Fl_Pack* b = new Fl_Pack(0, 0, w, height / 2);
		b->type(Fl_Pack::HORIZONTAL);
		Fl_Button* cancel = new Fl_Button(margin, 0, w / 4, height, "cancel");
		Fl_Button* apply = new Fl_Button(margin, 0, w / 4, height, "apply");
		b->end();
		cancel->callback(static_load_data, (void*)this);
		apply->callback(static_save_data, (void*)this);
		g->end();

	}

	void CharacterEditor::load_data()
	{
		std::cout << "updating characters" << std::endl;
		int i = browser->value();
		if (i <= characters.size() && i > 0)
		{
			std::cout << "selected: " << i << std::endl;
			current_character = (Character::Character*)browser->data(i);
			update_data();
		}
	}

	void CharacterEditor::create()
	{
		Character::Character* c = new Character::Character();
		characters.push_back(c);
		populate_browser();
		browser->bottomline(browser->size());
		browser->select(browser->size());
		load_data();
	}

	void CharacterEditor::save()
	{
		if (filepath.empty())
		{
			save_as();
		}
		else
		{
			try
			{
				for (Character::Character* t : characters) {
					serializecharacter::SaveCharacter(t, this->filepath+"\\");

				}
			}
			catch (const std::exception& e)
			{
				fl_alert("There was an error saving the file. Try using 'save as'");
			}
			try
			{
				std::vector<serializecharacter::CharacterRecord> records = serializecharacter::LoadAllCharacters(this->filepath);
				for (serializecharacter::CharacterRecord t : records) {
					characters.push_back(new Character::Character(t));
				}

				populate_browser();
				/* code */
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}

	void CharacterEditor::open(std::string)
	{
	}


	void CharacterEditor::save_as()
	{
		if (BaseEditor::save_as())
		{
			try
			{
				save();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		};
	}

	void CharacterEditor::save_data()
	{
		// TODO
		current_character->SetID(std::stoi(idInput->value()));
		current_character->Name(nameInput->value());
		current_character->Set_Ability_Score(Character::Abilities_Stats::Strength, std::stoi(strInput->value()));
		current_character->Set_Ability_Score(Character::Abilities_Stats::Dexterity, std::stoi(dexInput->value()));
		current_character->Set_Ability_Score(Character::Abilities_Stats::Constitution, std::stoi(consInput->value()));
		current_character->Set_Ability_Score(Character::Abilities_Stats::Intelligence, std::stoi(intInput->value()));
		current_character->Set_Ability_Score(Character::Abilities_Stats::Wisdom, std::stoi(wisInput->value()));
		current_character->Set_Ability_Score(Character::Abilities_Stats::Charisma, std::stoi(charInput->value()));
		current_character->SetClass(stocs(characterClassInput->value()));
		current_character->set_Level(stocs(characterClassInput->value()), std::stoi(levelInput->value()));
		current_character->setMaxHitPoints(std::stoi(hpInput->value()));
		
		int currentInventoryID = std::stoi(inventoryIDChoice->value());
		
		auto foundInventory = std::find_if(editorContainers.begin(),
											editorContainers.end(),
											[currentInventoryID](ItemContainer* container) { return container->GetItemId() == currentInventoryID; });
		current_character->SetInventory(*(*foundInventory));
		current_character->SetIsPlayerControlled(isPlayableChoice);

		populate_browser();
	}

	void CharacterEditor::delete_entry()
	{
		if (characters.size() < 0)
		{
			return;
		}
		int i = browser->value();
		if (i < 1 || i > characters.size())
		{
			return;
		};
		characters.erase(characters.begin() + (i - 1));
		browser->value(0);
		populate_browser();
	}

	void CharacterEditor::update_data()
	{
		_loadCharacterID = current_character->ID();
		_loadCharacterName = current_character->Name();
		_loadCharacterStr = current_character->Get_Ability_Score(Character::Abilities_Stats::Strength);
		_loadCharacterDex = current_character->Get_Ability_Score(Character::Abilities_Stats::Dexterity);
		_loadCharacterCons = current_character->Get_Ability_Score(Character::Abilities_Stats::Constitution);
		_loadCharacterInt = current_character->Get_Ability_Score(Character::Abilities_Stats::Intelligence);
		_loadCharacterWis = current_character->Get_Ability_Score(Character::Abilities_Stats::Wisdom);
		_loadCharacterChar = current_character->Get_Ability_Score(Character::Abilities_Stats::Charisma);
		_loadCharacterClass = current_character->GetClass();
		_loadCharacterLevel = current_character->Levels((Character::Character_Class)current_character->GetClass());
		_loadCharacterHP = current_character->Max_Hit_Points();
		if (!newCharacter) {
			loadedInventoryID = current_character->Inventory().GetItemId();
		}
		_loadCharacterIsPlayable = current_character->GetIsPlayerControlled();

		currentCharacterID = std::to_string(_loadCharacterID);
		currentCharacterName = _loadCharacterName;
		currentCharacterStr = std::to_string(_loadCharacterStr);
		currentCharacterDex = std::to_string(_loadCharacterDex);
		currentCharacterCons = std::to_string(_loadCharacterCons);
		currentCharacterInt = std::to_string(_loadCharacterInt);
		currentCharacterWis = std::to_string(_loadCharacterWis);
		currentCharacterChar = std::to_string(_loadCharacterChar);
		currentCharacterClass = current_character->Get_Class_String(_loadCharacterClass);
		currentCharacterLevel = std::to_string(_loadCharacterLevel);
		currentCharacterHP = std::to_string(_loadCharacterHP);
		if (!newCharacter) {
			currentInventoryID = std::to_string(loadedInventoryID);
		}
		currentCharacterIsPlayable = std::to_string(_loadCharacterIsPlayable);

		idInput->value(currentCharacterID.c_str());
		nameInput->value(currentCharacterName.c_str());
		strInput->value(currentCharacterStr.c_str());
		dexInput->value(currentCharacterDex.c_str());
		consInput->value(currentCharacterCons.c_str());
		intInput->value(currentCharacterInt.c_str());
		wisInput->value(currentCharacterWis.c_str());
		charInput->value(currentCharacterChar.c_str());
		characterClassInput->value(currentCharacterClass.c_str());
		levelInput->value(currentCharacterLevel.c_str());
		hpInput->value(currentCharacterHP.c_str());
		if (!newCharacter) {
			inventoryIDChoice->value(currentInventoryID.c_str());
		}
		isPlayableChoice->value(currentCharacterIsPlayable.c_str());
	}

	void CharacterEditor::populate_browser()
	{
		browser->clear();
		std::string label;
		for (Character::Character* i : characters)
		{
			label = std::to_string(i->ID()) + ": " + i->Name();
			browser->add(label.c_str(), i);
		}
	}

	Character::Character_Class CharacterEditor::stocs(const std::string s)
	{
		int j = 12;
		for (int i = 0; i < j; i++)
		{
			Character::Character_Class temp = (Character::Character_Class)i;
			if (s == current_character->Get_Class_String(temp))
			{
				return (Character::Character_Class)i;
			}
		}
	}

	int CharacterEditor::get_character()
	{
		return this->browser->value();
	}

}