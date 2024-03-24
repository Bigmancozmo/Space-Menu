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
    void hideButton();
    void showButton();
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
    CCMenuItemSpriteExtra* sm_button;
};

inline void SMLayer::hideButton()
{
    sm_button->setVisible(false);
}

inline void SMLayer::showButton()
{
    sm_button->setVisible(true);
}

bool SMLayer::init() {
    if (!CCLayer::init()) {
        return false;
    }
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    CCMenu* spaceMenu = CCMenu::create();
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("SM_Button.png"_spr);
    sm_button = CCMenuItemSpriteExtra::create(
        sprite, this, menu_selector(SMLayer::onButton)
    );

    float buttonSize = 0.25f;
    sprite->setScale(buttonSize);
    sprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    sprite->setPosition(CCPoint(0.0f, 0.0f));
    sm_button->setContentSize(CCSize(128.0f * buttonSize, 128.0f * buttonSize));

    sm_button->setPositionX(screenSize.width / -2 + 57);
    sm_button->setPositionY(screenSize.height / 2 - 18.5f);

    spaceMenu->addChild(sm_button);
    spaceMenu->setID("SMButtonMenu");
    this->addChild(spaceMenu);
    this->setID("SMLayer");

    this->setZOrder(999);

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