#pragma once

namespace abstractcomponent
{
    class AbstractComponent
    {
        public:
            virtual int Ability_Score_Natural(int) { return 0; };
    };
}

