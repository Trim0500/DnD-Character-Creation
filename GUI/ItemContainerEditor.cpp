//#include "../ProjectSourceCode/Serialize/serializeItem.h"

//using namespace serializeItem;
//namespace CampaignEditor
//{
//	void ItemContainerEditor::save()
//	{
//		SaveItemContainers(filepath, *itemcontainers);
//	}
//
//	void ItemContainerEditor::populate_browser()
//	{
//		browser->clear();
//		std::string label;
//		for (ItemContainer *i : *itemcontainers)
//		{
//			label = std::to_string(i->GetItemId());
//			browser->add(label.c_str(), i);
//		}
//	}
//}

#include "ItemContainerEditor.h"

namespace {

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
}
