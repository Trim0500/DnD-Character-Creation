#pragma once

#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "ItemEditor.h"
#include "MapEditor.h"
#include "CampaignEditor.h"
#include "ItemContainerEditor.h"
#include "PlayEditor.h"
#include "MapSerializer.h"
#include "CharacterEditor.h"
#include "dooreditor.h"
#include "../ProjectSourceCode/Map/Map.h"
#include "../ProjectSourceCode/Builder/MapBuilder.h"
#include "../ProjectSourceCode/Game/game.h"

namespace fs = std::filesystem;
using namespace dooreditor;

namespace CampaignEditor
{
	bool hasEnding(std::string const &fullString, std::string const &ending);
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
			std::cout << "Saving in Campaign Editor" << std::endl;
			// ie->save_as();
			ce->save();

			// for (Map::Map *_m: *me->maps)
			campaign_dir = fs::path(ce->filepath);
			update_directories();
			if (fs::exists(item_directory))
			{
				ie->open(item_directory.string());
			}
			else
			{
				fs::create_directories(item_directory.parent_path());
			}
			if (fs::exists(map_directory))
			{
				std::string ext(".csv");
				std::string path(map_directory.string());
				for (auto& p : fs::directory_iterator(path))
				{
					if (p.path().extension() == ext)
					{
						std::string s = p.path().string();
						Map::Map* m = MapBuilder::MapBuilder::LoadMap(s);
						maps->push_back(m);
					}
				}
			}
			else
			{
				fs::create_directory(map_directory);
			}
			if (fs::exists(character_directory)) {
				chare->open(character_directory.string());
			}
			else {
				fs::create_directories(character_directory);
			}
			//fs::create_directories(map_directory);
			std::vector<Map::Map*> mapsToSave = *me->maps;
			for (int index = 0; index < (int)mapsToSave.size(); index++)
			{
				Map::Map* mapToSave = mapsToSave[index];
				fs::path fp = map_directory / ("Map" + std::to_string(mapToSave->GetMapID()) + ".csv");
				std::string s = fp.string();
				MapBuilder::MapBuilder::SaveMap(mapToSave, s);
				// MapSerializer::save_map(fp, _m);
			}
			//fs::create_directories(item_directory.parent_path());
			//fs::create_directories(character_directory.parent_path());
			ie->save();
			chare->save();

			fs::create_directories(doorDirectory.parent_path());
			doorEditor->save();

			return;
		};
		void open()
		{
			// tabs->value()->save();
			std::cout << "Opening in Campaign Editor" << std::endl;
			maps->clear();

			// ie->save_as();
			if (ce->open())
			{
				campaign_dir = fs::path(ce->filepath);
				update_directories();
				if (fs::exists(item_directory))
				{
					ie->open(item_directory.string());
				}
				else
				{
					fs::create_directories(item_directory.parent_path());
				}

				if (fs::exists(map_directory))
				{
					std::string ext(".csv");
					std::string path(map_directory.string());
					for (auto &p : fs::directory_iterator(path))
					{
						if (p.path().extension() == ext)
						{
							std::string s = p.path().string();
							Map::Map *m = MapBuilder::MapBuilder::LoadMap(s);
							maps->push_back(m);
						}
					}
				}
				else
				{
					fs::create_directory(map_directory);
				}
				if (fs::exists(character_directory)) {
					chare->open(character_directory.string());
				}
				else {
					fs::create_directories(character_directory);
				}

				if (fs::exists(doorDirectory))
				{
					doorEditor->open(doorDirectory.string());
				}
				else
				{
					fs::create_directories(doorDirectory.parent_path());
				}

				ce->maps = this->maps;
				me->set_maps(ce->maps);
			}

			return;
		};
		void save_as()
		{
			// tabs->value()->save();
			// Fl_Native_File_Chooser::Type t;
			int o;
			Fl_Native_File_Chooser fnfc;
			fnfc.title("");
			// fnfc.filter("*.csv");
			fnfc.type(Fl_Native_File_Chooser::BROWSE_SAVE_DIRECTORY);
			fnfc.options(0);
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
				campaign_dir = fs::path(fnfc.filename());
				update_directories();
				save();
				break; // FILE CHOSEN
			}
		};

		void update_directories()
		{
			// campaign_dir = fs::path(ce->filepath);
			ce->filepath = campaign_dir.string();
			item_directory = campaign_dir / "Items" / "items.csv";
			map_directory = campaign_dir / "Maps";
			doorDirectory = campaign_dir / "Doors" / "doors.csv";
			character_directory = campaign_dir / "Characters";
			ie->filepath = item_directory.string();
			me->filepath = map_directory.string();
			chare->filepath = character_directory.string();
		}

		
	private:
		Fl_Tabs *tabs;

		Fl_Menu_Bar *menu;

		ItemEditor *ie;

		ItemContainerEditor* containerEditor;

		MapEditor *me;

		CharacterEditor *chare;

		CampaignEditor *ce;

		DoorEditor* doorEditor;

		PlayEditor* playEditor;

		Fl_Group *ig;

		Fl_Group *mg;

		Fl_Group *cg;
		Fl_Group *charg;

		Fl_Group* doorGroup;

		Fl_Group* playGroup;

		fs::path map_directory;

		fs::path item_directory;

		fs::path item_container_directory;

		fs::path doorDirectory;

		fs::path character_directory;

		fs::path campaign_dir;
		// std::vector<Map::Map *> maps;
		std::vector<Map::Map *> *maps;
		// std::vector<Character::Character *> *characters;
	};

}
