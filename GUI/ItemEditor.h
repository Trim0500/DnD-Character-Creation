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

#include "../ProjectSourceCode/item.h"
#include "../ProjectSourceCode/Character.h"
#include "../ProjectSourceCode/serializeItem.h"

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
				idInput = new Fl_Int_Input(0, 0, w, height, "Id");
				idInput->readonly(true);
				nameInput = new Fl_Input(0, 0, w, height, "name");
				itemTypeInput = new Fl_Int_Input(0,0, w, height, "Item Type");
				weightInput = new Fl_Float_Input(0,0, w, height, "Weight");

				Fl_Pack * b = new Fl_Pack(0,0,w, height/2);
				b->type(Fl_Pack::HORIZONTAL);
				Fl_Button * cancel = new Fl_Button(margin, 0, w/4, height, "cancel");
				Fl_Button * apply = new Fl_Button(margin, 0, w/4, height, "apply");
				b->end();
				browser->callback(static_load_data,(void *)this);
				cancel->callback(static_load_data, (void*)this);
				apply->callback(static_save_data, (void*)this);
				g->end();
			};
			void load_data();
			void create();
			void save();
			void open();
			void save_as();
			void save_data();
	protected:
		void populate_browser();

		private: 
			void update_data();
			int get_item();
			std::vector<std::string> item_database;
			// UI Components

			Fl_Int_Input * idInput; // constant
			// Fl_Int_Input * containerIdInput; // temp
			Fl_Input * nameInput;
			Fl_Int_Input * itemTypeInput;

			Fl_Float_Input * weightInput;

			// TODO: enchantment section 
			Fl_Int_Input * enchantmentBonusInput;
			Fl_Int_Input * enchantmentTypeInput;

			// Values loaded from file
			int _loadedItemId;
			// int _loadedContainerId;
			std::string _loadedItemName;
			int _loadedEnchantmentBonus;
			item::ItemType _loadedItemType;
			item::CharacterStats _loadedEnchantmentType;
			float _loadedWeight;

			Item * current_item;
			// Values currently in GUI
			std::string currentItemId;
			std::string currentItemName;
			std::string currentEnchantmentBonus;
			std::string currentItemType;
			std::string currentEnchantmentType;
			std::string currentWeight;


			std::vector<Item*> items;
			// std::string current_file;
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