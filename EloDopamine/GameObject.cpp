#include "GameObject.h"


bool GameObject::Load(unsigned int objectAddress, bool deepLoad /* if true load all strings etc. */) {

    return false;
}

bool GameObject::CanAttack() {
    return this->actionState & CharacterState::CanAttack;
}

bool GameObject::CanMove() {
    return this->actionState & CharacterState::CanMove;
}

bool GameObject::CanCast() {
    return this->actionState & CharacterState::CanCast;
}

bool GameObject::CheckState(CharacterState state) {
    return this->actionState & state;
}


UnitInfo* GameObject::GetUnitInfo() {
    return this->unitInfo;
}