#include <string>
#include <sstream>
#include <FL/fl_ask.H>
#include <regex>
#include <algorithm>

#include "ItemContainerEditor.h"

namespace {
	std::string BuildItemIDInput(std::vector<Item>* _idVector) {
		std::ostringstream result;

		for (int i = 0; i < (int)_idVector->size(); i++)
		{
			if (i == _idVector->size() - 1) {
				result << _idVector->at(i).GetItemId();

				break;
			}

			result << _idVector->at(i).GetItemId() << ",";
		}

		return result.str();
	}

	std::vector<Item> FindItemsByIDInput(std::string _idInput, std::vector<Item> itemsToSearch) {
		std::vector<Item> result;

		std::vector<int> idVector;

		std::smatch match;

		std::regex numberRgx("[0-9]+");

		while (regex_search(_idInput, match, numberRgx)) {
			idVector.push_back(std::stoi(match.str()));

			_idInput = match.suffix().str();
		}

		for (int id : idVector)
		{
			auto foundItem = std::find_if(itemsToSearch.begin(),
											itemsToSearch.end(),
											[id](Item item) { return item.GetItemId() == id; });
			if (foundItem != itemsToSearch.end()) {
				result.push_back((*foundItem));
			}
		}

		return result;
	}

	std::vector<Item> FindItemsByIDInput(std::vector<int> _idInput, std::vector<Item> itemsToSearch) {
		std::vector<Item> result;

		for (int id : _idInput)
		{
			auto foundItem = std::find_if(itemsToSearch.begin(),
											itemsToSearch.end(),
											[id](Item item) { return item.GetItemId() == id; });
			if (foundItem != itemsToSearch.end()) {
				result.push_back((*foundItem));
			}
		}

		return result;
	}
}

namespace itemcontainereditor {
	ItemContainerEditor::ItemContainerEditor(int x, int y, int w, int h) : ItemEditor(x, y, w, h) {
		const int height = 50;

		enchantmentBonusInput->value(std::to_string(0).c_str());
		enchantmentBonusInput->readonly(true);

		enchantmentTypeInput->clear();
		enchantmentTypeInput->value(item::statStrings[9].c_str());

		itemTypeInput->clear();
		for (int i = 7; i < 11; i++)
		{
			if (i == 8) {
				continue;
			}

			itemTypeInput->add(item::itemTypeStrings[i].c_str());
		}

		itemFieldPack->begin();

		capacityInput = new Fl_Float_Input(0, 0, w, height, "Capacity");

		itemsIDChoice = new Fl_Input_Choice(0, 0, w, height, "Items");
		itemsIDChoice->input()->readonly(true);
		itemsIDChoice->callback(OnItemIDChoice, (void*)this);

		itemFieldPack->end();
	}

	void ItemContainerEditor::load_data() {
		ItemEditor::load_data();

		std::cout << "[ItemContainerEditor/load_data] -- Updating containers" << std::endl;

		int i = browser->value();
		if (i <= containers.size() && i > 0)
		{
			std::cout << "[ItemContainerEditor/load_data] -- Selected: " << i << std::endl;

			currentContainer = (ItemContainer*)browser->data(i);

			update_data();
		}
	}

	void ItemContainerEditor::create() {
		ItemContainer* container = new ItemContainer("New Container", item::ItemType::Inventory, 30.0);
		containers.push_back(container);

		items.push_back(static_cast<Item*>(container));

		Notify();

		populate_browser();

		browser->bottomline(browser->size());
		browser->select(browser->size());

		load_data();
	}

	void ItemContainerEditor::save() {
		if (filepath.empty())
		{
			save_as();
		}
		else
		{
			try
			{
				serializeItem::SaveItemContainers(this->filepath, containers);
			}
			catch (const std::exception& e)
			{
				fl_alert("There was an error saving the file. Try using 'save as'");
			}

			try
			{
				containers.clear();

				items.clear();

				containerRecords = serializeItem::LoadItemContainerRecords(filepath);
				for (int i = 0; i < (int)containerRecords.size(); i++)
				{
					std::vector<Item> containerItems = FindItemsByIDInput(containerRecords[i]->itemIDs, itemEditorItems);
					ItemContainer* savedContainer = new ItemContainer(containerRecords[i]->containerId,
																		containerRecords[i]->itemName,
																		0, 
																		containerRecords[i]->itemtype,
																		item::CharacterStats::NA,
																		containerRecords[i]->weight,
																		containerRecords[i]->capacity,
																		containerItems);
					containers.push_back(savedContainer);

					items.push_back(static_cast<Item*>(savedContainer));
				}

				Notify();

				populate_browser();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}

	void ItemContainerEditor::open(std::string _filePath) {
		try
		{
			containers.clear();

			items.clear();

			containerRecords = serializeItem::LoadItemContainerRecords(filepath);
			for (int i = 0; i < (int)containerRecords.size(); i++)
			{
				std::vector<Item> containerItems = FindItemsByIDInput(containerRecords[i]->itemIDs, itemEditorItems);
				ItemContainer* savedContainer = new ItemContainer(containerRecords[i]->containerId,
																	containerRecords[i]->itemName,
																	0,
																	containerRecords[i]->itemtype,
																	item::CharacterStats::NA,
																	containerRecords[i]->weight,
																	containerRecords[i]->capacity,
																	containerItems);
				containers.push_back(savedContainer);

				items.push_back(static_cast<Item*>(savedContainer));
			}

			Notify();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

		try
		{
			populate_browser();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

	void ItemContainerEditor::open() {
		if (BaseEditor::open())
		{
			try
			{
				containers.clear();

				items.clear();

				containerRecords = serializeItem::LoadItemContainerRecords(filepath);
				for (int i = 0; i < (int)containerRecords.size(); i++)
				{
					std::vector<Item> containerItems = FindItemsByIDInput(containerRecords[i]->itemIDs, itemEditorItems);
					ItemContainer* savedContainer = new ItemContainer(containerRecords[i]->containerId,
																		containerRecords[i]->itemName,
																		0,
																		containerRecords[i]->itemtype,
																		item::CharacterStats::NA,
																		containerRecords[i]->weight,
																		containerRecords[i]->capacity,
																		containerItems);
					containers.push_back(savedContainer);

					items.push_back(static_cast<Item*>(savedContainer));
				}

				Notify();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}

			try
			{
				populate_browser();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		};
	}

	void ItemContainerEditor::save_as() {
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

	void ItemContainerEditor::save_as(std::string _filePath) {
		try
		{
			serializeItem::SaveItemContainers(_filePath, containers);
		}
		catch (const std::exception& e)
		{
			fl_alert("There was an error saving the file. Try using 'save as'");
		}
	}

	void ItemContainerEditor::save_data() {
		ItemEditor::save_data();

		currentContainer->SetCapacity(std::stof(capacityInput->value()));
		currentContainer->SetItems(FindItemsByIDInput(currentContainerItemIDs, itemEditorItems));

		populate_browser();
	}

	void ItemContainerEditor::delete_entry() {
		if (containers.size() < 0)
		{
			return;
		}

		int i = browser->value();
		if (i < 1 || i > containers.size())
		{
			return;
		};

		containers.erase(containers.begin() + (i - 1));

		items.erase(items.begin() + (i - 1));

		Notify();

		browser->value(0);

		populate_browser();
	}

	void ItemContainerEditor::update_data() {
		loadedContainerCapacity = currentContainer->GetCapacity();
		loadedContainerItems = currentContainer->GetAllItems();

		currentCapacity = std::to_string(loadedContainerCapacity);
		currentContainerItemIDs = BuildItemIDInput(&loadedContainerItems);

		capacityInput->value(currentCapacity.c_str());
		itemsIDChoice->value(currentContainerItemIDs.c_str());
	}

	void ItemContainerEditor::populate_browser() {
		ItemEditor::populate_browser();
	}

	void ItemContainerEditor::update(void* _observable) {
		std::vector<Item*> updatedItemList = ((ItemEditor*)_observable)->GetEditorItems();

		itemEditorItems.clear();

		for (int i = 0; i < (int)updatedItemList.size(); i++)
		{
			Item item = *updatedItemList[i];
			itemEditorItems.push_back(item);
		}

		Fl_Input* _temp = itemsIDChoice->input();
		_temp->readonly(true);
		for (int i = 0; i < (int)itemEditorItems.size(); i++)
		{
			itemsIDChoice->add(std::to_string(itemEditorItems[i].GetItemId()).c_str());
		}
	}

	void ItemContainerEditor::Notify() {
		for (int i = 0; i < (int)observers.size(); i++)
		{
			observers[i]->update((void*)this);
		}
	}

	void ItemContainerEditor::HandleItemIDDropdown() {
		std::ostringstream updatedItemIDText;
		if (currentContainerItemIDs.empty()) {
			updatedItemIDText << itemsIDChoice->value();
		}
		else {
			updatedItemIDText << currentContainerItemIDs << "," << itemsIDChoice->value();
		}

		currentContainerItemIDs = updatedItemIDText.str();
		itemsIDChoice->value(currentContainerItemIDs.c_str());

		currentContainer->SetItems(FindItemsByIDInput(currentContainerItemIDs, itemEditorItems));
	}
}
