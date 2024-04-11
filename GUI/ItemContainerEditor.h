#pragma once

#include "ItemEditor.h"
#include "../ProjectSourceCode/Serialize/serializeItem.h"
#include "../ProjectSourceCode/Observer/Observer.h"

using namespace CampaignEditor;
using namespace serializeItem;
using namespace observer;

namespace itemcontainereditor {
	class ItemContainerEditor : public ItemEditor, public Observer {
		public:
			ItemContainerEditor(int x, int y, int w, int h);

			virtual ~ItemContainerEditor() {};

			void load_data();

			void create();

			void save();

			void open(std::string);

			void open();

			void save_as();

			void save_as(std::string);

			void save_data();

			void delete_entry();

			void update_data();

			void populate_browser();

			void update(std::string) override {};

			void update(void*) override;

			void update(const int&, const int&, const int&) override {};

			std::vector<ItemContainer*> GetEditorContainers() { return containers; };

			void SetEditorContainers(std::vector<ItemContainer*> _containers) { containers = _containers; };

			static void OnItemIDChoice(Fl_Widget* _widget, void* _handler) { ((ItemContainerEditor*)_handler)->HandleItemIDDropdown(); };

			static void HandleItemIDDropdown();
		private:
			Fl_Float_Input* capacityInput;

			static inline Fl_Input_Choice* itemsIDChoice;

			double loadedContainerCapacity;

			std::vector<Item> loadedContainerItems;

			static inline std::vector<Item> itemEditorItems;

			static inline ItemContainer* currentContainer;

			std::string currentCapacity;

			static inline std::string currentContainerItemIDs;

			std::vector<ItemContainer*> containers;

			std::vector<ItemContainerRecord*> containerRecords;
	};
}