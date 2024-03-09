#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Group.H>
#include "ItemEditor.h"
#include "MapEditor.h"
namespace CampaignEditor {
    class MainMenu :
        public Fl_Window
    {
    public:
        MainMenu();
        void start();
		static void static_save(Fl_Widget *w, void * f) {
			((MainMenu*)f)->save();
		};
		static void static_save_as(Fl_Widget *w, void * f) {
			((MainMenu*)f)->save_as();
		};
		static void static_open(Fl_Widget *w, void * f) {
			((MainMenu*)f)->open();
		};
		// static void static_save_as(Fl_Widget *w, void * f) {
		// 	((MainMenu*)f)->save_as();
		// };
		void save(){
			// tabs->value()->save();
			Fl_Group * current = tabs->value()->as_group();
			std::cout << "Triggering Save function" << std::endl;
			std::cout << current << std::endl;
			std::cout << ie << std::endl;
			if (current == ig) {
				std::cout << "Saving in Item Editor" << std::endl;
				ie->save();
				return;
			}

			if (current == mg) {
				std::cout << "Saving in Map Editor" << std::endl;
				return;
			}
		};
		void open(){
			// tabs->value()->save();
			Fl_Group * current = tabs->value()->as_group();
			std::cout << "Triggering Open function" << std::endl;
			std::cout << current << std::endl;
			std::cout << ie << std::endl;
			if (current == ig) {
				std::cout << "Opening in Item Editor" << std::endl;
				ie->open();
				return;
			}

			if (current == mg) {
				std::cout << "Opening in Map Editor" << std::endl;
				return;
			}
		};
		void save_as(){
				// tabs->value()->save();
			Fl_Group * current = tabs->value()->as_group();
			std::cout << "Triggering Save function" << std::endl;
			std::cout << current << std::endl;
			std::cout << ie << std::endl;
			if (current == ig) {
				std::cout << "Saving in Item Editor" << std::endl;
				return;
			}

			if (current == mg) {
				std::cout << "Saving in Map Editor" << std::endl;
			}
		};
    private:
		Fl_Tabs* tabs;
		Fl_Menu_Bar * menu;
        ItemEditor* ie;
        MapEditor* me;

		Fl_Group * ig;
		Fl_Group * mg;
    };


}
