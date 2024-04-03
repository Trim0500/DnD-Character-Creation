#pragma once

#include "Interactable.h"

class Wall : public Interactable::Interactable
{
public:

	bool passable() const { return false; }
	std::string serialize() { return "w"; };

};
