#pragma once 
#include <string>

namespace Interactable {

	class Interactable {

	public:

		//can the player pass through a cell of this type
		virtual bool passable() { return true; };
		virtual std::string serialize() { return "e"; };

		//the derived classes should be: empty, wall, item, character

	};
}