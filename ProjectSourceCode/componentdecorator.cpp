#include "componentdecorator.h"

namespace {

}

namespace componentdecorator {
    int ComponentDecorator::Ability_Score_Natural(int _anilityScore, int _attackTurnNumber) {
        return wrappee->Ability_Score_Natural(_anilityScore, _attackTurnNumber);
    }

    int ComponentDecorator::ModifierDecorator(int _anilityScore) {
        return Ability_Score_Natural(_anilityScore, 0);
    }

    std::vector<AbstractComponent*> ComponentDecorator::GetDecoratorList() {
        return wrappee->GetDecoratorList();
    }
}