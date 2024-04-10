#pragma once

#include "ItemEditor.h"

using namespace CampaignEditor;

//#include "BaseEditor.h"
//#include "../ProjectSourceCode/Item/itemcontainer.h"

//namespace CampaignEditor
//{
//	class ItemContainerEditor : public BaseEditor
//	{
//	public:
//		ItemContainerEditor(int x, int y, int w, int h);
//		void load_data();
//		void create();
//		void save();
//		void open(std::string);
//		void open();
//		void save_as();
//		void save_as(std::string s);
//		void save_data();
//		void delete_entry();
//		void update_data();
//		void populate_browser();
//		void set_items(std::vector<item::Item *> * i) {
//			items = i;
//		} 
//	private:
//		std::vector<itemcontainer::ItemContainer *> *itemcontainers;
//		std::vector<item::Item *> *items;
//	};
//}

namespace itemcontainereditor {
	class ItemContainerEditor : public ItemEditor {
		public:
			ItemContainerEditor(int x, int y, int w, int h);

			/*void load_data();

			void create();

			void save();

			void open(std::string);

			void open();

			void save_as();

			void save_as(std::string s);

			void save_data();

			void delete_entry();

			void update_data();

			void populate_browser();*/

			std::vector<ItemContainer*> GetEditorContainers() { return containers; };

			void SetEditorContainers(std::vector<ItemContainer*> _containers) { containers = _containers; };
		private:
			Fl_Float_Input* capacityInput;

			Fl_Input_Choice* itemsIDChoice;

			double loadedContainerCapacity;

			std::vector<Item> containerItems;

			ItemContainer* currentContainer;

			std::string currentCapacity;

			std::string currentContainerItemIDs;

			std::vector<ItemContainer*> containers;
	};
}