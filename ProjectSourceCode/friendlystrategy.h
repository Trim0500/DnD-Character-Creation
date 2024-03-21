#pragma once

#include "characteractionstrategy.h"

using namespace characteractionstrategy;

namespace friendlystrategy {
    class FriendlyStrategy : public CharacterActionStrategy {
        void UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>>&, const int&, const int&) const override;
    };
}
