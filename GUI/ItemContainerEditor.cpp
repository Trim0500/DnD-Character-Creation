#include "ItemContainerEditor.h"
#include "../ProjectSourceCode/serializeItem.h"

using namespace serializeItem;
namespace CampaignEditor
{
	void ItemContainerEditor::save()
	{
		SaveItemContainers(filepath, *itemcontainers);
	}

	void ItemContainerEditor::populate_browser()
	{
		browser->clear();
		std::string label;
		for (ItemContainer *i : *itemcontainers)
		{
			label = std::to_string(i->GetItemId());
			browser->add(label.c_str(), i);
		}
	}
}
