#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>

#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>

#include <FL/Fl_Return_Button.H>
#include <vector>
#include "BaseEditor.h"
#include "../ProjectSourceCode/Map.h"

namespace CampaignEditor
{

	class MapCellButton : public Fl_Button
	{
		MapCellButton(int x, int y, int w, int h, std::string name) : Fl_Button(x, y, w, h, name.c_str()) {}

	public:
		void cell_type(Map::Cell_Type ct){this->ct = ct;};
		Map::Cell_Type cell_type() {return ct;}
	private:
			Map::Cell_Type ct;
	};
	class MapEditor : public BaseEditor
	{
	public:
		MapEditor(int x, int y, int w, int h) : BaseEditor(x, y, w, h) {
			side_bars = new Fl_Group(0,0,200, 200);
			Fl_Box *box = new Fl_Box(20,40,50,50,"Cell Editor");
			side_bars->end();
			// g->add(map_grid);
			g->begin();
			map_grid = new Fl_Group(0,0,500, 500, "Map");
			g->end();

		}
		void redraw_map();
		void load_map(Map::Map *m);
		void populate_browser();
		MapCellButton *get_cell(int x, int y) { return cell_buttons[y][x]; }
		void create();
		void load_data();
		void save_data();
		static void confirm(Fl_Widget *widget, void * f );
		static void hide (Fl_Widget *widget, void * f);
	protected:
		;

	private:
		int editor_height, editor_width;
		Fl_Group * map_grid;
		Fl_Group * side_bars;
		std::vector<std::vector<MapCellButton *>> cell_buttons;

		std::vector<Map::Map*> maps;

		int _new_x, _new_y; //internal only, used during dialog to create map;
		/*
		methods to implement: opening all the maps
		drawing all the tiles
		opening all item containers


		*/
	};

	class NewMapModal : public Fl_Window{
		public:
		NewMapModal() : Fl_Window(300, 200, "New Map"){
			in_x = new Fl_Int_Input(50, 10, 50, 30, "width");
			in_y = new Fl_Int_Input(150, 10, 50, 30, "height");
			in_x -> value("5");
			in_y -> value("5");
			// Fl_Button *cb = new Fl_Return_Button(10, 50, 100, 30, "Cancel");
			Fl_Return_Button *rb = new Fl_Return_Button(10, 50, 100, 30, "Create...");
			set_modal();
			// cb->callback(h, (void *)this);
			rb->callback(confirm, (void *)this);
		}
		int y() {return std::stoi(in_y->value());}
		int x() {return std::stoi(in_x->value());}
		int confirmed() {return _confirmed;}
		void static h(Fl_Widget * w, void * f) {
			((NewMapModal*)f)->hide(); 
		}
		void static confirm(Fl_Widget * w, void * f) {
			((NewMapModal*)f)->submit();
		}
		void submit() {
			if (std::string(in_x->value()).empty() || std::string(in_y->value()).empty()){
				_confirmed = false;
				std::cout << "inputs not filed" << std::endl;
				// TODO: display error to the user.
			} else {
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