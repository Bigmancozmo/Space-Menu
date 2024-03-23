#pragma once

#include <Geode/Geode.hpp>
#include <iostream>

using namespace geode::prelude;

class Hack {
public:
	inline static std::string name = "Hack";
	inline static std::string description = "Placeholder";
	inline static bool enabled = false;
	inline static void setEnabled(bool enabled2) {
		enabled = enabled2;
	}
	inline static void loadValue() {
		std::string hackKey = name + "-hack";
		setEnabled(Mod::get()->getSavedValue<bool>(hackKey, false));
	}
};