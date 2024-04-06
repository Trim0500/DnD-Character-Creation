#include "BaseEditor.h"
#include "../ProjectSourceCode/itemcontainer.h"

namespace CampaignEditor
{
	class ItemContainerEditor : public BaseEditor
	{
	public:
		ItemContainerEditor(int x, int y, int w, int h);
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
		void set_items(std::vector<item::Item *> * i) {
			items = i;
		} 
	private:
		std::vector<itemcontainer::ItemContainer *> *itemcontainers;
		std::vector<item::Item *> *items;
	};
}