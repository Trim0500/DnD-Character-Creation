#pragma once

#include "characteractionstrategy.h"

using namespace characteractionstrategy;

namespace humanplayerstrategy {
    class HumanPlayerStrategy : public CharacterActionStrategy {
        public:
            void UseMovementStrategy() const override;
    };
}
