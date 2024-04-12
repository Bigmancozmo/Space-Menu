#pragma once

#include <Geode/Geode.hpp>
#include <iostream>
#include "../HackTemplate.hpp"
#include "../HackManager.hpp"

using namespace geode::prelude;

class NoclipFlashOnDeath : public Hack {
public:
	inline static std::string name = "Flash On Death";
	inline static std::string description = "Allows the player to clip through blocks and spikes.";
	inline static std::string hackKey = "noclip--flashondeath-hack";

	inline static void setEnabled(bool enabled) {
		Hacks::setEnabled(hackKey, enabled);
	}
	inline static void loadValue() {
		cout << Mod::get()->getSavedValue<bool>(hackKey) << endl;
		Hacks::setEnabled(hackKey, Mod::get()->getSavedValue<bool>(hackKey));
	}
};
