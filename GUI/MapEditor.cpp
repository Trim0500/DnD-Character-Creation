#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include "MapEditor.h"
#include "MapSerializer.h"
#include "../ProjectSourceCode/Interactable/Interactable.h"
#include "../ProjectSourceCode/Interactable/Wall.h"
#include "../ProjectSourceCode/Interactable/EmptyCell.h"
#include "../ProjectSourceCode/Character/Character.h"
#include "../ProjectSourceCode/Item/item.h"
#include "../ProjectSourceCode/Builder/MapBuilder.h"

using namespace CampaignEditor;

MapEditor::MapEditor(int x, int y, int w, int h) : BaseEditor(x, y, w, h)
{
	// g->resize(0, 0, w * .6, (h));
	// side_bars = new Fl_Group(0, 0, 200, 200);
	// Fl_Box *box = new Fl_Box(20, 40, 50, 50, "Cell Editor");
	// side_bars->end();
	// g->add(map_grid);
	g->begin();
	// Fl_Box *box = new Fl_Box(20, 40, 50, 50, "Map");
	map_grid = new Fl_Scroll(0, 0, w, h - 40, "Map");
	map_grid->type(Fl_Scroll::BOTH_ALWAYS);
	map_grid->end();
	g->resizable(map_grid);
	g->end();
}

//std::string cttos(Map::Cell_Type ct)
std::string cttos(Interactable::Interactable* ct)
{
	//switch (typeid(ct))
	//{
	////case Map::Cell_Type::special:
	//case Map::Cell_Type::special:
	//	return "s";
	//	break;
	////case Map::Cell_Type::wall:
	//case typeid(Wall) == typeid(ct):
	//	return "w";
	//default:
	//	return " ";

	//	break;
	//}

	if (typeid(*ct) == typeid(Wall)) {
		return "w";
	}
	else if(typeid(*ct) == typeid(item::Item)) {
		return "i";
	}	
	else if(typeid(*ct) == typeid(Character::Character)) {
		return "c";
	}
	else {
		return " ";
	}

}

int MapCellButton::handle(int e)
{
	if (e == FL_RELEASE)
	{
		current_l = (current_l + 1) % 3;
		copy_label(Cell_Labels[current_l].c_str());
		this->value(current_l != 0);
		return 1;
	}
	if (e == FL_PUSH)
	{
		this->set();
		return 1;
	}
	return 0;
}

void MapEditor::redraw_map()
{
	std::cout << "Redrawing the map" << std::endl;
	std::string label;
	map_grid->clear();
	map_grid->hide();
	// map_grid->resize(0, 0,10+30*_grid_x, 10+30*_grid_y);
	map_grid->begin();
	// map_grid->clear();
	// Fl_Pack * c = new Fl_Pack(0,0,300, 50*_grid_y);
	// MapCellButton * mc;
	for (int j = 0; j < _grid_y; j++)
	{
		// Fl_Pack * r = new Fl_Pack(0,0,50*_grid_x, 50);
		// r->type(Fl_Pack::HORIZONTAL);
		mcbs.push_back(std::vector<MapCellButton *>());
		for (int i = 0; i < _grid_x; i++)
		{
			MapCellButton *m = new MapCellButton(30 + 30 * i, 30 + 30 * j, 30, 30, i, j);
			//m->copy_label(cttos(current_map->getGrid()[j][i]).c_str());//TODO. error here.
			mcbs[j].push_back(m);
		}
		// r->end();
	}
	// c->end();
	map_grid->end();
	// map_grid->scroll_to(0,0);
	map_grid->show();
}

void MapEditor::load_data()
{
	std::cout << "updating map" << std::endl;
	// int i = this->get_item();
	int i = browser->value();
	if (i <= maps->size() && i > 0)
	{
		std::cout << "selected: " << i << std::endl;
		current_map = (Map::Map *)browser->data(i);

		update_data();
	}
	// TODO: load map from file
}

void MapEditor::update_data()
{
	_grid_x = current_map->getCols();
	_grid_y = current_map->getRows();
	redraw_map();
}
void MapEditor::create()
{
	// TODO: create empty map
	char const *t_x = " ";
	char const *t_y = " ";
	NewMapModal *w = new NewMapModal();
	// in_x->static_value(t_x);
	// in_y->static_value(t_y);

	w->show();

	while (w->shown())
	{
		Fl::wait();
	}
	if (w->confirmed())
	{
		_new_x = w->x();
		_new_y = w->y();
		std::cout << _new_x << "," << _new_y << std::endl;
		try
		{
			Map::Map *m = new Map::Map(_new_x, _new_y);
			maps->push_back(m);
			populate_browser();
			browser->bottomline(browser->size());
			browser->select(browser->size());
			load_data();
		}
		catch (std::exception &e)
		{
		}
	}
	else
	{
		// TODO: signal the error
	}
}

void MapEditor::hide(Fl_Widget *widget, void *f)
{
	Fl_Window *window = (Fl_Window *)widget;
	window->hide();
}

void MapEditor::confirm(Fl_Widget *widget, void *f)
{
	Fl_Window *window = (Fl_Window *)widget;
	std::cout << window->children() << std::endl;

	// TODO: all the errors
}

void MapEditor::save_data()
{
	// TODO: get values to save map
}

void MapEditor::save_as()
{
	if (BaseEditor::save_as())
	{
		try
		{
			//MapSerializer::save_map(filepath, current_map);
			MapBuilder::MapBuilder::SaveMap(current_map, filepath);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	};
}

void MapEditor::populate_browser()
{
	browser->clear();
	std::string label;
	for (Map::Map *i : *maps)
	{
		label = std::to_string(i->GetMapID());
		browser->add(label.c_str(), i);
	}
}

void MapEditor::open(std::string s)
{
	//Map::Map m = MapSerializer::load_map(filepath);
	Map::Map m = MapBuilder::MapBuilder::LoadMap(filepath);
	maps->push_back(&m);
	populate_browser();
	browser->bottomline(browser->size());
	browser->select(browser->size());
	load_data();
}

void MapEditor::open()
{
	if (BaseEditor::open())
	{
		//Map::Map m = MapSerializer::load_map(filepath);
		Map::Map m = MapBuilder::MapBuilder::LoadMap(filepath);
		maps->push_back(&m);
		populate_browser();
		browser->bottomline(browser->size());
		browser->select(browser->size());
		load_data();
	}
}

void MapEditor::delete_entry()
{
	if (maps->size() < 0)
	{
		return;
	}
	int i = browser->value();
	if (i < 1 || i > maps->size())
	{
		return;
	};
	maps->erase(maps->begin() + (i - 1));
	browser->value(0);
	populate_browser();
}

//void MapEditor::update_cell(int x, int y, Map::Cell_Type ct) { current_map->ChangeCell(x, y, ct); }
//void MapEditor::update_cell(int x, int y, char ct) { current_map->ChangeCell(x, y, Map::ConvertToCellType(ct)); }
//void MapEditor::update_cell(int x, int y, std::string ct) { current_map->ChangeCell(x, y, Map::ConvertToCellType(ct[0])); }

void MapEditor::update_cell(int x, int y, Interactable::Interactable* ct) { current_map->setCell(x, y, ct); }
//void MapEditor::update_cell(int x, int y, char ct) { current_map->setCell(x, y, Map::ConvertToCellType(ct)); } // deprecated
//void MapEditor::update_cell(int x, int y, std::string ct) { current_map->ChangeCell(x, y, Map::ConvertToCellType(ct[0])); } //deprecated