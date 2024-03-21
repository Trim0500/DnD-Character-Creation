#pragma once

#include <vector>

#include "Interactable.h"

namespace characteractionstrategy {
    class CharacterActionStrategy {
        public:
            virtual ~CharacterActionStrategy() = default;

            virtual void UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>>&, const int&, const int&) const = 0;
    };
}
