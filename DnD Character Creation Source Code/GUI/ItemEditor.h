#pragma once
#include <iostream>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Pack.H>
// #include <FL/Fl_Flex.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Float_Input.H>

#include "../item.h"
#include "../Character.h"
// #include "../serializeItem.h"

namespace CampaignEditor {

	class ItemEditor : public Fl_Window {
		public:
			ItemEditor(int x, int y) : Fl_Window(x,y){
				const int margin = 100;
				const int width = 100;
				const int height = 50;
				const int padding = 30;
				int c_y = 10;
				Fl_Pack * _g = new Fl_Pack(0,0,300,640);
				itemBrowser = new Fl_Browser(margin, 20, 300, 500, "Items");
				_g->end();
				c_y = 10;
				Fl_Pack * g = new Fl_Pack(400,0,400,640);
				idInput = new Fl_Int_Input(margin, c_y, width, height, "Id");
				c_y += padding+height;
				containerIdInput = new Fl_Int_Input(margin, c_y, width, height, "Container Id"); // temp
				c_y += padding+height;
				nameInput = new Fl_Input(margin, c_y, width, height, "name");
				c_y += padding+height;
				itemTypeInput = new Fl_Int_Input(margin,c_y, width, height, "Item Type");
				c_y += padding+height;
				weightInput = new Fl_Float_Input(margin,c_y, width, height, "Weight");
				c_y += padding+height;
				Fl_Button * button = new Fl_Button(margin, c_y, width, height, "submit");
				// g->resizable();
				idInput->align(FL_ALIGN_TOP);
				containerIdInput->align(FL_ALIGN_TOP);
				itemTypeInput->align(FL_ALIGN_TOP);
				weightInput->align(FL_ALIGN_TOP);
				itemBrowser->align(FL_ALIGN_TOP);
				g->end();
				this->resizable(this);
			};

		private: 

			// Item browser
			Fl_Browser * itemBrowser;
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