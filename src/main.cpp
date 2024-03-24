#include <Geode/Geode.hpp>

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp> // show
#include <Geode/modify/LevelEditorLayer.hpp> // hide
#include <Geode/modify/LevelSelectLayer.hpp> // show
#include <Geode/modify/LevelInfoLayer.hpp> // show

#include "interface/sm_layer.hpp"
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <iostream>

using namespace geode::prelude;
using namespace keybinds;

bool buttonExists = false;
SMLayer* smLayer;

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

        smLayer = SMLayer::create();
        this->addChild(smLayer);

        smLayer->setVisible(true);
        smLayer->showButton();

        SceneManager::get()->keepAcrossScenes(smLayer);

        buttonExists = true;

        return true;
    }
};

class $modify(PlayLayer) {
    bool init(GJGameLevel * level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        smLayer->setVisible(false);
        smLayer->showButton();
        return true;
    }
};

class $modify(PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();
        smLayer->setVisible(true);
        smLayer->showButton();
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