#include <sstream>
#include <string>
#include <FL/fl_ask.H>
#include <regex>

#include "dooreditor.h"
#include "MapEditor.h"

namespace {
	std::string BuildVectorInputString(const std::vector<int>& _locationVector) {
		std::ostringstream inputString;
		inputString << _locationVector[0] << "," << _locationVector[1];

		return inputString.str();
	}

	std::vector<int> BuildVectorFromInput(std::string _locationInput) {
		std::vector<int> result;

		std::smatch match;

		std::regex numberRgx("[0-9]+");

		while (regex_search(_locationInput, match, numberRgx)) {
			result.push_back(std::stoi(match.str()));

			_locationInput = match.suffix().str();
		}

		return result;
	}

	void UpdateMapIDDropdownSelection(Fl_Input_Choice* _inputChoice, const std::vector<int>& _idVector) {
		_inputChoice->clear();

		Fl_Input* _temp = _inputChoice->input();
		_temp->readonly(true);

		for (int i = 0; i < (int)_idVector.size(); i++)
		{
			_inputChoice->add(std::to_string(_idVector[i]).c_str());
		}
	}
}

namespace dooreditor {
	DoorEditor::DoorEditor(int x, int y, int w, int h) : BaseEditor(x, y, w, h) {
		const int margin = 100;
		const int width = 100;
		const int height = 50;
		const int padding = 50;

		g->begin();
		/*
			base item information
		*/
		doorIDInput = new Fl_Int_Input(0, 0, w, height, "ID");
		doorIDInput->readonly(true);

		firstMapIDChoice = new Fl_Input_Choice(0, 0, w, height, "1st Map ID");
		Fl_Input* _temp = firstMapIDChoice->input();
		_temp->readonly(true); // If I can't choose when poopulating, check this out
		
		secondMapIDChoice = new Fl_Input_Choice(0, 0, w, height, "2nd Map ID");
		_temp = secondMapIDChoice->input();
		_temp->readonly(true); // If I can't choose when poopulating, check this out

		firstMapLocationInput = new Fl_Input(0, 0, w, height, "1st Map x,y");
		firstMapLocationInput->readonly(true);
		
		secondMapLocationInput = new Fl_Input(0, 0, w, height, "2nd Map x,y");
		secondMapLocationInput->readonly(true);
		
		firstMapSpawnPointInput = new Fl_Input(0, 0, w, height, "1st Map Spawn x,y");

		secondMapSpawnPointInput = new Fl_Input(0, 0, w, height, "2nd Map Spawn x,y");

		Fl_Pack* fieldButtons = new Fl_Pack(0, 0, w, height / 2);
		fieldButtons->type(Fl_Pack::HORIZONTAL);

		Fl_Button* cancel = new Fl_Button(margin, 0, w / 4, height, "Cancel");
		Fl_Button* apply = new Fl_Button(margin, 0, w / 4, height, "Apply");

		fieldButtons->end();

		cancel->callback(static_load_data, (void*)this);
		apply->callback(static_save_data, (void*)this);

		g->end();
	}

	void DoorEditor::update(void* _observable) {
		std::vector<Map::Map*>* mapsInEditor = ((MapEditor*)_observable)->GetEditorMaps();

		std::vector<int> mapIDs;

		for (int i = 0; i < (int)mapsInEditor->size(); i++)
		{
			mapIDs.push_back(mapsInEditor->at(i)->GetMapID());
		}

		UpdateMapIDDropDowns(mapIDs);
	}

	void DoorEditor::load_data() {
		std::cout << "[DoorEditor/load_data] -- Updating Doors" << std::endl;

		int i = browser->value();
		if (i <= editorDoors.size() && i > 0)
		{
			std::cout << "[DoorEditor/load_data] -- Selected: " << i << std::endl;
			currentDoor = (Door*)browser->data(i);

			update_data();
		}
	}
	
	void DoorEditor::create() {
		Door* newDoor = new Door();
		editorDoors.push_back(newDoor);

		populate_browser();

		browser->bottomline(browser->size());
		browser->select(browser->size());

		load_data();
	}

	void DoorEditor::save() {
		if (filepath.empty())
		{
			save_as();
		}
		else
		{
			try
			{
				SaveDoors(filepath, editorDoors);
			}
			catch (const std::exception& e)
			{
				fl_alert("[DoorEditor/save] -- There was an error saving the file. Try using 'save as'");
			}

			try
			{
				editorDoors = LoadDoors(filepath);

				populate_browser();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}

	void DoorEditor::open(std::string _filePath) {
		filepath = _filePath;

		try
		{
			editorDoors = LoadDoors(filepath);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

		try
		{
			populate_browser();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

	void DoorEditor::open() {
		if (BaseEditor::open())
		{
			try
			{
				editorDoors = LoadDoors(filepath);
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}

			try
			{
				populate_browser();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}

	void DoorEditor::save_as() {
		if (BaseEditor::save_as())
		{
			try
			{
				save();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}

	void DoorEditor::save_as(std::string _filePath) {
		try
		{
			SaveDoors(_filePath, editorDoors);
		}
		catch (const std::exception& e)
		{
			fl_alert("[DoorEditor/save] -- There was an error saving the file. Try using 'save as'");
		}
	}

	void DoorEditor::save_data() {
		currentDoor->SetDoorID(std::stoi(doorIDInput->value()));
		currentDoor->SetFirstMapID(std::stoi(firstMapIDChoice->value()));
		currentDoor->SetSecondMapID(std::stoi(secondMapIDChoice->value()));
		currentDoor->SetFirstMapLocation(BuildVectorFromInput(firstMapLocationInput->value()));
		currentDoor->SetSecondMapLocation(BuildVectorFromInput(secondMapLocationInput->value()));
		currentDoor->SetFirstMapSpawnPoint(BuildVectorFromInput(firstMapSpawnPointInput->value()));
		currentDoor->SetSecondMapSpawnPoint(BuildVectorFromInput(secondMapSpawnPointInput->value()));

		populate_browser();
	}

	void DoorEditor::delete_entry() {
		if (editorDoors.size() < 0)
		{
			return;
		}

		int i = browser->value();
		if (i < 1 || i > editorDoors.size())
		{
			return;
		}

		editorDoors.erase(editorDoors.begin() + (i - 1));

		browser->value(0);

		populate_browser();
	}

	void DoorEditor::update_data() {
		loadedDoorId = currentDoor->GetDoorID();
		loadedFirstMapId = currentDoor->GetFirstMapID();
		loadedSecondMapId = currentDoor->GetSecondMapID();
		loadedFirstMapLocation = currentDoor->GetFirstMapLocation();
		loadedSecondMapLocation = currentDoor->GetSecondMapLocation();
		loadedFirstMapSpawnPoint = currentDoor->GetFirstMapSpawnPoint();
		loadedSecondMapSpawnPoint = currentDoor->GetSecondMapSpawnPoint();

		currentDoorId = std::to_string(loadedDoorId);
		currentFirstMapID = std::to_string(loadedFirstMapId);
		currentSecondMapID = std::to_string(loadedSecondMapId);
		currentFirstMapLocation = BuildVectorInputString(loadedFirstMapLocation);
		currentSecondMapLocation = BuildVectorInputString(loadedSecondMapLocation);
		currentFirstMapSpawnPoint = BuildVectorInputString(loadedFirstMapSpawnPoint);
		currentSecondMapSpawnPoint = BuildVectorInputString(loadedSecondMapSpawnPoint);

		doorIDInput->value(currentDoorId.c_str());
		firstMapIDChoice->value(currentFirstMapID.c_str());
		secondMapIDChoice->value(currentSecondMapID.c_str());
		firstMapLocationInput->value(currentFirstMapLocation.c_str());
		secondMapLocationInput->value(currentSecondMapLocation.c_str());
		firstMapSpawnPointInput->value(currentFirstMapSpawnPoint.c_str());
		secondMapSpawnPointInput->value(currentSecondMapSpawnPoint.c_str());
	}

	void DoorEditor::populate_browser() {
		browser->clear();

		std::string label;
		for (Door* door : editorDoors)
		{
			label = std::to_string(door->GetDoorID());
			browser->add(label.c_str(), door);
		}
	}

	void DoorEditor::UpdateMapIDDropDowns(const std::vector<int>& _mapIDs) {
		UpdateMapIDDropdownSelection(firstMapIDChoice, _mapIDs);

		UpdateMapIDDropdownSelection(secondMapIDChoice, _mapIDs);
	}
}
