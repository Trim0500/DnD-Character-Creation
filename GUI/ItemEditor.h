#pragma once
#include <iostream>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Float_Input.H>

#include "../DnD Character Creation Source Code/item.h"
#include "../DnD Character Creation Source Code/Character.h"
// #include "../serializeItem.h"

#include "BaseEditor.h"

namespace CampaignEditor {
	class ItemEditor : public BaseEditor {
		friend class MainMenu;
		public:
			ItemEditor(int x, int y, int w, int h) : BaseEditor(x,y, w, h){
				const int margin = 100;
				const int width = 100;
				const int height = 50;
				const int padding = 50;
				g->begin();
				idInput = new Fl_Int_Input(0, 0, width, height, "Id");
				containerIdInput = new Fl_Int_Input(0, 0, width, height, "Container Id"); // temp
				nameInput = new Fl_Input(0, 0, width, height, "name");
				itemTypeInput = new Fl_Int_Input(0,0, width, height, "Item Type");
				weightInput = new Fl_Float_Input(0,0, width, height, "Weight");
				Fl_Button * button = new Fl_Button(margin, 0, width, height, "save");
				
				browser->callback(static_load_data,(void *)this);
				g->end();
			};
			void load_data();
			void create();
			void save();
			void open();
	protected:
		void populate_browser();

		private: 
			int get_item();
			std::vector<std::string> item_database;
			// UI Components

			Fl_Int_Input * idInput; // constant
			Fl_Int_Input * containerIdInput; // temp
			Fl_Input * nameInput;
			Fl_Int_Input * itemTypeInput;

			Fl_Float_Input * weightInput;

			// TODO: enchantment section 
			Fl_Int_Input * enchantmentBonusInput;
			Fl_Int_Input * enchantmentTypeInput;

			// Values loaded from file
			int _loadedItemId;
			int _loadedContainerId;
			std::string _loadedItemName;
			int _loadedEnchantmentBonus;
			item::ItemType _loadedItemType;
			item::CharacterStats _loadedEnchantmentType;
			float _loadedWeight;

			// Values currently in GUI
			int currentItemId;
			int currentContainerId;
			std::string currentItemName;
			int currentEnchantmentBonus;
			item::ItemType currentItemType;
			item::CharacterStats currentEnchantmentType;
			float currentWeight;


			std::vector<Item*> items;
			std::string current_file;
			/* 
			fields to have: 
			int itemId;
				int containerId;
				string itemName;
				int enchantmentBonus;
				ItemType itemtype;
				CharacterStats enchantmentType;
				float weight;
			 */

			/*
				buttons to have:
				save
				revert to last save
			*/

			;
	};
}