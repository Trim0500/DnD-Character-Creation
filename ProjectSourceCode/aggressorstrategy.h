#pragma once

#include "characteractionstrategy.h"

using namespace characteractionstrategy;

namespace aggressorstrategy {
    class AggressorStrategy : public CharacterActionStrategy {
        void UseMovementStrategy() const override;
    };
}
