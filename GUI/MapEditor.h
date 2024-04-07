#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>

#include <FL/Fl_Return_Button.H>
#include <vector>
#include "BaseEditor.h"
#include "../ProjectSourceCode/Map/Map.h"
#include "../ProjectSourceCode/Interactable/Interactable.h"

namespace CampaignEditor
{
	const std::string Cell_Labels[4] = {" ", "w", "i", "c"};
	class MapCellButton : public Fl_Button
	{
	public:
		MapCellButton(int x, int y, int w, int h, int _x, int _y);

		//void cell_type(Map::Cell_Type ct) { this->ct = ct; };
		void cell_type(Interactable::Interactable* ct) { this->ct = ct; };

		//Map::Cell_Type cell_type() { return ct; }
		Interactable::Interactable * cell_type() { return ct; }

		int X() { return x; }
		int Y() { return y; }
		int handle(int e);

	private:
		//Map::Cell_Type ct;
		Interactable::Interactable * ct;

		int x, y;
		int current_l = 0;
	};
	class MapEditor : public BaseEditor
	{
		friend class MainMenu;

	public:
		MapEditor(int x, int y, int w, int h);
		MapCellButton *get_cell(int x, int y) { return mcbs[y][x]; }

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
		//void update_cell(int x, int y, Map::Cell_Type ct);
		void update_cell(int x, int y, Interactable::Interactable* ct);
		void update_cell(int x, int y, std::string ct);
		void update_cell(int x, int y, char ct);
		void set_maps(std::vector<Map::Map *> *m) { maps = m; }
		static void confirm(Fl_Widget *widget, void *f);
		static void hide(Fl_Widget *widget, void *f);

	private:
		Fl_Scroll *map_grid;
		std::vector<Map::Map *> *maps;
		Map::Map *current_map;
		int _grid_x, _grid_y;
		std::vector<std::vector<MapCellButton *>> mcbs;
		int _new_x, _new_y; // internal only, used during dialog to create map;
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