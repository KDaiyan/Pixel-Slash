#pragma once

#include <unordered_map>
#include "AssetList.hpp"
#include "FilePath.hpp"

inline std::unordered_map<Asset, FilePath> g_assetMap = {
    /// Maps
    {Assets::Maps::Start_Menu, FilePath{"assets/maps/start_menu.png"}},
    {Assets::Maps::Forest_Cave, FilePath("assets/maps/forest_cave.png")},
    {Assets::Maps::Shaded_Cave, FilePath("assets/maps/shaded_cave.png")},

    /// Icons/Buttons
    {Assets::Icons::Play_Button, FilePath("assets/icons/play_button.png")},
    {Assets::Icons::Settings_Button, FilePath("assets/icons/settings_button.png")},
    {Assets::Icons::Quit_Button, FilePath("assets/icons/quit_button.png")},
    {Assets::Icons::Logo, FilePath("assets/icons/logo.png")},
    {Assets::Icons::Home_Button, FilePath("assets/icons/home_button.png")},
    {Assets::Icons::Replay_Button, FilePath("assets/icons/replay_button.png")},
    {Assets::Icons::Exit_Button, FilePath("assets/icons/exit_button.png")},

    /// Coin Assets
    {Assets::Items::Coin, FilePath("assets/items/coin.png")},

    /// Soldier Assets
    {Assets::Entity::Soldier_Attack, FilePath("assets/player/soldier_attack.png")},
    {Assets::Entity::Soldier_Death, FilePath("assets/player/soldier_death.png")},
    {Assets::Entity::Soldier_Damaged, FilePath("assets/player/soldier_damaged.png")},
    {Assets::Entity::Soldier_Idle, FilePath("assets/player/soldier_idle.png")},
    {Assets::Entity::Soldier_Walk, FilePath("assets/player/soldier_walk.png")},

    /// Orc Assets
    {Assets::Entity::Orc_Attack, FilePath("assets/player/orc_attack.png")},
    {Assets::Entity::Orc_Death, FilePath("assets/player/orc_death.png")},
    {Assets::Entity::Orc_Damaged, FilePath("assets/player/orc_damaged.png")},
    {Assets::Entity::Orc_Idle, FilePath("assets/player/orc_idle.png")},
    {Assets::Entity::Orc_Walk, FilePath("assets/player/orc_walk.png")},

    /// Pillar Assets
    {Assets::BackgroundObjects::Pillar, FilePath("assets/background-objects/wooden_pillar.png")},
    {Assets::BackgroundObjects::Pillar_Head, FilePath("assets/background-objects/wooden_pillar_head.png")},

    /// Scroll
    {Assets::BackgroundObjects::Scroll, FilePath("assets/background-objects/scroll.png")},

    /// Fonts
    {Assets::Fonts::Quinque_Five, FilePath("assets/fonts/quinque_five.ttf")},

    /// Cave outline
    {Assets::BackgroundObjects::Cave_Outline, FilePath("assets/background-objects/cave_outline.png")}
};

namespace AssetHandler {
    inline FilePath get_path(const Asset& asset) {
        const auto path_iterator = g_assetMap.find(asset);
        assert(path_iterator != g_assetMap.end());
        return path_iterator->second;
    }
}
