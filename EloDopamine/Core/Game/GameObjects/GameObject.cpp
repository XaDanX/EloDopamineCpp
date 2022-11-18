#include "GameObject.h"


bool GameObject::Load(unsigned int objectAddress, bool deepLoad) {

    return false;
}

[[maybe_unused]] bool GameObject::CanAttack() const {
    return this->actionState & CharacterState::CanAttack;
}

[[maybe_unused]] bool GameObject::CanMove() const {
    return this->actionState & CharacterState::CanMove;
}

[[maybe_unused]] bool GameObject::CanCast() const {
    return this->actionState & CharacterState::CanCast;
}

[[maybe_unused]] bool GameObject::CheckState(CharacterState state) {
    return this->actionState & state;
}


UnitInfo* GameObject::GetUnitInfo() {
    return this->unitInfo;
}