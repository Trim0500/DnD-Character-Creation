#include <FL/Fl_Tabs.H>
#include "ItemEditor.h"
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 800
#include "MainMenu.h"

using namespace CampaignEditor;


MainMenu::MainMenu() : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Campaign Editor") {
	
	menu = new Fl_Menu_Bar(0,0, WINDOW_WIDTH, 30, "Campaign Editor");
	menu->add("@fileopen open", FL_CTRL+'o', MainMenu::static_open, (void*)this);
	menu->add("@filesave save", FL_CTRL+'s', MainMenu::static_save, (void*)this);
	menu->add("@filesave save as", FL_CTRL+FL_SHIFT+'s', MainMenu::static_save_as, (void*)this);
	// menu->end();
	tabs = new Fl_Tabs(10, 30, WINDOW_WIDTH, WINDOW_HEIGHT-30);
	ig = new Fl_Group(20, 90, WINDOW_WIDTH, WINDOW_HEIGHT - 60, "Items");
	{
		ie = new ItemEditor(20, 90, WINDOW_WIDTH-10, WINDOW_HEIGHT - 90);
	}
	ig->end();

	mg = new Fl_Group(20, 90, WINDOW_WIDTH, WINDOW_HEIGHT - 60, "Map");
	{
		me = new MapEditor(20, 90, WINDOW_WIDTH-10, WINDOW_HEIGHT - 90);
	}
	mg->end();

	tabs->end();
	this->end();
	this->resizable(tabs);
}

void MainMenu::start() {
}