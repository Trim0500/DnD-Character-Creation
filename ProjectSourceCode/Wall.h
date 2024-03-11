#pragma once

#include "Interactable.h"

class Wall : public Interactable::Interactable
{
public:

	bool passable() { return false; }
};

