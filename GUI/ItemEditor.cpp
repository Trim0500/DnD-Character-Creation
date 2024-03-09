#include "ItemEditor.h"

namespace CampaignEditor {
	void ItemEditor::load_data() {
		std::cout << "updating items" << std::endl;
		//int i = this->get_item();
		int i = browser->value();
		std::cout << "selected: " << i << std::endl;
	}
	int ItemEditor::get_item() {
		return this->browser->value();
	}

	void ItemEditor::populate_browser() {
		// TODO: load from item file
		std::string label;
		for (Item * i: items) {
			label = std::to_string(i->GetItemId()) + ": " + i->GetItemName();
			browser->add(label.c_str(), i);
		}
	}
	void ItemEditor::create() {
		// TODO: Create empty item;
	}

	void ItemEditor::save(){
		serializeItem::SaveItemContainers(this->filepath, items);
	}

	void ItemEditor::open() {
		filepath = BaseEditor::open();
		items = serializeItem::LoadItems(filepath);
	}
}