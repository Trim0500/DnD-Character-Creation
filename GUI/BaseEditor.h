#pragma once

#include <iostream>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Native_File_Chooser.H>
namespace CampaignEditor {
	class BaseEditor :
		public Fl_Pack
	{
	public:
		BaseEditor(int x, int y, int w, int h) : Fl_Pack(x, y, w-10, h-10) {
			spacing(30);
			int c_y = 10;
			this->type(Fl_Pack::HORIZONTAL);
			this->spacing(100);
			Fl_Pack* _g = new Fl_Pack(10, 45, w * .2, (h) * .9);
			browser = new Fl_Hold_Browser(0, 20, w / 2, (h) * .5);
			Fl_Pack* _b = new Fl_Pack(0,0, w * .2, 30);
			_b->type(Fl_Pack::HORIZONTAL);
			delete_button = new Fl_Button(0, 0, w * .1, 30, "Delete");
			delete_button->callback(static_delete, (void*)this);
			create_new = new Fl_Button(0, 0, w* .1, 30, "New");
			create_new->callback(static_create_new, (void*)this);
			_b->end();
			_g->end();
			g = new Fl_Pack(0, 0, w * .8, (h));

			g->end();
			browser->callback(static_load_data,(void *)this);

			this->resizable(g);
		};
		static void static_load_data(Fl_Widget* w, void* f) {
			((BaseEditor*)f)->load_data();
		};
		static void static_save_data(Fl_Widget* w, void* f) {
			((BaseEditor*)f)->save_data();
		};
		static void static_create_new(Fl_Widget* w, void* f) {
			((BaseEditor*)f)->create();
		}
		static void static_delete(Fl_Widget* w, void* f) {
			((BaseEditor*)f)->delete_entry();
		}
	protected:
		Fl_Hold_Browser* browser;
		Fl_Pack* g;
		virtual void populate_browser() = 0;
		virtual void load_data() = 0;
		virtual void save_data() = 0;
		virtual void create() = 0;
		virtual void delete_entry() = 0;
		bool open();
		bool save();
		bool save_as();
		bool File_Chooser();
		bool File_Chooser(std::string title, Fl_Native_File_Chooser::Type t, int o = 0);
		Fl_Button* create_new;
		Fl_Button* delete_button;
		bool unsaved_data = true;
		std::string filepath;
		// virtual vector<
	};
}


