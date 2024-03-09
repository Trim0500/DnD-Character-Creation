#include <FL/Fl_Native_File_Chooser.H>

#include "BaseEditor.h"

namespace CampaignEditor
{
	std::string BaseEditor::open()
	{
		Fl_Native_File_Chooser fnfc;
		fnfc.title("Open...");
		fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
		switch (fnfc.show())
		{
		case -1:
			printf("ERROR: %s\n", fnfc.errmsg());
			break; // ERROR
		case 1:
			printf("CANCEL\n");
			break; // CANCEL
		default:
			// printf("PICKED: %s\n", fnfc.filename());
			return fnfc.filename();
			break; // FILE CHOSEN
		}
	}
}