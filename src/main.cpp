#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "interface/sm_layer.hpp"
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <iostream>

using namespace geode::prelude;
using namespace keybinds;

bool buttonExists = false;

class $modify(MenuLayer){

    bool init() {
        if (!MenuLayer::init()) return false;

        if (!Mod::get()->setSavedValue("seen-intro-popup", true)) {
            FLAlertLayer* popup = FLAlertLayer::create(
                "SpaceMenu",
                "Welcome to SpaceMenu!\n<cb>Use the Page Down key or press the button.</c>",
                "OK"
            );
            popup->m_scene = this;
            popup->show();
        }

        if (buttonExists) return true;

        auto layer = SMLayer::create();
        this->addChild(layer);

        SceneManager::get()->keepAcrossScenes(layer);

        buttonExists = true;

        return true;
    }
};

// register keys
#ifdef GEODE_IS_WINDOWS
$execute{
    using namespace keybinds;

    BindManager::get()->registerBindable({
        "close-spacemenu"_spr,
        "Close SpaceMenu",
        "",
        { Keybind::create(KEY_Escape, Modifier::None) },
        "SpaceMenu/Menu Keybinds"
    });

    BindManager::get()->registerBindable({
        "open-spacemenu"_spr,
        "Open SpaceMenu",
        "",
        { Keybind::create(KEY_PageDown, Modifier::None) },
        "SpaceMenu/Menu Keybinds"
    });
}
#endif