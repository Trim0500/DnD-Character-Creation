#include <FL/Fl_Tabs.H>
#include "ItemEditor.h"
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 800
#define GROUP_SETTINGS 20, 90, WINDOW_WIDTH, (WINDOW_HEIGHT - 30)*.8
#define EDITOR_SETTINGS 30, 90, WINDOW_WIDTH*.8, (WINDOW_HEIGHT - 60)*.8
#include "MainMenu.h"

using namespace CampaignEditor;


MainMenu::MainMenu() : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Campaign Editor") {
	
	menu = new Fl_Menu_Bar(0,0, WINDOW_WIDTH, 30, "Campaign Editor");
	menu->add("@fileopen open", FL_CTRL+'o', MainMenu::static_open, (void*)this);
	menu->add("@filesave save", FL_CTRL+'s', MainMenu::static_save, (void*)this);
	menu->add("@filesave save as", FL_CTRL+FL_SHIFT+'s', MainMenu::static_save_as, (void*)this);
	// menu->end();
	tabs = new Fl_Tabs(10, 30, WINDOW_WIDTH, WINDOW_HEIGHT-30);
	// cg = new Fl_Group(GROUP_SETTINGS, "Campaign");
	// {
		ce = new CampaignEditor(EDITOR_SETTINGS);
		ce->end();
	// }
	// cg->end();
	mg = new Fl_Group(GROUP_SETTINGS, "Map");
	{
		me = new MapEditor(EDITOR_SETTINGS);
		me->set_maps(ce->get_maps());
	}
	mg->end();
	ig = new Fl_Group(GROUP_SETTINGS, "Items");
	{
		ie = new ItemEditor(EDITOR_SETTINGS);
	}
	ig->end();

	// chare = new CharacterEditor(EDITOR_SETTINGS);

	tabs->end();
	this->end();
	this->resizable(tabs);
	maps = new std::vector<Map::Map*>;
}

void MainMenu::start() {
}



