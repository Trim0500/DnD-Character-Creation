#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include "MapEditor.h"

using namespace CampaignEditor;

void MapEditor::redraw_map()
{
	std::cout << "Redrawing the map" << std::endl;
	// for (int j = 0; j < editor_height; j++) {

	// 	for (int i = 0; i < editor_width; i++) {

	// 	}
	// }
}

void MapEditor::load_map(Map::Map *m)
{
	std::cout << "Loading Map" << std::endl;
}

void MapEditor::load_data()
{
	// TODO: load map from file

}
void MapEditor::create()
{
	// TODO: create empty map
	char const* t_x = " ";
	char const* t_y = " ";
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
		try
		{
			Map::Map *m = new Map::Map(_new_x, _new_y);
			maps.push_back(m);
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

void MapEditor::populate_browser()
{
	browser->clear();
	std::string label;
	for (Map::Map *i : maps)
	{
		label = std::to_string(i->GetMapID());
		browser->add(label.c_str());
	}
}