#include <iostream>
#include "Logger.h"
#include "Offsets.h"
#include "EloDopamine.h"

int main() {
    logger->SetLevel(LogLevel::Debug);
    eloDopamine->Initialize();

    while (true) {
        eloDopamine->Update();
    }
}