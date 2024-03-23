#pragma once

#include <Geode/Geode.hpp>
#include "hacks/hack.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class Noclip : public Hack {
public:
	inline static std::string name = "Noclip";
	inline static std::string description = "Allows the player to clip through blocks and spikes.";
};

class $modify(PlayLayer) {
	void destroyPlayer(PlayerObject * player, GameObject * p1) {
		if (!Noclip::enabled) { PlayLayer::destroyPlayer(player, p1); }
	}
};