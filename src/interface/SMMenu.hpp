#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class SMMenu : CCLayer {
public:
    static SMMenu* create();
};

SMMenu* SMMenu::create() {
    auto layer = CCLayer::create();
    return layer;
}