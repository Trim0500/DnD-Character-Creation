#include "componentdecorator.h"

namespace {

}

namespace componentdecorator {
    int ComponentDecorator::Ability_Score_Natural(int _anilityScore) {
        return wrappee->Ability_Score_Natural(_anilityScore);
    }

    std::vector<AbstractComponent*> ComponentDecorator::GetDecoratorList() {
        return wrappee->GetDecoratorList();
    }
}