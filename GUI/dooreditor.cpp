#include "dooreditor.h"

namespace {

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

	void DoorEditor::load_data() {

	}
	
	void DoorEditor::create() {

	}

	void DoorEditor::save() {

	}

	void DoorEditor::open(std::string _filePath) {

	}

	void DoorEditor::open() {

	}

	void DoorEditor::save_as() {

	}

	void DoorEditor::save_as(std::string _filePath) {

	}

	void DoorEditor::save_data() {

	}

	void DoorEditor::delete_entry() {

	}

	void DoorEditor::update_data() {

	}

	void DoorEditor::populate_browser() {

	}
}
