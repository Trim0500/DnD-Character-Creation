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

		itemFieldPack->begin();

		capacityInput = new Fl_Float_Input(0, 0, w, height, "Capacity");

		itemsIDChoice = new Fl_Input_Choice(0, 0, w, height, "Items");
		itemsIDChoice->input()->readonly(true);

		itemFieldPack->end();
	}

	void ItemContainerEditor::load_data() {
		ItemEditor::load_data();

		std::cout << "[ItemContainerEditor/load_data] -- Updating containers" << std::endl;

		int i = browser->value();
		if (i <= items.size() && i > 0)
		{
			std::cout << "[ItemContainerEditor/load_data] -- Selected: " << i << std::endl;

			currentContainer = (ItemContainer*)browser->data(i);

			update_data();
		}
	}

	void ItemContainerEditor::create() {
		ItemContainer* container = new ItemContainer();
		containers.push_back(container);

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
				containerRecords = serializeItem::LoadItemContainerRecords(filepath);
				for (int i = 0; i < (int)containerRecords.size(); i++)
				{
					ItemContainer* savedContainer = new ItemContainer(containerRecords[i]->itemName, containerRecords[i]->itemtype, containerRecords[i]->capacity);
					savedContainer->SetItems(FindItemsByIDInput(containerRecords[i]->itemIDs, containerItems));
					containers.push_back(savedContainer);
				}

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
			containerRecords = serializeItem::LoadItemContainerRecords(filepath);
			for (int i = 0; i < (int)containerRecords.size(); i++)
			{
				ItemContainer* savedContainer = new ItemContainer(containerRecords[i]->itemName, containerRecords[i]->itemtype, containerRecords[i]->capacity);
				savedContainer->SetItems(FindItemsByIDInput(containerRecords[i]->itemIDs, containerItems));
				containers.push_back(savedContainer);
			}
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
				containerRecords = serializeItem::LoadItemContainerRecords(filepath);
				for (int i = 0; i < (int)containerRecords.size(); i++)
				{
					ItemContainer* savedContainer = new ItemContainer(containerRecords[i]->itemName, containerRecords[i]->itemtype, containerRecords[i]->capacity);
					savedContainer->SetItems(FindItemsByIDInput(containerRecords[i]->itemIDs, containerItems));
					containers.push_back(savedContainer);
				}
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
		currentContainer->SetItems(FindItemsByIDInput(currentContainerItemIDs, containerItems));

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

		containerItems.clear();

		for (int i = 0; i < (int)updatedItemList.size(); i++)
		{
			Item item = *updatedItemList[i];
			containerItems.push_back(item);
		}
	}
}
