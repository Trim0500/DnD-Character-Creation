#include <iostream>
#include <FL/Fl_Native_File_Chooser.H>

#include "BaseEditor.h"

namespace CampaignEditor
{
	bool BaseEditor::open()
	{
		return File_Chooser("Open...", Fl_Native_File_Chooser::BROWSE_FILE );
	}
	bool BaseEditor::save_as() {
		return File_Chooser("Save As...", Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
	}
	bool BaseEditor::File_Chooser(){
		return File_Chooser("Open", Fl_Native_File_Chooser::BROWSE_FILE);
	}
	bool BaseEditor::File_Chooser(std::string title, Fl_Native_File_Chooser::Type t){
		Fl_Native_File_Chooser fnfc;
		fnfc.title(title.c_str());
		fnfc.filter("*.csv");
		fnfc.type(t);
		fnfc.directory("./");
		switch (fnfc.show())
		{
		case -1:
			printf("ERROR: %s\n", fnfc.errmsg());
			// throw std::invalid_argument("");
			break; // ERROR
		case 1:
			printf("CANCEL\n");
			break; // CANCEL
		default:
			// printf("PICKED: %s\n", fnfc.filename());
			filepath = fnfc.filename();
			return true;
			break; // FILE CHOSEN
		}
		return false;
	}
}