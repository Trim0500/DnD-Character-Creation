#pragma once

#include <vector>

namespace abstractcomponent
{
    class AbstractComponent
    {
        public:
            virtual int Ability_Score_Natural(int) { return 0; };
            virtual std::vector<AbstractComponent*> GetDecoratorList() { std::vector<AbstractComponent*> initDecorators; return initDecorators; };
    };
}

