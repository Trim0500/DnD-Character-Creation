#pragma once
#include <iostream>
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

namespace CampaignEditor
{
	CharacterEditor::CharacterEditor(int x, int y, int w, int h) {
		g->begin();
		idInput = new Fl_Int_Input(0, 0, w, height, "Id");
		idInput->readonly(true);
	}


}