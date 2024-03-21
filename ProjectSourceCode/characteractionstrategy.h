#pragma once

#include <vector>
#include <string>

#include "Interactable.h"

namespace characteractionstrategy {
    struct CellActionInfo {
        int row = 0;
        int col = 0;
        std::string cellColor = "";
        std::string actionName = "";
    };

    class CharacterActionStrategy {
        public:
            virtual ~CharacterActionStrategy() = default;

            virtual std::vector<CellActionInfo> UseMovementStrategy(std::vector<std::vector<Interactable::Interactable*>>&, const int&, const int&) const = 0;
    };
}
