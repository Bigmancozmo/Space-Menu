#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "hacks/Hacks.h"

#include <iostream>

using namespace std;
using namespace geode::prelude;

class $modify(PlayLayer) {
	void destroyPlayer(PlayerObject * player, GameObject * p1) {
		if (Hacks::isEnabled(Noclip::hackKey)) {
			if (Hacks::isEnabled(NoclipFlashOnDeath::hackKey)) {
				cout << "flash screen here" << endl;
			}
		} else {
			PlayLayer::destroyPlayer(player, p1);
		}
	}
};
