#pragma once

#include <Geode/Geode.hpp>
#include <iostream>

using namespace geode::prelude;
using namespace std;

class SpaceMenu : public CCMenu {
public:
    virtual bool init();
    static SpaceMenu* create();
};

bool SpaceMenu::init() {
    if (!CCMenu::init()) {
        return false;
    }

    cout << "wenis" << endl;

    return true;
}

SpaceMenu* SpaceMenu::create() {
    SpaceMenu* me = new SpaceMenu();
    me->init();
    return me;
}