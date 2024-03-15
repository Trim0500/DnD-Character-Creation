#pragma once

#include "abstractcomponent.h";

using namespace abstractcomponent;

namespace componentdecorator {
    class ComponentDecorator : public AbstractComponent
    {
        public: 
            ComponentDecorator() {};

            ComponentDecorator(AbstractComponent* _wrappee) { wrappee = _wrappee; };
            
            int Ability_Score_Natural(int) override;

            std::vector<AbstractComponent*> GetDecoratorList() override;
        protected:
            AbstractComponent* wrappee;
    };
}
