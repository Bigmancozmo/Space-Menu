#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

class SMButton {
public:
    static void onButton(CCObject* sender);
    static void errorOccuredOpening(const char* error);
};