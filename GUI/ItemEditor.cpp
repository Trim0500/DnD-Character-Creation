// #include <FL.H>
#include <FL/fl_ask.H>

#include "ItemEditor.h"

using std::cout;
using std::endl;
using std::to_string;

namespace CampaignEditor
{
	item::ItemType stoit(const std::string s)
	{
		for (int i = 0; i < 11; i++)
		{
			if (s == itemTypeStrings[i])
			{
				return static_cast<item::ItemType>(i + 1);
			}
		}
	}
	item::CharacterStats stocs(const std::string s)
	{
		for (int i = 0; i < 10; i++)
		{
			if (s == statStrings[i])
			{
				return static_cast<item::CharacterStats>(i);
			}
		}
	}
	ItemEditor::ItemEditor(int x, int y, int w, int h) : BaseEditor(x, y, w, h)
	{
		const int margin = 100;
		const int width = 100;
		const int height = 50;
		const int padding = 50;
		g->begin();
		itemFieldPack = new Fl_Pack(0, 0, w, 200);
		/*
			base item information
		*/
		idInput = new Fl_Int_Input(0, 0, w, height, "Id");
		idInput->readonly(true);
		nameInput = new Fl_Input(0, 0, w, height, "name");
		// itemTypeInput = new Fl_Int_Input(0, 0, w, height, "Item Type");
		itemTypeInput = new Fl_Input_Choice(0, 0, w, height, "Item Type");
		Fl_Input *_temp = itemTypeInput->input();
		_temp->readonly(true);
		int s = 7;
		for (int i = 0; i < s; i++)
		{
			itemTypeInput->add(item::itemTypeStrings[i].c_str());
		}
		weightInput = new Fl_Float_Input(0, 0, w, height, "Weight");

		/*
			enchantment information
		*/
		Fl_Pack *ench = new Fl_Pack(0, 0, w, 200);

		enchantmentTypeInput = new Fl_Input_Choice(0, 0, w, height, "Ench type");
		Fl_Input *__temp = enchantmentTypeInput->input();
		__temp->readonly(true);
		Fl_Menu_Button *mb = enchantmentTypeInput->menubutton();
		s = 9;
		for (int i = 0; i < s; i++)
		{
			mb->add(item::statStrings[i].c_str());
		}
		enchantmentBonusInput = new Fl_Int_Input(0, 0, w, height, "Ench Bonus");

		ench->end();

		itemFieldPack->end();

		Fl_Pack *b = new Fl_Pack(0, 0, w, height / 2);
		b->type(Fl_Pack::HORIZONTAL);
		Fl_Button *cancel = new Fl_Button(margin, 0, w / 4, height, "cancel");
		Fl_Button *apply = new Fl_Button(margin, 0, w / 4, height, "apply");
		b->end();
		cancel->callback(static_load_data, (void *)this);
		apply->callback(static_save_data, (void *)this);
		g->end();
	};
	void ItemEditor::load_data()
	{
		std::cout << "updating items" << std::endl;
		int i = browser->value();
		if (i <= items.size() && i > 0)
		{
			std::cout << "selected: " << i << std::endl;
			current_item = (Item *)browser->data(i);
			update_data();
		}
	}
	int ItemEditor::get_item()
	{
		return this->browser->value();
	}

	void ItemEditor::populate_browser()
	{
		browser->clear();
		std::string label;
		for (Item *i : items)
		{
			label = std::to_string(i->GetItemId()) + ": " + i->GetItemName();
			browser->add(label.c_str(), i);
		}
	}
	void ItemEditor::create()
	{
		Item *i = new Item();
		items.push_back(i);

		Notify();

		populate_browser();
		browser->bottomline(browser->size());
		browser->select(browser->size());
		load_data();
	}

	void ItemEditor::delete_entry()
	{
		if (items.size() < 0)
		{
			return;
		}
		int i = browser->value();
		if (i < 1 || i > items.size())
		{
			return;
		};
		items.erase(items.begin() + (i - 1));

		Notify();

		browser->value(0);
		populate_browser();
	}

	void ItemEditor::save_data()
	{
		// TODO
		current_item->SetItemID(std::stoi(idInput->value()));
		current_item->SetItemName(nameInput->value());
		current_item->SetItemType(stoit(itemTypeInput->value())); // TODO: change input to dropdown

		current_item->SetItemWeight(std::stof(weightInput->value()));

		current_item->SetEnchantmentType(stocs(enchantmentTypeInput->value()));
		current_item->SetEnchantmentBonus(std::stoi(enchantmentBonusInput->value()));

		populate_browser();
	}
	void ItemEditor::update_data()
	{
		_loadedItemId = current_item->GetItemId();
		// _loadedContainerId =- current_item->get
		_loadedItemName = current_item->GetItemName();
		_loadedEnchantmentBonus = current_item->GetEnchantmentBonus();
		_loadedItemType = current_item->GetItemType();
		_loadedEnchantmentType = current_item->GetEnchantmentType();
		_loadedWeight = current_item->GetItemWeight();

		currentItemId = to_string(_loadedItemId);
		currentItemName = _loadedItemName;
		currentEnchantmentBonus = to_string(_loadedEnchantmentBonus);
		currentItemType = item::itemTypeStrings[_loadedItemType - 1];
		currentWeight = to_string(_loadedWeight);

		idInput->value(currentItemId.c_str());
		nameInput->value(currentItemName.c_str());
		itemTypeInput->value(currentItemType.c_str());
		weightInput->value(currentWeight.c_str());
		currentEnchantmentType = item::statStrings[_loadedEnchantmentType];

		enchantmentTypeInput->value(currentEnchantmentType.c_str());
		enchantmentBonusInput->value(currentEnchantmentBonus.c_str());

		// idInput->value();
	}
	void ItemEditor::save()
	{
		if (filepath.empty())
		{
			save_as();
		}
		else
		{
			try
			{
				serializeItem::SaveItems(this->filepath, items);
			}
			catch (const std::exception &e)
			{
				fl_alert("There was an error saving the file. Try using 'save as'");
			}
			try
			{
				items = serializeItem::LoadItems(filepath);

				Notify();

				populate_browser();
				/* code */
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}
	void ItemEditor::open(std::string s)
	{
		filepath = s;
		try
		{
			items = serializeItem::LoadItems(filepath);

			Notify();
			/* code */
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
		try
		{
			populate_browser();
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	void ItemEditor::open()
	{
		// filepath = BaseEditor::open();
		if (BaseEditor::open())
		{
			try
			{
				items = serializeItem::LoadItems(filepath);

				Notify();
				/* code */
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
			try
			{
				populate_browser();
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		};
	}
	void ItemEditor::save_as()
	{
		if (BaseEditor::save_as())
		{
			try
			{
				save();
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		};
	}
	void ItemEditor::save_as(std::string s)
	{
		try
		{
			serializeItem::SaveItems(s, items);
		}
		catch (const std::exception &e)
		{
			fl_alert("There was an error saving the file. Try using 'save as'");
		}
	}

	void ItemEditor::Notify() {
		for (int i = 0; i < (int)observers.size(); i++)
		{
			observers[i]->update((void*)this);
		}
	}
}