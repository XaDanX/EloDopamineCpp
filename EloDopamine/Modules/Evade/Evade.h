#pragma once
#include "../../Core/Game/Managers/ModuleManager/Module.h"
#include "Helpers/SpellListingService.h"

class Evade : public ModuleBase {
private:
    SpellListingService* spellService = new SpellListingService();
public:
    void OnUpdate() override;
    void OnGui() override;
    std::string ModuleType() override;
    std::string GetName() override;

    void OnInitialize() override;
    void OnExit() override;
};

