#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(SMButton, MenuLayer){

    bool init(){
        if(!MenuLayer::init()) return false;

        CCMenu* spaceMenu = CCMenu::create();
        CCSprite* sprite = CCSprite::create("SM_Button.png"_spr);
        CCMenuItemSpriteExtra* sm_button = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(SMButton::onButton)
        );

        spaceMenu->addChild(sm_button);
        this->addChild(spaceMenu);

        SceneManager::get()->keepAcrossScenes(spaceMenu);

        return true;
    }

    void onButton(CCObject*){
        FLAlertLayer::create("Space Menu", "What are we setting up Cameron Cameron?", "OK")->show();
    }
};