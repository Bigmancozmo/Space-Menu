#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

class SMButton {
public:
    void onButton(CCObject* sender);
    void errorOccuredOpening(const char* error);
    void disableMenuClicks();
    void enableMenuClicks();
};