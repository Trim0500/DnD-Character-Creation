// #include <FL.H>
#include <FL/fl_ask.H>
#include "ItemEditor.h"

using std::cout;
using std::endl;
using std::to_string;

namespace CampaignEditor
{
	void ItemEditor::load_data()
	{
		std::cout << "updating items" << std::endl;
		// int i = this->get_item();
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
		populate_browser();
		browser->bottomline(browser->size());
		browser->select(browser->size());
		load_data();
	}
	void ItemEditor::save_data()
	{
		/* try {current_item->SetName(nameInput->value());} catch (std::exception& e) {}
		try {current_item->SetType(itemTypeInput->value());} catch (std::exception& e) {}
		try {current_item->SetWeight(weightInput->value());} catch (std::exception& e) {}
 */
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
		currentItemType = to_string(_loadedItemType);
		currentEnchantmentType = to_string(_loadedEnchantmentType);
		currentWeight = to_string(_loadedWeight);

		idInput->value(currentItemId.c_str());
		nameInput->value(currentItemName.c_str());
		itemTypeInput->value(currentItemType.c_str());
		weightInput->value(currentWeight.c_str());
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
				populate_browser();
				/* code */
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
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
}