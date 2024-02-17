#pragma once

#include <Geode/Geode.hpp>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include "utils/UsefulRenames.h"
#else
    #include "../utils/UsefulRenames.h"
#endif

using namespace geode::prelude;

class SMRandomData {
public:
    inline static bool isOpen = false;
    inline static Layer* meAsLayer = nullptr;
};