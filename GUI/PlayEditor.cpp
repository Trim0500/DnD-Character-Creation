#include <FL/fl_ask.H>
#include "PlayEditor.h"

namespace CampaignEditor {
    PlayEditor::PlayEditor(int x, int y, int w, int h, const char* label)
        : Fl_Group(x, y, w, h, label) {
        end(); // Important: Call this to finish adding widgets to the group
        initUI();
    }

    PlayEditor::~PlayEditor() {}

    void PlayEditor::initUI() {
        // Initialize your gameplay UI here
        // For example, setting up buttons, game views, etc.
    }
}