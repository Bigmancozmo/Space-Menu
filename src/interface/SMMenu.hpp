#pragma once

#include <Geode/Geode.hpp>
#include <iostream>

// windows includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include "utils/UsefulRenames.h"
#else
    #include "../utils/UsefulRenames.h"
#endif

using namespace geode::prelude;
using namespace std;

class SMMenu : Layer {
public:
    static Layer* create();
};

Layer* SMMenu::create() {
    auto layer = Layer::create();
    auto infoLayer = Layer::create();
    infoLayer->setID("sm-info-layer");
    layer->setID("spacemenu-ui");

    auto touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
  	touchDispatcher->setForcePrio(touchDispatcher->getForcePrio() - 2);
    layer->setTouchEnabled(true);
    layer->setTouchMode(kCCTouchesOneByOne);
    layer->setMouseEnabled(true);
    layer->setKeypadEnabled(true);

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    Vec2 panelSize = screenSize - Vec2(50, 50);

    auto SM_Logo = Sprite::create("SM_FullLogo.png"_spr);
    SM_Logo->setAnchorPoint(Vec2(1.0f, 1.0f));
    SM_Logo->setScale(0.67f);
    SM_Logo->setPosition(panelSize - Vec2(11, 11));
    SM_Logo->setID("sm-logo-full");

    auto creatorText = CCLabelBMFont::create("by Bigmancozmo", "goldFont.fnt");
    creatorText->setID("sm-creator-label");
    creatorText->setPosition(panelSize - Vec2(76, 56));
    creatorText->setScale(0.525f);

    auto text = CCLabelBMFont::create("Hello, World!", "bigFont.fnt");
    text->setPosition(panelSize / 2);

    auto background = CCScale9Sprite::create("GJ_square02.png");
    background->setContentSize(panelSize);
    background->setID("sm-background");

    layer->setZOrder(100);

    // add children
    layer->addChild(background);
    background->addChild(text);
    infoLayer->addChild(SM_Logo);
    infoLayer->addChild(creatorText);
    background->addChild(infoLayer);

    

    return layer;
}