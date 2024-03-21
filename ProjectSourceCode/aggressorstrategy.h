#pragma once

#include "characteractionstrategy.h"

using namespace characteractionstrategy;

namespace aggressorstrategy {
    class AggressorStrategy : public CharacterActionStrategy {
        void UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>>&, const int&, const int&) const override;
    };
}
