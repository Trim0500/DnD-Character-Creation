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

#include "BaseEditor.h"
#include "../ProjectSourceCode/Item/item.h"
#include "../ProjectSourceCode/Character/Character.h"
#include "../ProjectSourceCode/Serialize/serializeItem.h"
#include "../ProjectSourceCode/Observer/Observable.h"

using namespace observable;

namespace CampaignEditor
{
	class ItemEditor : public BaseEditor, public Observable
	{
		friend class MainMenu; 

	public:
		ItemEditor(int x, int y, int w, int h);

		virtual ~ItemEditor() {};

		void load_data();

		void create();

		void save();

		void open(std::string);

		void open();

		void save_as();

		void save_as(std::string s);

		void save_data();

		void delete_entry();

		void update_data();

		void populate_browser();

		void Attach(Observer* _observer) override { observers.push_back(_observer); };

		void Detach(Observer* _observer) override { observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end()); };

		void Notify() override;

		std::vector<Item*> GetEditorItems() { return items; };

		void SetEditorItems(std::vector<Item*> _items) { items = _items; };
	protected:
		int get_item();

		std::vector<std::string> item_database;
		// UI Components

		Fl_Pack* itemFieldPack;

		Fl_Int_Input *idInput; // constant

		Fl_Input *nameInput;

		Fl_Input_Choice *itemTypeInput;

		Fl_Float_Input *weightInput;

		// TODO: enchantment section
		Fl_Int_Input *enchantmentBonusInput;

		Fl_Input_Choice *enchantmentTypeInput;

		// Values loaded from file
		int _loadedItemId;

		// int _loadedContainerId;

		std::string _loadedItemName;

		int _loadedEnchantmentBonus;

		item::ItemType _loadedItemType;

		item::CharacterStats _loadedEnchantmentType;

		float _loadedWeight;

		Item *current_item;

		// Values currently in GUI
		std::string currentItemId;

		std::string currentItemName;

		std::string currentEnchantmentBonus;

		std::string currentItemType;

		std::string currentEnchantmentType;

		std::string currentWeight;

		std::vector<Item *> items;
	private:
		std::vector<Observer*> observers;
	};
}