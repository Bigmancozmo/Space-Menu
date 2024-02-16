#pragma once

#include <Geode/Geode.hpp>
#include "util/UsefulRenames.h"

using namespace geode::prelude;

class SMMenu : CCLayer {
public:
    static CCLayer* create();
};

CCLayer* SMMenu::create() {
    auto layer = CCLayer::create();
    layer->setID("spacemenu-ui");

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    auto text = CCLabelBMFont::create("Hello, World!", "bigFont.fnt");
    text->setPosition(screenSize / 2);

    auto background = CCScale9Sprite::create("GJ_square02.png");
    background->setContentSize(Vec2(150, 150));
    background->setID("sm-background");

    layer->setZOrder(100);

    // add children
    layer->addChild(text);
    layer->addChild(background);

    return layer;
}