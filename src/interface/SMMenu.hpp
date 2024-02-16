#pragma once

#include <Geode/Geode.hpp>
#include "utils/UsefulRenames.h"

using namespace geode::prelude;

class SMMenu : Layer {
public:
    static Layer* create();
};

Layer* SMMenu::create() {
    auto layer = Layer::create();
    layer->setID("spacemenu-ui");

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    auto text = CCLabelBMFont::create("Hello, World!", "bigFont.fnt");

    auto background = CCScale9Sprite::create("GJ_square02.png");
    background->setContentSize(screenSize - Vec2(50, 50));
    background->setID("sm-background");

    layer->setZOrder(100);

    // add children
    layer->addChild(background);
    background->addChild(text);

    return layer;
}