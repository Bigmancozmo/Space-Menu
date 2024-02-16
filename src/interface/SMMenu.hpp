#pragma once

#include <Geode/Geode.hpp>

// windows includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include "utils/UsefulRenames.h"
#else
    #include "../utils/UsefulRenames.h"
#endif

using namespace geode::prelude;

class SMMenu : Layer {
public:
    static Layer* create();
};

Layer* SMMenu::create() {
    auto layer = Layer::create();
    layer->setID("spacemenu-ui");

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    Vec2 panelSize = screenSize - Vec2(50, 50);

    auto logo = Sprite::create("SM_FullLogo.png"_spr);
    logo->setAnchorPoint(Vec2(0.5f, 1.0f));
    logo->setPosition(Vec2(panelSize.x / 2, panelSize.y));

    auto text = CCLabelBMFont::create("Hello, World!", "bigFont.fnt");
    text->setPosition(panelSize / 2);

    auto background = CCScale9Sprite::create("GJ_square02.png");
    background->setContentSize(panelSize);
    background->setID("sm-background");

    layer->setZOrder(100);

    // add children
    layer->addChild(background);
    background->addChild(text);
    background->addChild(logo);

    return layer;
}