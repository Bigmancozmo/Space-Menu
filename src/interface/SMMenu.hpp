#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class SMMenu : CCLayer {
public:
    static CCLayer* create();
};

CCLayer* SMMenu::create() {
    auto layer = CCLayer::create();
    return layer;
}