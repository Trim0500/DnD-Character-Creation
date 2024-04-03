#pragma once

#include "Interactable.h"

class EmptyCell : public Interactable::Interactable
{
public:
	bool passable() { return true; }
};

