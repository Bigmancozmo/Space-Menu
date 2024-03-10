#pragma once

#include <Geode/Geode.hpp>
#include <iostream>

using namespace geode::prelude;
using namespace std;

class SMLayer : public CCLayer {
public:
    virtual bool init();
    static SMLayer* create();
    void onButton(CCObject* obj) {
        FLAlertLayer::create("Space Menu", "What are we setting up Cameron Cameron?", "OK")->show();
    };

private:
    bool buttonExists;
};

bool SMLayer::init() {
    if (!CCLayer::init()) {
        return false;
    }

    if (buttonExists) return true;

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

    buttonExists = true;

    return true;
}

SMLayer* SMLayer::create() {
    SMLayer* me = new SMLayer();
    me->init();
    return me;
}