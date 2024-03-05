#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(SMButton, MenuLayer){
    void onButton(CCObject*){
        FLAlertLayer::create("Space Menu", "What are we setting up Cameron?", "OK");
    }

    bool init(){
        if(!MenuLayer::init()) return false;

        CCMenu* spaceMenu = CCMenu::create();
        CCSprite* sprite = CCSprite::create("SM_Button.png"_spr);
        CCMenuItemSpriteExtra* sm_button = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(SMButton::onButton)
        );

        spaceMenu->addChild(sm_button);
        this->addChild(spaceMenu);
        return true;
    }
};