#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "interface/sm_layer.hpp"

using namespace geode::prelude;

bool buttonExists = false;

class $modify(MenuLayer){

    bool init() {
        if (!MenuLayer::init()) return false;
        if (buttonExists) return true;

        auto layer = SMLayer::create();
        this->addChild(layer);

        SceneManager::get()->keepAcrossScenes(layer);

        buttonExists = true;

        return true;
    }
};