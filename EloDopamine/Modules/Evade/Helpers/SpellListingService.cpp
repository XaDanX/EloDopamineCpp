//
// Created by XaDanX on 11/20/2022.
//

#include "SpellListingService.h"
#include "../../../Core/Game/Managers/ObjectManager/ObjectManager.h"
#include "../../../Core/Game/GameObjects/Hero/Hero.h"

void SpellListingService::UpdateActiveSpell() {
    for (Hero& hero : objectManager->GetHeroList()) {
        //if (hero.team == objectManager->GetLocalPlayer().team) continue;
        auto activeSpell = hero.GetActiveSpell();
        if (activeSpell.has_value()) {
            auto missile = activeSpell->GetMissile();

            if (this->missiles.contains(missile.name)) continue;

            this->missiles[missile.name] = missile;
            // TODO::Evadable spells database
        }
    }
}

void SpellListingService::ValidateSpells() {
    for (auto it = this->missiles.begin(), next_it = it; it != this->missiles.end(); it = next_it) {
        ++next_it;

        auto currentMissile = it->second;
        if (!(currentMissile.spellInfo->width == 0 && currentMissile.spellInfo->height == 0)) {
            auto spellLength = currentMissile.startPos.distance(currentMissile.endPos);
            auto travelTime = spellLength / currentMissile.spellInfo->speed;

            if (currentMissile.startTime + currentMissile.spellInfo->castTime + travelTime < engine->GameTime()) {
                this->missiles.erase(it);
            }
        } else {
            if (currentMissile.startTime + currentMissile.spellInfo->castTime < engine->GameTime()) {
                this->missiles.erase(it);
            }
        }
    }
}

void SpellListingService::Update() {

    this->UpdateActiveSpell();
    this->ValidateSpells();

}
