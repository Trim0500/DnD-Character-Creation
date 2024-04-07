#pragma once

#include <FL/Fl_Pack.H>
#include <FL/Fl_Scroll.H>
#include "BaseEditor.h"
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input_Choice.H>
#include "../ProjectSourceCode/Campaign/campaign.h"

using namespace campaign;
using std::vector;
namespace CampaignEditor
{
	class MapButton : public Fl_Button
	{
	public:
		MapButton(int x, int y, int w, int h, int _x, int _y);
		void ID(int id) { this->id = id;}
		int ID() { return id; }
		int X() { return x; }
		int Y() { return y; }
		// int handle(int e);
	private:
		int id;
		int x, y;
	};
	class CampaignEditor : BaseEditor
	{
		friend class MainMenu; 
		friend class MapEditor;

	public:
		CampaignEditor(int x, int y, int w, int h) : BaseEditor(x, y, w, h)
		{
			
			// spacing(30);
			label("Campaign Editor");
			browser->label("Loaded Maps");
			_g->hide();
			g->begin();
			// Fl_Box *box = new Fl_Box(20, 40, 50, 50, "Map");
			map_grid = new Fl_Scroll(0, 0, w * .6, h * .8);
			map_grid->type(Fl_Scroll::BOTH_ALWAYS);
			_grid_y = _grid_x = 5;
			campaign = new Campaign(_grid_x, _grid_y);
			redraw_map();
			map_grid->end();
			g->resizable(map_grid);
			g->end();
			maps = new std::vector<Map::Map *>();
			_c_x = _c_y = 1;
			sidebar->begin();

			sidebar_title = new Fl_Box(0,0,w*.2, 30);
			std::string label;
			label = "Map: " + std::to_string(_c_x) + ", " + std::to_string(_c_y);
			sidebar_title->copy_label(label.c_str());
			map_list = new Fl_Input_Choice(0, 0, w*.1, 30, "Map ID");
			
			map_list->callback(dropdown_cb, (void*)this);
			sidebar->end();
			// campaign
		}
		void redraw_map();
		void populate_browser();
		MapButton *get_cell(int x, int y) { return mbs[y][x]; }
		void create();
		bool open();
		void save();
		void save_as();
		void load_data();
		void update_data();
		void delete_entry();
		void save_data();
		void save_all();
		// void update_map_browser();
		void update_cell(int x, int y, int id);
		std::vector<Map::Map *> *get_maps() { return maps; }
		void show();
		void end(){BaseEditor::end();}
		void set_current_map(int x, int y){_c_x = x; _c_y = y;}
		void update_sidebar();
		Fl_Group * as_group() {return BaseEditor::as_group();}
		void update_dropdown();

		static void button_cb (Fl_Widget * w, void * f){
			int x = ((MapButton*)w)->X();
			int y = ((MapButton*)w)->Y();
			std::cout << "Button triggered" << std::endl;
			((CampaignEditor*) f)->handle_button(x,y);
		}

		static void dropdown_cb(Fl_Widget * w, void * f){
			// ((Fl_Input_Choice*)w)->value();
			((CampaignEditor*) f)->handle_dropdown();

		}
		void handle_dropdown();
		void handle_button (int x, int y){
			// set_current_map(x,y);
			_c_x = x; _c_y = y;
			update_sidebar();
		}
		// void set_browser() {}
	private:
		Fl_Scroll *map_grid;
		Fl_Box * sidebar_title;
		std::vector<Map::Map *> *maps;
		Map::Map *current_map;
		int _grid_x, _grid_y;
		std::vector<std::vector<MapButton *>> mbs;
		int _c_x, _c_y; // Current x and y values. set by buttons
		Campaign *campaign;
		Fl_Input_Choice * map_list;
	};
}
