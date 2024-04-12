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
#include <filesystem>
#include <locale>
#include <codecvt>

#include "../ProjectSourceCode/Item/item.h"
#include "../ProjectSourceCode/Character/Character.h"
#include "../ProjectSourceCode/Serialize/serializeItem.h"
#include "../ProjectSourceCode/Campaign/campaign.h"
#include "../ProjectSourceCode/Observer/Observable.h"
#include "../ProjectSourceCode/Game/game.h"
#include "../ProjectSourceCode/Game/gamelogger.h"
#include "BaseEditor.h"

using namespace game;
using namespace gamelogger;

namespace CampaignEditor {
    class PlayEditor : public BaseEditor, public Observable {
        friend class MainMenu;
    public:
        PlayEditor(int x, int y, int w, int h);

		static void browse_cb(Fl_Widget* w, void* data);

		static void startGame_cb(Fl_Widget* w, void* data);

		void load_data();
		void create();
		void save();
		void open(std::string);
		void open();
		void save_as();
		//void save_as(std::string s);
		void save_data();
		void delete_entry();
		void update_data();
		void populate_browser();

		void Notify() override;

		void Attach(Observer* _observer) override { observers.push_back(_observer); };

		void Detach(Observer* _observer) override { observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end()); };

		game::Game* GetCurrentGame() { return currentGame; };

		GameLogger* GetGameLogger() { return gameLogger; };

		void SetGameLogger(GameLogger* _gameLogger) { gameLogger = _gameLogger; };
    private:
		

		std::string _loadCampaignPathName;

		// Values currently in GUI
		std::string currentCharacterID;

		static inline std::filesystem::path* currentCampaignPath = nullptr;

		static inline Fl_Input* campaignChoiceInput;
		//Variable to load the campaign into when the game starts
		static inline game::Game* currentGame;

		static inline GameLogger* gameLogger;
        //campaign::Campaign* currentCampaignChoice;

		std::vector<Observer*> observers;

    };

	void PlayGame(Game* , Character::Character*, Map::Map*);
}