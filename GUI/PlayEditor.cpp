#include <FL/fl_ask.H>
#include "PlayEditor.h"

namespace CampaignEditor {
    PlayEditor::PlayEditor(int x, int y, int w, int h) : BaseEditor(x,y,w,h){

		const int margin = 100;
		const int width = 100;
		const int height = 40;
		const int padding = 50;

		g->begin();

		campaignChoiceInput = new Fl_Input(margin, y, w, height, "Campaigns");
		campaignChoiceInput->readonly(true);


		Fl_Pack* b = new Fl_Pack(margin, y+height, w/4, height / 2);
		b->type(Fl_Pack::HORIZONTAL);

		// Create a "Browse" button
		Fl_Button* browseBtn = new Fl_Button(0, 0, w/4, h, "Browse");
		browseBtn->callback(browse_cb, (void*)this); // Set the callback

		Fl_Button* start = new Fl_Button(margin, height, w /4, h, "Start");
		start->callback(startGame_cb, (void*)this);
		b->end();

		g->end();
		Notify();

    }

	void PlayEditor::browse_cb(Fl_Widget* w, void* data)
	{
		PlayEditor* editor = static_cast<PlayEditor*>(data);
		Fl_Native_File_Chooser chooser;
		chooser.title("Choose a File");
		chooser.type(Fl_Native_File_Chooser::BROWSE_FILE); // Set to browse files
		if (chooser.show() == 0) { // User made a selection
			std::filesystem::path selectedFile = chooser.filename();
			// Now you can use selectedFile as needed
			// For example, storing it in the PlayEditor class
			currentCampaignPath = new std::filesystem::path(selectedFile);
			campaignChoiceInput->value(currentCampaignPath->string().c_str());
		}
	}

	void PlayEditor::startGame_cb(Fl_Widget* w, void* data)
	{
		std::string gameDirToLoad = campaignChoiceInput->value();

		currentGame = new Game();
		gameLogger = new GameLogger(currentGame);
		currentGame->GameSetup(currentCampaignPath, gameLogger);
		currentGame->GetGameCampaign()->SetCurrentMap(currentGame->GetGameCampaign()->GetCurrentMap());
		CampaignMap currentMap = currentGame->GetGameCampaign()->GetCurrentMap();

		PlayGame(currentGame, currentGame->GetActiveCharacter(), currentGame->GetGameCampaign()->GetMap(currentMap.coorX, currentMap.coorY));
	}


	void PlayEditor::load_data()
	{
		std::cout << "updating campaigns" << std::endl;
		update_data();
	}

	void PlayEditor::create()
	{
		load_data();
	}

	void PlayEditor::save()
	{
		if (filepath.empty())
		{
			save_as();
		}
		else
		{
			try
			{
				Notify();
			}
			catch (const std::exception& e)
			{
				fl_alert("There was an error saving the file. Try using 'save as'");
			}
			try
			{

				Notify();
				populate_browser();
				/* code */
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}

	void PlayEditor::open(std::string)
	{
	}

	void PlayEditor::open()
	{
	}

	void PlayEditor::save_as()
	{
		if (BaseEditor::save_as())
		{
			try
			{
				save();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		};
		Notify();
	}

	void PlayEditor::save_data()
	{


		populate_browser();
	}

	void PlayEditor::delete_entry()
	{
	}

	void PlayEditor::update_data()
	{
		_loadCampaignPathName = currentCampaignPath->string();
		campaignChoiceInput->value(_loadCampaignPathName.c_str());
	}

	void PlayEditor::populate_browser()
	{
		Notify();

	}

	void PlayEditor::Notify()
	{
		for (int i = 0; i < (int)observers.size(); i++)
		{
			observers[i]->update((void*)this);
		}
	}

	void PlayGame(Game* currentGame, Character::Character* playerCharacter, Map::Map* currentMap) {
		char userInput = ' ';
		while (userInput != 'E')
		{
			system("cls");

			CampaignMap currentCampaignMap = currentGame->GetGameCampaign()->GetCurrentMap();
			Map::Map* map = currentGame->GetGameCampaign()->GetMap(currentCampaignMap.coorX, currentCampaignMap.coorY);
			map->printMap();

			currentGame->PrintActionMenu(playerCharacter);

			currentGame->GetUserSelection(userInput);

			currentGame->ProcessUserAction(userInput, playerCharacter);

			if (currentGame->GetActiveCharacter() != playerCharacter)
			{
				int x, y;
				currentMap->GetCharacterCoordinates(x, y, currentGame->GetActiveCharacter());

				CellActionInfo npcCellAction = currentGame->GetActiveCharacter()->DecideNPCAction(currentMap->getGrid(), x + 1, y + 1);
				currentGame->EndTurn(npcCellAction.actionName, npcCellAction.row, npcCellAction.col);
			}

			getchar();
		}

		exit(0);
	}
}