#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "src/hacks/Hacks.h"

using namespace geode::prelude;

class $modify(PlayLayer) {
	void destroyPlayer(PlayerObject * player, GameObject * p1) {
		if (!(Hacks::getModEnabled(Noclip::hackKey))) {
			PlayLayer::destroyPlayer(player, p1);
		}
	}
};