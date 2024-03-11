#pragma once

#include <Geode/Geode.hpp>
#include <iostream>
#include "mod_menu.hpp"
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;
using namespace std;
using namespace keybinds;

class SMLayer : public CCLayer {
public:
    virtual bool init();
    static SMLayer* create();
    void onButton(CCObject* obj) {
        if (menuWasCreated) {
            menu->show();
        }
        else {
            menu = SpaceMenu::create();
            this->addChild(menu);
        }
        menuWasCreated = true;
    };
private:
    bool menuWasCreated = false;
    SpaceMenu* menu;
};

bool SMLayer::init() {
    if (!CCLayer::init()) {
        return false;
    }

    CCMenu* spaceMenu = CCMenu::create();
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("SM_Button.png"_spr);
    CCMenuItemSpriteExtra* sm_button = CCMenuItemSpriteExtra::create(
        sprite, this, menu_selector(SMLayer::onButton)
    );

    float buttonSize = 0.25f;
    sprite->setScale(buttonSize);
    sprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    sprite->setPosition(CCPoint(0.0f, 0.0f));
    sm_button->setContentSize(CCSize(128.0f * buttonSize, 128.0f * buttonSize));

    spaceMenu->addChild(sm_button);
    spaceMenu->setID("SMButtonMenu");
    this->addChild(spaceMenu);
    this->setID("SMLayer");

#ifdef GEODE_IS_WINDOWS
    this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
        if (event->isDown()) {
            cout << "open SM" << endl;
            SMLayer::onButton(nullptr);
        }
        return ListenerResult::Propagate;
        }, "open-spacemenu"_spr);
#endif

    return true;
}

SMLayer* SMLayer::create() {
    SMLayer* me = new SMLayer();
    me->init();
    return me;
}

