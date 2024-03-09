#include <FL/Fl_Pack.H>
#include "MapEditor.h"

using namespace CampaignEditor;

void MapEditor::redraw_map() {
	std::cout << "Redrawing the map" << std::endl;
	// for (int j = 0; j < editor_height; j++) {
		
	// 	for (int i = 0; i < editor_width; i++) {

	// 	}
	// }
}

void MapEditor::load_map(Map::Map * m )  {
	std::cout << "Loading Map" << std::endl;
}

void MapEditor::load_data() {
	// TODO: load map from file
}
void MapEditor::create(){
	// TODO: create empty map
}

void MapEditor::save_data() {
	// TODO: get values to save map
}

void MapEditor::populate_browser() {
	std::string label;
	for (int i = 0; i < 10; i++) {
		label = std::to_string(i) + ": Test Map";
		browser->add(label.c_str());
	}
}