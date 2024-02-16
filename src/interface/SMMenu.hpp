#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class SMMenu : CCLayer {
public:
    static CCLayer* create();
};

CCLayer* SMMenu::create() {
    auto layer = CCLayer::create();
    layer->setID("spacemenu-ui");

    auto text = CCLabelBMFont::create("Hello, World!", "bigFont.fnt");
    layer->addChild(text);

    return layer;
}