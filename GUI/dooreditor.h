#pragma once

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Float_Input.H>

#include "BaseEditor.h"
#include "../ProjectSourceCode/Door/door.h"
#include "../ProjectSourceCode/Observer/Observer.h"

using namespace CampaignEditor;
using namespace door;
using namespace observer;

namespace dooreditor {
	class DoorEditor : public BaseEditor, public Observer {
		friend class MainMenu;
	public:
		DoorEditor(int, int, int, int);

		virtual ~DoorEditor() {};

		void update(std::string) override {};

		void update(void*) override;

		void load_data();

		void create();

		void save();

		void open(std::string);

		void open();

		void save_as();

		void save_as(std::string);

		void save_data();

		void delete_entry();

		void update_data();

		void populate_browser();

		std::vector<Door*> GetEditorDoors() { return editorDoors; };

		void SetEditorItems(std::vector<Door*> _editorDoors) { editorDoors = _editorDoors; };

		void UpdateMapIDDropDowns(const std::vector<int>&);
	private:
		int get_item();

		std::vector<std::string> doorDatabase;
		// UI Components

		Fl_Int_Input* doorIDInput; // constant

		Fl_Input_Choice* firstMapIDChoice;

		Fl_Input_Choice* secondMapIDChoice;

		Fl_Input* firstMapLocationInput;

		Fl_Input* secondMapLocationInput;
		
		Fl_Input* firstMapSpawnPointInput;

		Fl_Input* secondMapSpawnPointInput;

		// Values loaded from file
		int loadedDoorId;

		int loadedFirstMapId;

		int loadedSecondMapId;

		std::vector<int> loadedFirstMapLocation;

		std::vector<int> loadedSecondMapLocation;

		std::vector<int> loadedFirstMapSpawnPoint;

		std::vector<int> loadedSecondMapSpawnPoint;

		Door* currentDoor;

		// Values currently in GUI
		std::string currentDoorId;

		std::string currentFirstMapID;

		std::string currentSecondMapID;

		std::string currentFirstMapLocation;

		std::string currentSecondMapLocation;

		std::string currentFirstMapSpawnPoint;

		std::string currentSecondMapSpawnPoint;

		std::vector<Door*> editorDoors;
	};
}
