#pragma once

#include <Geode/Geode.hpp>
#include <iostream>
#include "hacks/hacks.hpp"

using namespace geode::prelude;
using namespace std;

class Hack {
public:
	inline static std::string name = "Hack";
	inline static std::string description = "Placeholder";
	inline static std::string hackKey;

	inline static void setEnabled(bool enabled2) {
		Hacks::setModEnabled(hackKey, enabled2);
	}
	inline static void loadValue() {
		Hacks::setModEnabled(hackKey, Mod::get()->getSavedValue<bool>(hackKey, false));
	}
};