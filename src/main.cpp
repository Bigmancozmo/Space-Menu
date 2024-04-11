#include <Geode/Geode.hpp>

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp> // hide
#include <Geode/modify/LevelSelectLayer.hpp> // show
#include <Geode/modify/LevelInfoLayer.hpp> // show
#include <Geode/modify/EditLevelLayer.hpp> // show / reset

#include "interface/SMLayer.hpp"
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
        smLayer->resetButtonPositioning();

        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        smLayer->setVisible(false);
        smLayer->showButton();
        return true;
    }
};

class $modify(PauseLayer) {
    void customSetup() {
        smLayer->resetButtonPositioning();
        PauseLayer::customSetup();
        smLayer->setVisible(true);
        smLayer->showButton();
    }
};

class $modify(EditLevelLayer) {
    bool init(GJGameLevel * level) {
        smLayer->resetButtonPositioning();
        if (!EditLevelLayer::init(level)) { return false; }
        smLayer->setVisible(true);
        smLayer->showButton();
        return true;
    }
};

class $modify(EditorPauseLayer) {
    bool init(LevelEditorLayer * level) {
        if (!EditorPauseLayer::init(level)) return false;

        auto guidelinesMenu = this->getChildByID("guidelines-menu");

        smLayer->setVisible(true);
        smLayer->showButton();
        smLayer->setButtonParent(guidelinesMenu);

        CCSprite* sprite = CCSprite::createWithSpriteFrameName("SM_Button.png"_spr);
        CCMenuItemSpriteExtra* sm_button = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(SMLayer::onButton)
        );

        float buttonSize = 0.25f;
        sprite->setScale(buttonSize);
        sprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
        sm_button->setContentSize(CCSize(128.0f * buttonSize, 128.0f * buttonSize));

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
