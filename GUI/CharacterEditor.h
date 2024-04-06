#include "BaseEditor.h"

namespace CampaignEditor
{
	class CharacterEditor : public BaseEditor
	{
		public:
		CharacterEditor(int x, int y, int w, int h);
		void load_data();
		void create();
		void save();
		void open(std::string);
		void open();
		void save_as();
		void save_as(std::string s);
		void save_data();
		void delete_entry();
		void update_data();
		void populate_browser();
		private:
			vector<Character::Character *> * characters;
	};
}