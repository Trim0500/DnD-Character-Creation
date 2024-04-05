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
#include <fstream>
#include <iostream>
#include "../ProjectSourceCode/Map.h"
#include "../ProjectSourceCode/MapBuilder.h"
#include "Tests/GuiTest.h"
namespace fs = std::filesystem;

namespace CampaignEditor
{

	bool hasEnding(std::string const& fullString, std::string const& ending);
	class MainMenu : public Fl_Window
	{
		friend class TestGUI;
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
		void create_campaign()
		{
		}
		void save()
		{
			std::cout << "Triggering Save function" << std::endl;
			ce->save();
			update_directories();
			std::cout << "Directories updated" << std::endl;
			fs::path fp;
			fs::create_directories(map_directory);
			for (Map::Map *_m : *me->maps)
			{
				fp = map_directory / ("Map" + std::to_string(_m->GetMapID()) + ".csv");
			}
			std::cout << "Maps saved" << std::endl;
			if (!fs::exists(item_directory))
			{
				fs::create_directories(campaign_dir / "Items");
			}
			ie->filepath = item_directory;

			ie->save();
			std::cout << "Items saved" << std::endl;
			return;
		};
		void open()
		{
			// tabs->value()->save();
			Fl_Group *current = tabs->value()->as_group();
			std::cout << "Triggering Open function" << std::endl;
			std::cout << current << std::endl;
			std::cout << ie << std::endl;
			std::cout << "Opening in Campaign Editor" << std::endl;
			// ie->save_as();
			if (ce->open())
			{
				update_directories();
				// std::string item_path = ce->filepath +
				if (fs::exists(item_directory))
				{
					ie->open(item_directory);
				}
				else
				{
					fs::create_directories(campaign_dir / "Items");
					ie->filepath = item_directory;
					ie->save();
				}
				if (fs::exists(map_directory))
				{
					std::string ext(".csv");
					for (auto &p : fs::directory_iterator(map_directory))
					{
						if (p.path().extension() == ext)
						{
							// me->open(p.path().string());
							// TODO: map loader
						}
					}
				}
				else
				{
					fs::create_directory(map_directory);
				}
				ce->maps = this->maps;
				me->set_maps(ce->maps);
			}
		};
		void save_as()
		{
			// Fl_Group *current = tabs->value()->as_group();
			std::cout << "Triggering Save function" << std::endl;
			// std::cout << current << std::endl;
			// std::cout << "Saving campaign" << std::endl;
			try
			{
				ce->save_as();
				campaign_dir = ce->filepath;

				save();
			}
			catch (std::exception *e)
			{
				std::cout << "Error while saving " << std::endl;
				std::cerr << e->what() << std::endl;
			}
			return;
		};

		vector<Map::Map*> * get_maps() {
			return maps;
		}
		void update_directories() {
			campaign_dir = fs::path(ce->filepath);
			item_directory = campaign_dir / "Items" / "items.csv";
			map_directory = campaign_dir / "Maps";
		}
	private:
		Fl_Tabs *tabs;
		Fl_Menu_Bar *menu;
		ItemEditor *ie;
		MapEditor *me;
		CampaignEditor *ce;

		Fl_Group *ig;
		Fl_Group *mg;
		Fl_Group *cg;

		fs::path campaign_dir;

		fs::path map_directory;
		fs::path item_directory;
		fs::path item_container_directory;
		fs::path character_directory;
		std::vector<Map::Map *> *maps;
	};

}
