#pragma once 

namespace Interactable {

	class Interactable {

	public:

		//can the player pass through a cell of this type
<<<<<<< HEAD
		virtual bool passable();
=======
		virtual bool passable() const { return true; };
>>>>>>> e48c3efde6b37d850058987a2bdc28da07358e64

		//the derived classes should be: empty, wall, item, character

	};
}