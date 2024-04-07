#include "../ProjectSourceCode/Observer/Observer.h"
#include <FL/Fl_Window.H>

using namespace observer;

namespace CampaignEditor {
	class BaseViewer : public Fl_Window, public Observer {
		
	};
}