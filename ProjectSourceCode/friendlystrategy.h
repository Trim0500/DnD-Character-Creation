#pragma once

#include "characteractionstrategy.h"

using namespace characteractionstrategy;

namespace friendlystrategy {
    class FriendlyStrategy : public CharacterActionStrategy {
        void UseMovementStrategy() const override;
    };
}
