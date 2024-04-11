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

#include "../ProjectSourceCode/Item/item.h"
#include "../ProjectSourceCode/Character/Character.h"
#include "../ProjectSourceCode/Serialize/serializeItem.h"

#include "BaseEditor.h"

namespace CampaignEditor {
    class PlayEditor : public Fl_Group {
    public:
        PlayEditor(int x, int y, int w, int h, const char* label = 0);
        virtual ~PlayEditor();

        void initUI();
    };
}