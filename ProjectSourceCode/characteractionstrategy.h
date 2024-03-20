#pragma once

namespace characteractionstrategy {
    class CharacterActionStrategy {
        public:
            virtual ~CharacterActionStrategy() = default;

            virtual void UseMovementStrategy() const = 0;
    };
}
