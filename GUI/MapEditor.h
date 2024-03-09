#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
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
	protected:
		;

	private:
		int editor_height, editor_width;
		Fl_Group * map_grid;
		Fl_Group * side_bars;
		std::vector<std::vector<MapCellButton *>> cell_buttons;
		/*
		methods to implement: opening all the maps
		drawing all the tiles
		opening all item containers


		*/
	};
}