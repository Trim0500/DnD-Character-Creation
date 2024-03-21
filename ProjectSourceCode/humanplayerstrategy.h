#pragma once

#include "characteractionstrategy.h"

using namespace characteractionstrategy;

namespace humanplayerstrategy {
    class HumanPlayerStrategy : public CharacterActionStrategy {
        public:
            std::vector<CellActionInfo> UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>>&, const int&, const int&) const override;
    };
}
