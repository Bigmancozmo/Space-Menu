#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "interface/sm_layer.hpp"

using namespace geode::prelude;


class $modify(MenuLayer){

    bool init() {
        if (!MenuLayer::init()) return false;
        auto layer = SMLayer::create();
        this->addChild(layer);

        SceneManager::get()->keepAcrossScenes(layer);

        return true;
    }
};