#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <algorithm>

#include "MapEditor.h"
#include "MapSerializer.h"
#include "../ProjectSourceCode/Interactable/Interactable.h"
#include "../ProjectSourceCode/Interactable/Wall.h"
#include "../ProjectSourceCode/Interactable/EmptyCell.h"
#include "../ProjectSourceCode/Character/Character.h"
#include "../ProjectSourceCode/Item/item.h"
#include "../ProjectSourceCode/Builder/MapBuilder.h"
#include "../ProjectSourceCode/Door/door.h"

using namespace CampaignEditor;
using namespace door;

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
	//redraw_map();
	map_grid->end();
	g->resizable(map_grid);
	g->end();

	sidebar->begin();

	cellSideBarTitle = new Fl_Box(0, 0, w * .2, 30);
	std::string label;
	label = "Cell: " + std::to_string(0) + ", " + std::to_string(0);
	cellSideBarTitle->copy_label(label.c_str());
	objectIDChoiceList = new Fl_Input_Choice(0, 0, w * .1, 30, "Interactable ID");

	objectIDChoiceList->callback(InteractableIDDropdownCallBack, (void*)this);

	//map_list->callback(dropdown_cb, (void*)this);
	sidebar->end();
}

//std::string cttos(Map::Cell_Type ct)
std::string cttos(Interactable::Interactable* ct)
{
	if (typeid(*ct) == typeid(Wall)) {
		return "w";
	}
	else if (typeid(*ct) == typeid(Door)) {
		return "d";
	}
	else if(typeid(*ct) == typeid(Character::Character)) {
		return "c";
	}
	else if(typeid(*ct) == typeid(ItemContainer)) {
		return "co";
	}
	else if(typeid(*ct) == typeid(item::Item)) {
		return "i";
	}	
	else {
		return "";
	}
}

int MapCellButton::handle(int e)
{
	if ((x == 0 && y == 0) || (x == MapEditor::GetEndCellBbuttonX() && y == MapEditor::GetEndCellBbuttonY())) {
		return 0;
	}

	if (e == FL_RELEASE)
	{
		current_l = (current_l + 1) % 6;
		copy_label(Cell_Labels[current_l].c_str());
		this->value(current_l != 0);

		switch (current_l)
		{
			case 0:
				ct = new EmptyCell();

				break;
			case 1:
				ct = new Wall();

				break;
			case 2:
				ct = new Door();
				static_cast<Door*>(ct)->SetDoorID(0);

				break;
			case 3:
				ct = new Character::Character();
				static_cast<Character::Character*>(ct)->SetID(0);

				break;
			case 4:
				ct = new ItemContainer();
				static_cast<ItemContainer*>(ct)->SetItemID(0);

				break;
			case 5:
				ct = new Item();
				static_cast<Item*>(ct)->SetItemID(0);

				break;
			default:

				break;
		}

		MapEditor::update_cell(x, y, ct);

		//mapEditor->UpdateCellObjectIDDropDownLabel(x, y);
		MapEditor::UpdateCellObjectIDDropDownLabel(x, y);

		return 1;
	}
	if (e == FL_PUSH)
	{
		this->set();
		return 1;
	}
	return 0;
}

void MapEditor::Notify() {
	for (int i = 0; i < (int)observers.size(); i++)
	{
		observers[i]->update((void*)this);
	}
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
	mcbs.clear();
	for (int j = 0; j < _grid_y; j++)
	{
		// Fl_Pack * r = new Fl_Pack(0,0,50*_grid_x, 50);
		// r->type(Fl_Pack::HORIZONTAL);
		mcbs.push_back(std::vector<MapCellButton *>());
		for (int i = 0; i < _grid_x; i++)
		{
			MapCellButton *m = new MapCellButton(60 + 60 * i, 60 + 60 * j, 60, 60, i, j);

			m->copy_label(cttos(current_map->getGrid()[j][i]).c_str());
			
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

		endCellX = _new_x - 1;
		endCellY = _new_y - 1;

		std::cout << _new_x << "," << _new_y << std::endl;
		try
		{
			Map::Map *m = new Map::Map(_new_x, _new_y);
			maps->push_back(m);

			Notify();

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
	Map::Map* m = MapBuilder::MapBuilder::LoadMap(filepath);
	maps->push_back(m);

	Notify();

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
		Map::Map* m = MapBuilder::MapBuilder::LoadMap(filepath);
		maps->push_back(m);

		Notify();

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

	Notify();

	browser->value(0);
	populate_browser();
}

void MapEditor::UpdateCellObjectIDDropDownLabel(const int& _cellButtonX, const int& _cellButtonY)
{
	std::string label = "Cell: " + std::to_string(_cellButtonX) + ", " + std::to_string(_cellButtonY);
	cellSideBarTitle->copy_label(label.c_str());

	mapCellButtonX = _cellButtonX;

	mapCellButtonY = _cellButtonY;

	UpdateDropDown(_cellButtonX, _cellButtonY);
}


void MapEditor::UpdateDropDown(const int& _cellButtonX, const int& _cellButtonY) {
	objectIDChoiceList->clear();

	objectIDChoiceList->add("");

	if (get_cell(_cellButtonX, _cellButtonY)->ID() != 0) {
		objectIDChoiceList->value(std::to_string(get_cell(_cellButtonX, _cellButtonY)->ID()).c_str());
	}
	else {
		objectIDChoiceList->value("");
	}

	Interactable::Interactable* interactableAtCell = get_cell(_cellButtonX, _cellButtonY)->cell_type();
	if (dynamic_cast<Wall*>(interactableAtCell) || dynamic_cast<EmptyCell*>(interactableAtCell)) {
		return;
	}

	mapInteractables.clear();

	if (dynamic_cast<Door*>(interactableAtCell)) {
		std::vector<Door*> editorDoors = doorEditor->GetEditorDoors();
		for (int i = 0; i < (int)editorDoors.size(); i++)
		{
			mapInteractables.push_back(static_cast<Interactable::Interactable*>(editorDoors[i]));

			objectIDChoiceList->add(std::to_string(editorDoors[i]->GetDoorID()).c_str());
		}
	}
	else if (dynamic_cast<Character::Character*>(interactableAtCell)) {
		std::vector<Character::Character*> editorCharacters = characterEditor->GetEditorCharacters();
		for (int i = 0; i < (int)editorCharacters.size(); i++)
		{
			mapInteractables.push_back(static_cast<Interactable::Interactable*>(editorCharacters[i]));

			objectIDChoiceList->add(std::to_string(editorCharacters[i]->ID()).c_str());
		}
	}
	else if (dynamic_cast<ItemContainer*>(interactableAtCell)) {
		std::vector<ItemContainer*> editorContainers = containerEditor->GetEditorContainers();
		for (int i = 0; i < (int)editorContainers.size(); i++)
		{
			mapInteractables.push_back(static_cast<Interactable::Interactable*>(editorContainers[i]));

			objectIDChoiceList->add(std::to_string(editorContainers[i]->GetItemId()).c_str());
		}
	}
	else if (dynamic_cast<Item*>(interactableAtCell)) {
		std::vector<Item*> editorItems = itemEditor->GetEditorItems();
		for (int i = 0; i < (int)editorItems.size(); i++)
		{
			mapInteractables.push_back(static_cast<Interactable::Interactable*>(editorItems[i]));

			objectIDChoiceList->add(std::to_string(editorItems[i]->GetItemId()).c_str());
		}
	}
}

void MapEditor::HandleDropdownEvent() {
	MapCellButton* b = get_cell(mapCellButtonX, mapCellButtonY);
	b->ID(std::stoi(objectIDChoiceList->value()));
	
	bool found = false;
	
	for (int i = 0; i < (int)mapInteractables.size(); i++) {
		int interactableID = 0;
		char interactableCharacter = ' ';

		if (dynamic_cast<Door*>(mapInteractables[i])) {
			interactableID = static_cast<Door*>(mapInteractables[i])->GetDoorID();

			interactableCharacter = 'd';
		}
		else if (dynamic_cast<Character::Character*>(mapInteractables[i])) {
			interactableID = static_cast<Character::Character*>(mapInteractables[i])->ID();

			interactableCharacter = 'c';
		}
		else if (dynamic_cast<ItemContainer*>(mapInteractables[i])) {
			interactableID = static_cast<ItemContainer*>(mapInteractables[i])->GetItemId();

			interactableCharacter = 'co';
		}
		else if (dynamic_cast<Item*>(mapInteractables[i])) {
			interactableID = static_cast<Item*>(mapInteractables[i])->GetItemId();

			interactableCharacter = 'i';
		}

		if (interactableID == std::stoi(objectIDChoiceList->value())) {
			found = true;

			get_cell(mapCellButtonX, mapCellButtonY)->cell_type(mapInteractables[i]);

			current_map->setCell(mapCellButtonX, mapCellButtonY, mapInteractables[i]);
			
			break;
		}
	}
	if (!found) {
		// TODO:  Map not found error
		return;
	}
	
	std::cout << "Map cell modified" << std::endl;
}

//void MapEditor::update_cell(int x, int y, Map::Cell_Type ct) { current_map->ChangeCell(x, y, ct); }
//void MapEditor::update_cell(int x, int y, char ct) { current_map->ChangeCell(x, y, Map::ConvertToCellType(ct)); }
//void MapEditor::update_cell(int x, int y, std::string ct) { current_map->ChangeCell(x, y, Map::ConvertToCellType(ct[0])); }

void MapEditor::update_cell(int x, int y, Interactable::Interactable* ct) { current_map->setCell(x, y, ct); }
//void MapEditor::update_cell(int x, int y, char ct) { current_map->setCell(x, y, Map::ConvertToCellType(ct)); } // deprecated
//void MapEditor::update_cell(int x, int y, std::string ct) { current_map->ChangeCell(x, y, Map::ConvertToCellType(ct[0])); } //deprecated