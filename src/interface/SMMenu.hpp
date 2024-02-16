#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class SMMenu : CCLayer {
public:
    static CCLayer* create();
    bool isOpen = false;    
};

CCLayer* SMMenu::create() {
    if(!isOpen){
        auto layer = CCLayer::create();
        layer->setID("spacemenu-ui");

        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

        auto text = CCLabelBMFont::create("Hello, World!", "bigFont.fnt");
        text->setPosition(screenSize / 2);
        layer->addChild(text);
    }
    isOpen = true;

    return layer;
}