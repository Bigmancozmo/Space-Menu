#pragma once

#include <iostream>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class Hacks {
public:
	inline static void setEnabled(std::string modName, bool enabled) {
		modsEnabled[modName] = enabled;
		Mod::get()->setSavedValue<bool>(modName, enabled);
	};

	inline static bool isEnabled(std::string modName) {
		return modsEnabled[modName];
	};

private:
	inline static std::map<std::string, bool> modsEnabled{
		{ "noclip-hack", false }
	};
};