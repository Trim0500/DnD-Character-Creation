#include <FL/Fl_Tabs.H>
#include "ItemEditor.h"
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 800
#include "MainMenu.h"

using namespace CampaignEditor;


MainMenu::MainMenu() : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT) {
	
	menu = new Fl_Menu_Bar(0,0, WINDOW_WIDTH, 30, "Campaign Editor");
	Fl_Menu_Item bar[] = {
		{"&open", FL_CTRL+'o', MainMenu::static_open, (void*)this},
		{"&save", FL_CTRL+'s', MainMenu::static_save, (void*)this},
		{"save as...", FL_SHIFT+'s', MainMenu::static_save_as, (void*)this}
	};
	menu->copy(bar);
	// const int window_width = WINDOW_WIDTH;
	// const int window_height = WINDOW_HEIGHT;

	tabs = new Fl_Tabs(10, 30, WINDOW_WIDTH, WINDOW_HEIGHT);
	ig = new Fl_Group(20, 30, WINDOW_WIDTH, WINDOW_HEIGHT - 150, "Items");
	{
		ie = new ItemEditor(50, 50, WINDOW_WIDTH - 150, WINDOW_HEIGHT - 150);
	}
	ig->end();

	mg = new Fl_Group(20, 30, WINDOW_WIDTH - 40, WINDOW_HEIGHT - 150, "Map");
	{
		me = new MapEditor(50, 50, WINDOW_WIDTH - 150, WINDOW_HEIGHT - 150);
	}
	mg->end();

	tabs->end();
	this->end();
	this->resizable(tabs);
}

void MainMenu::start() {
	ie->populate_browser();
	this->show();

}