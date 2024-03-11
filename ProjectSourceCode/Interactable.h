namespace Interactable {

	class Interactable {

		//can the player pass through a cell of this type
		virtual bool passable() = 0;

		//the derived classes should be: empty, wall, item, character

	};
}