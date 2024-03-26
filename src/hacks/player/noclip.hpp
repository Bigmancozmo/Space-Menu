#pragma once

#include <Geode/Geode.hpp>
#include <iostream>
#include "../HackTemplate.hpp"
#include "../HackManager.hpp"

using namespace geode::prelude;

class Noclip : public Hack {
public:
	inline static std::string name = "Noclip";
	inline static std::string description = "Allows the player to clip through blocks and spikes.";
	inline static std::string hackKey = "noclip-hack";

	inline static void setEnabled(bool enabled) {
		Hacks::setModEnabled(hackKey, enabled);
	}
	inline static void loadValue() {
		cout << Mod::get()->getSavedValue<bool>(hackKey) << endl;
		Hacks::setModEnabled(hackKey, Mod::get()->getSavedValue<bool>(hackKey));
	}
};