#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class SMMenu : CCLayer {
public:
    static SMMenu* create();
};

SMMenu* SMMenu::create() {
    auto layer = SMMenu::create();
    layer->setID("spacemenu-ui");

    auto text = CCLabelBMFont::create("Hello, World!", "bigFont.fnt");
    layer->addChild(text);

    return layer;
}