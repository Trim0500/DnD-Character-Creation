#pragma once
#include <iostream>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Scroll.H>

#include "../ProjectSourceCode/Item/item.h"
#include "../ProjectSourceCode/Character/Character.h"
#include "../ProjectSourceCode/Serialize/serializeItem.h"
#include "../ProjectSourceCode/Serialize/SerializeCharacter.h"

#include "BaseEditor.h"

namespace CampaignEditor
{
	class CharacterEditor : public BaseEditor
	{
		friend class MainMenu;
		public:
		CharacterEditor(int x, int y, int w, int h);
		void load_data();
		void create();
		void save();
		void open(std::string);
		void open();
		void save_as();
		//void save_as(std::string s);
		void save_data();
		void delete_entry();
		void update_data();
		void populate_browser();
		Character::Character_Class stocs(const std::string s);

		std::vector<Character::Character*> GetEditorCharacters() { return characters; };

		void SetEditorCharacters(std::vector<Character::Character*> _characters) { characters = _characters; };

		private:

			int get_character();
			Fl_Int_Input* idInput; // constant
			Fl_Input* nameInput;
			Fl_Int_Input* levelInput;
			Fl_Int_Input* strInput;
			Fl_Int_Input* dexInput;
			Fl_Int_Input* consInput;
			Fl_Int_Input* intInput;
			Fl_Int_Input* wisInput;
			Fl_Int_Input* charInput;
			Fl_Input_Choice *characterClassInput;
			Fl_Int_Input* hpInput;

			int _loadCharacterID;
			std::string _loadCharacterName;
			int _loadCharacterStr;
			int _loadCharacterDex;
			int _loadCharacterCons;
			int _loadCharacterInt;
			int _loadCharacterWis;
			int _loadCharacterChar;
			int _loadCharacterClass;
			int _loadCharacterLevel;
			int _loadCharacterHP;

			// Values currently in GUI
			std::string currentCharacterID;
			std::string currentCharacterName;
			std::string currentCharacterStr;
			std::string currentCharacterDex;
			std::string currentCharacterCons;
			std::string currentCharacterInt;
			std::string currentCharacterWis;
			std::string currentCharacterChar;
			std::string currentCharacterClass;
			std::string currentCharacterLevel;
			std::string currentCharacterHP;

			Character::Character* current_character;
			Fl_Scroll* character_scroll;
			std::vector<Character::Character *> characters;
	};
}