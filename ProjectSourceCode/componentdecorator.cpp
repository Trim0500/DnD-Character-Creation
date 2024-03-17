#include "componentdecorator.h"

namespace {

}

namespace componentdecorator {
    int ComponentDecorator::Ability_Score_Natural(int _anilityScore, int _attackTurnNumber) {
        return wrappee->Ability_Score_Natural(_anilityScore, _attackTurnNumber);
    }

    std::vector<AbstractComponent*> ComponentDecorator::GetDecoratorList() {
        return wrappee->GetDecoratorList();
    }
}