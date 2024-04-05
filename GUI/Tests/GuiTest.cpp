#include <iostream>
#include <string>
#include <sstream>

#include "GuiTest.h"
#include "../../ProjectSourceCode/item.h"
void TestGUI::setUp(void) {
	main_menu = new CampaignEditor::MainMenu();
}
void TestGUI::TestCampaignSave(void)
{
	Map::Map *m = new Map::Map();
	item::Item *item = new item::Item();
	main_menu->get_maps()->push_back(m);
	//main_menu->;
	//main_menu->save();
}
void TestGUI::TestCampaignOpen(void)
{
	//main_menu->open();
}
void TestGUI::TestCampaignSaveAs(void)
{
	Map::Map* m = new Map::Map();
	item::Item* item = new item::Item();
	main_menu->get_maps()->push_back(m);
	//main_menu->;
	//main_menu->save_as();
	//main_menu->save();
}