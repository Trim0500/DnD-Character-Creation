#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Return_Button.H>
#include <vector>

#include "BaseEditor.h"
#include "ItemEditor.h"
#include "CharacterEditor.h"
#include "ItemContainerEditor.h"
#include "../ProjectSourceCode/Map/Map.h"
#include "../ProjectSourceCode/Interactable/Interactable.h"
#include "../ProjectSourceCode/Observer/Observable.h"

using namespace observable;

namespace CampaignEditor
{
	const std::string Cell_Labels[6] = {" ", "w", "d", "c", "co", "i"};

	class MapCellButton : public Fl_Button
	{
	public:
		MapCellButton(int x, int y, int w, int h, int _x, int _y);

		//void cell_type(Map::Cell_Type ct) { this->ct = ct; };
		void cell_type(Interactable::Interactable* ct) { this->ct = ct; };

		//Map::Cell_Type cell_type() { return ct; }
		Interactable::Interactable* cell_type() { return ct; }

		void ID(int id) { this->id = id; }
		int ID() { return id; }
		int X() { return x; }
		int Y() { return y; }

		int handle(int e);
	private:
		Interactable::Interactable* ct;

		int id;
		int x, y;
		int current_l = 0;
	};
	
	class MapEditor : public BaseEditor, public Observable
	{
		friend class MainMenu;

		public:
			MapEditor(int x, int y, int w, int h);
			static MapCellButton *get_cell(int x, int y) { return mcbs[y][x]; }

			virtual ~MapEditor() {};

			void redraw_map();
			void populate_browser();
			void create();
			void open();
			void open(std::string);
			void save() { save_as(); };
			void save_as();
			void load_data();
			void update_data();
			void delete_entry();
			void save_data();

			void Attach(Observer* _observer) override { observers.push_back(_observer); };

			void Detach(Observer* _observer) override { observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end()); };

			void Notify() override;

			std::vector<Interactable::Interactable*> GetMapInteractables() { return mapInteractables; };

			void SetMapInteractables(std::vector<Interactable::Interactable*> _mapInteractables) { mapInteractables = _mapInteractables; };

			ItemEditor* GetItemEditor() { return itemEditor; };

			void SetItemEditor(ItemEditor* _itemEditor) { itemEditor = _itemEditor; };

			CharacterEditor* GetCharacterEditor() { return characterEditor; };

			void SetCharacterEditor(CharacterEditor* _characterEditor) { characterEditor = _characterEditor; };

			ItemContainerEditor* GetContainerEditor() { return containerEditor; };

			void SetContainerEditor(ItemContainerEditor* _containerEditor) { containerEditor = _containerEditor; };

			//void update_cell(int x, int y, Map::Cell_Type ct);
			void update_cell(int x, int y, Interactable::Interactable* ct);
			void update_cell(int x, int y, std::string ct);
			void update_cell(int x, int y, char ct);
			std::vector<Map::Map*>* GetEditorMaps() { return maps; };
			void set_maps(std::vector<Map::Map *> *m) { maps = m; }
			static void confirm(Fl_Widget *widget, void *f);
			static void hide(Fl_Widget *widget, void *f);

			static int GetEndCellBbuttonX() { return endCellX; };

			static int GetEndCellBbuttonY() { return endCellY; };

			int GetMapCellBbuttonX() { return mapCellButtonX; };

			void SetMapCellBbuttonX(const int& _mapCellButtonX) { mapCellButtonX = _mapCellButtonX; };

			int GetMapCellBbuttonY() { return mapCellButtonY; };

			void SetMapCellBbuttonY(const int& _mapCellButtonY) { mapCellButtonX = _mapCellButtonY; };

			static void UpdateCellObjectIDDropDownLabel(const int&, const int&);

			static void UpdateDropDown(const int&, const int&);

			static void InteractableIDDropdownCallBack(Fl_Widget* _widget, void* _mapEditor) { ((MapEditor*)_mapEditor)->HandleDropdownEvent(); };

			void HandleDropdownEvent();
		private:
			Fl_Scroll *map_grid;

			std::vector<Map::Map *> *maps;

			Map::Map *current_map;

			int _grid_x, _grid_y;

			static inline std::vector<std::vector<MapCellButton *>> mcbs;

			int _new_x, _new_y; // internal only, used during dialog to create map;

			static inline Fl_Box* cellSideBarTitle;

			static inline Fl_Input_Choice* objectIDChoiceList;

			static inline int endCellX, endCellY;

			static inline int mapCellButtonX, mapCellButtonY;

			static inline std::vector<Interactable::Interactable*> mapInteractables;

			static inline ItemEditor* itemEditor;

			static inline CharacterEditor* characterEditor;

			static inline ItemContainerEditor* containerEditor;

			std::vector<Observer*> observers;
	};

	class NewMapModal : public Fl_Window
	{
	public:
		NewMapModal() : Fl_Window(300, 200, "New Map")
		{
			in_x = new Fl_Int_Input(50, 10, 50, 30, "width");
			in_y = new Fl_Int_Input(150, 10, 50, 30, "height");
			in_x->value("5");
			in_y->value("5");
			// Fl_Button *cb = new Fl_Return_Button(10, 50, 100, 30, "Cancel");
			Fl_Return_Button *rb = new Fl_Return_Button(10, 50, 100, 30, "Create...");
			set_modal();
			// cb->callback(h, (void *)this);
			rb->callback(confirm, (void *)this);
		}
		int y() { return std::stoi(in_y->value()); }
		int x() { return std::stoi(in_x->value()); }
		int confirmed() { return _confirmed; }
		void static h(Fl_Widget *w, void *f)
		{
			((NewMapModal *)f)->hide();
		}
		void static confirm(Fl_Widget *w, void *f)
		{
			((NewMapModal *)f)->submit();
		}
		void submit()
		{
			if (std::string(in_x->value()).empty() || std::string(in_y->value()).empty())
			{
				_confirmed = false;
				std::cout << "inputs not filed" << std::endl;
				// TODO: display error to the user.
			}
			else
			{
				_confirmed = true;
				this->hide();
			}
		}

	private:
		int _x;
		int _y;
		bool _confirmed = false;
		Fl_Int_Input *in_x;
		Fl_Int_Input *in_y;
	};
}