#pragma once

#include <Geode/Geode.hpp>
#include <iostream>

using namespace geode::prelude;
using namespace std;

class Hack {
public:
	inline static std::string name = "Hack";
	inline static std::string description = "Placeholder";
	inline static bool enabled = false;
	inline static std::string hackKey;
	inline static CCMenuItemToggler* myToggle;
	inline static void setEnabled(bool enabled2) {
		enabled = enabled2; 
		Mod::get()->setSavedValue<bool>(hackKey, enabled2);
	}
	inline static void loadValue() {
		setEnabled(Mod::get()->getSavedValue<bool>(hackKey, false));
	}
	inline static bool getEnabled() {
		return enabled;
	}
};