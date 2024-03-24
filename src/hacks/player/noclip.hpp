#pragma once

#include <Geode/Geode.hpp>
#include "hacks/hack.hpp"
#include "hacks/hacks.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class Noclip : public Hack {
public:
	inline static std::string name = "Noclip";
	inline static std::string description = "Allows the player to clip through blocks and spikes.";
	inline static std::string hackKey = "noclip-hack";

	inline static void setEnabled(bool enabled2) {
		Hacks::setModEnabled(hackKey, enabled2);
	}
	inline static void loadValue() {
		Hacks::setModEnabled(hackKey, Mod::get()->getSavedValue<bool>(hackKey, false));
	}
};

class $modify(PlayLayer) {
	void destroyPlayer(PlayerObject * player, GameObject * p1) {
		if (!(Hacks::getModEnabled(Noclip::hackKey))) {
			PlayLayer::destroyPlayer(player, p1);
		}
	}
};