#pragma once

#include <FL/Fl_Pack.H>
#include <FL/Fl_Hold_Browser.H>

#include "../ProjectSourceCode/campaign.h"

using namespace campaign;

namespace CampaignEditor {
	class CampaignEditor : Fl_Pack {
	public:
		CampaignEditor(int x, int y, int w, int h) : Fl_Pack(x, y, w, h) {
			spacing(30);
			// campaign
		}
	protected:
		;
	private:

		Fl_Hold_Browser* map_browser;
		Campaign * campaign;
	};
}

