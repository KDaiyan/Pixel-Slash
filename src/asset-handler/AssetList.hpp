#pragma once

#include <variant>

namespace Assets {

enum struct Maps {
    Forest_Cave,
    Start_Menu,
    Shaded_Cave
};

enum struct Entity {
    Soldier_Attack,
    Soldier_Death,
    Soldier_Damaged,
    Soldier_Idle,
    Soldier_Walk,
    Orc_Attack,
    Orc_Death,
    Orc_Damaged,
    Orc_Idle,
    Orc_Walk,
};

enum struct Items {
    Standard_Sword,
    Standard_Bow,
    Coin
};

enum struct Icons {
    Button,
    Play_Button,
    Quit_Button,
    Settings_Button,
    Home_Button,
    Replay_Button,
    Exit_Button,
    Logo
};

enum struct BackgroundObjects {
    Pillar,
    Pillar_Head,
    Scroll,
    Cave_Outline
};

enum struct Fonts {
    Quinque_Five
};

}

using Asset = std::variant<
    Assets::Items,
    Assets::Maps,
    Assets::Entity,
    Assets::Icons,
    Assets::BackgroundObjects,
    Assets::Fonts>;