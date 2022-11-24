set(PROJECT_NAME EloDopamine)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "Main.cpp"
)
source_group("" FILES ${no_group_source_files})

set(Core/Game
        "Core/EloDopamine/EloDopamine.h"
        "Core/Game/Offsets.h"
)
source_group("Core/Game" FILES ${Game})

set(Game__Controller
    "Core/Game/InputController/InputController.cpp"
    "Core/Game/InputController/InputController.h"
)
source_group("Game\\Controller" FILES ${Game__Controller})

set(Game__Controller__Orders
    "Core/Game/InputController/Orders/BlockInputOrder.h"
    "Core/Game/InputController/Orders/KeyClickOrder.h"
    "Core/Game/InputController/Orders/MouseMoveOrder.h"
    "Core/Game/InputController/Orders/OrderBase.h"
    "Core/Game/InputController/Orders/RightClickOrder.h"
    "Core/Game/InputController/Orders/TimeoutOrder.h"
)
source_group("Game\\Controller\\Orders" FILES ${Game__Controller__Orders})

set(Game__Engine
    "Core/Game/Engine/Engine.cpp"
    "Core/Game/Engine/Engine.h"
)
source_group("Game\\Engine" FILES ${Game__Engine})

set(Game__GameData
    "Core/Game/GameData/GameData.cpp"
    "Core/Game/GameData/GameData.h"
    "Core/Game/GameData/UnitInfo.cpp"
    "Core/Game/GameData/UnitInfo.h"
)
source_group("Game\\GameData" FILES ${Game__GameData})

set(Game__GameObjects__GameObject
    "Core/Game/GameObjects/GameObject.cpp"
    "Core/Game/GameObjects/GameObject.h"
)
source_group("Game\\GameObjects\\GameObject" FILES ${Game__GameObjects__GameObject})

set(Game__GameObjects__Hero
    "Core/Game/GameObjects/Hero/Hero.cpp"
    "Core/Game/GameObjects/Hero/Hero.h"
)
source_group("Game\\GameObjects\\Hero" FILES ${Game__GameObjects__Hero})

set(Game__GameObjects__Hero__AiManager
    "Core/Game/GameObjects/Hero/AiManager/AiManager.cpp"
    "Core/Game/GameObjects/Hero/AiManager/AiManager.h"
)
source_group("Game\\GameObjects\\Hero\\AiManager" FILES ${Game__GameObjects__Hero__AiManager})

set(Game__GameObjects__Hero__BuffManager
    "Core/Game/GameObjects/Hero/BuffManager/Buff.cpp"
    "Core/Game/GameObjects/Hero/BuffManager/Buff.h"
    "Core/Game/GameObjects/Hero/BuffManager/BuffManager.cpp"
    "Core/Game/GameObjects/Hero/BuffManager/BuffManager.h"
)
source_group("Game\\GameObjects\\Hero\\BuffManager" FILES ${Game__GameObjects__Hero__BuffManager})

set(Game__GameObjects__Hero__SpellBook
    "Core/Game/GameObjects/Hero/SpellBook/Spell.cpp"
    "Core/Game/GameObjects/Hero/SpellBook/Spell.h"
)
source_group("Game\\GameObjects\\Hero\\SpellBook" FILES ${Game__GameObjects__Hero__SpellBook})

set(Game__GameObjects__Minion
    "Core/Game/GameObjects/Minion/Minion.cpp"
    "Core/Game/GameObjects/Minion/Minion.h"
)
source_group("Game\\GameObjects\\Minion" FILES ${Game__GameObjects__Minion})

set(Game__Managers
    "Core/Game/Managers/ModuleManager/ModuleManager.cpp"
    "Core/Game/Managers/ModuleManager/ModuleManager.h"
    "Core/Game/Managers/ObjectManager/ObjectManager.cpp"
    "Core/Game/Managers/ObjectManager/ObjectManager.h"
)
source_group("Game\\Managers" FILES ${Game__Managers})

set(Game__Renderer
    "Core/Game/Renderer/Overlay/Overlay.cpp"
    "Core/Game/Renderer/Overlay/Overlay.h"
    "Core/Game/Renderer/Renderer.cpp"
    "Core/Game/Renderer/Renderer.h"
    "Core/Game/Managers/TextureManager/TextureManager.cpp"
    "Core/Game/Managers/TextureManager/TextureManager.h"
)
source_group("Game\\Renderer" FILES ${Game__Renderer})

set(Imgui
    "imgui/imconfig.h"
    "imgui/imgui.cpp"
    "imgui/imgui.h"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_impl_dx11.cpp"
    "imgui/imgui_impl_dx11.h"
    "imgui/imgui_impl_win32.cpp"
    "imgui/imgui_impl_win32.h"
    "imgui/imgui_internal.h"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"
    "imgui/imstb_rectpack.h"
    "imgui/imstb_textedit.h"
    "imgui/imstb_truetype.h"
)
source_group("Imgui" FILES ${Imgui})

set(Memory
    "Core/Game/Managers/MemoryManager/MemoryManager.cpp"
    "Core/Game/Managers/MemoryManager/MemoryManager.h"
)
source_group("Memory" FILES ${Memory})

set(Modules
    "Core/Game/Managers/ModuleManager/Module.h"
)
source_group("Modules" FILES ${Modules})

set(Modules__Avareness
    "Modules/Avareness/Avareness.cpp"
    "Modules/Avareness/Avareness.h"
)
source_group("Modules\\Avareness" FILES ${Modules__Avareness})

set(Modules__OrbWalker
    "Modules/OrbWalker/OrbWalker.cpp"
    "Modules/OrbWalker/OrbWalker.h"
)
source_group("Modules\\OrbWalker" FILES ${Modules__OrbWalker})

set(Modules__SpellTracker
    "Modules/SpellTracker/SpellTracker.cpp"
    "Modules/SpellTracker/SpellTracker.h"
)
source_group("Modules\\SpellTracker" FILES ${Modules__SpellTracker})

set(Security
    "Core/Security/XorStr.hpp"
)
source_group("Security" FILES ${Security})

set(Utils
    "Core/Utils/KeyCodes.h"
    "Core/Utils/Logger.h"
    "Core/Math/Math.h"
    "Core/Utils/stb_image.h"
    "Core/Utils/StringUtils.h"
)
source_group("Utils" FILES ${Utils})

set(ALL_FILES
    ${no_group_source_files}
    ${Game}
    ${Game__Controller}
    ${Game__Controller__Orders}
    ${Game__Engine}
    ${Game__GameData}
    ${Game__GameObjects__GameObject}
    ${Game__GameObjects__Hero}
    ${Game__GameObjects__Hero__AiManager}
    ${Game__GameObjects__Hero__BuffManager}
    ${Game__GameObjects__Hero__SpellBook}
    ${Game__GameObjects__Minion}
    ${Game__Managers}
    ${Game__Renderer}
    ${Imgui}
    ${Memory}
    ${Modules}
    ${Modules__Avareness}
    ${Modules__OrbWalker}
    ${Modules__SpellTracker}
    ${Security}
    ${Utils}
        Core/Game/Offsets.cpp Core/EloDopamine/EloDopamine.cpp Core/Game/GameObjects/Hero/ActiveSpell/ActiveSpell.cpp Core/Game/GameObjects/Hero/ActiveSpell/ActiveSpell.h Core/Game/GameData/SpellInfo.cpp Core/Game/GameData/SpellInfo.h Modules/Evade/Evade.cpp Modules/Evade/Evade.h Modules/Evade/EvadableSpell.h Modules/Evade/Helpers/SpellListingService.cpp Modules/Evade/Helpers/SpellListingService.h Core/Game/GameData/Missile.cpp Core/Game/GameData/Missile.h Modules/Evade/Helpers/EvadeDrawings.h)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE EloDopamine)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd5105;
            /wd4244;
            /wd4305;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            ;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "d3d11.lib;"
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3dx11.lib;"
        "dxgi.lib"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "d3d11;"
        "d3dx11.lib;"
        "dxgi"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

