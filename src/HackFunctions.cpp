#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "hacks/IncludeHacks.h"

using namespace geode::prelude;

class $modify(PlayLayer) {
	void destroyPlayer(PlayerObject * player, GameObject * p1) {
		if (!(Hacks::getModEnabled(Noclip::hackKey))) {
			PlayLayer::destroyPlayer(player, p1);
		}
	}
};