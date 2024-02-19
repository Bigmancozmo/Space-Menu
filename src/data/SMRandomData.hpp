#pragma once

#include <Geode/Geode.hpp>
#include "../utils/UsefulRenames.h"

using namespace geode::prelude;

class SMRandomData {
public:
    inline static bool isOpen = false;
    inline static Layer* meAsLayer = nullptr;
    inline static Layer* smPanelLayer = nullptr;
};