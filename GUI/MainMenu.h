#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <vector>
#include "ItemEditor.h"
#include "MapEditor.h"
#include "CampaignEditor.h"
#include "MapSerializer.h"
#include <filesystem>
#include "../ProjectSourceCode/Map.h"
namespace CampaignEditor
{
	class MainMenu : public Fl_Window
	{
	public:
		MainMenu();
		void start();
		static void static_save(Fl_Widget *w, void *f)
		{
			((MainMenu *)f)->save();
		};
		static void static_save_as(Fl_Widget *w, void *f)
		{
			((MainMenu *)f)->save_as();
		};
		static void static_open(Fl_Widget *w, void *f)
		{
			((MainMenu *)f)->open();
		};
		// static void static_save_as(Fl_Widget *w, void * f) {
		// 	((MainMenu*)f)->save_as();
		// };
		void save()
		{
			// tabs->value()->save();
			Fl_Group *current = tabs->value()->as_group();
			std::cout << "Triggering Save function" << std::endl;
			std::cout << current << std::endl;
			std::cout << ie << std::endl;
			if (current == ce->as_group())
			{
				std::cout << "Saving in Campaign Editor" << std::endl;
				// ie->save_as();
				ce->save();
				std::string temp = me->filepath;
				me->filepath = ce->filepath;
				std::string fp;
				for (Map::Map *_m: *me->maps){
					std::filesystem::create_directories(me->filepath + "/Maps");
					fp = me->filepath + "/Maps/Map" + std::to_string(_m->GetMapID()) + ".csv";
					MapSerializer::save_map(fp, _m);
				}
				me->filepath = temp;
				
				temp = ie->filepath;

				std::filesystem::create_directories(ce->filepath + "/Items");
				ie->filepath = ce->filepath+"/Items/items.csv";
				ie->save();
				ie->filepath = temp;
				return;
			}
			if (current == ig)
			{
				std::cout << "Saving in Item Editor" << std::endl;
				ie->save();
				return;
			}

			if (current == mg)
			{
				std::cout << "Saving in Map Editor" << std::endl;
				me->save();

				return;
			}
		};
		void open()
		{
			// tabs->value()->save();
			Fl_Group *current = tabs->value()->as_group();
			std::cout << "Triggering Open function" << std::endl;
			std::cout << current << std::endl;
			std::cout << ie << std::endl;
			if (current == ce->as_group())
			{
				std::cout << "Opening in Item Editor" << std::endl;
				// ie->save_as();
				ce->open();
				return;
			}
			if (current == ig)
			{
				std::cout << "Opening in Item Editor" << std::endl;
				ie->open();
				return;
			}

			if (current == mg)
			{
				std::cout << "Opening in Map Editor" << std::endl;
				me->open();
				return;
			}
		};
		void save_as()
		{
			// tabs->value()->save();
			Fl_Group *current = tabs->value()->as_group();
			std::cout << "Triggering Save function" << std::endl;
			std::cout << current << std::endl;
			// std::cout << ie << std::endl;
			if (current == ce->as_group())
			{
				std::cout << "Saving campaign" << std::endl;
				// ie->save_as();
				ce->save_as();
				return;
			}
			if (current == ig)
			{
				std::cout << "Saving in Item Editor" << std::endl;
				ie->save_as();
				return;
			}

			if (current == mg)
			{
				std::cout << "Saving as in Map Editor" << std::endl;
				me->save_as();
				return;
			}
		};

	private:
		Fl_Tabs *tabs;
		Fl_Menu_Bar *menu;
		ItemEditor *ie;
		MapEditor *me;
		CampaignEditor *ce;

		Fl_Group *ig;
		Fl_Group *mg;
		Fl_Group *cg;

		std::string campaign_dir;
		// std::vector<Map::Map *> maps;
	};

}
