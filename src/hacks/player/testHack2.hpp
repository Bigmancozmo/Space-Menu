#pragma once

#include <Geode/Geode.hpp>
#include "hacks/hack.hpp"
#include "hacks/hacks.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class TestHack2 : public Hack {
public:
	inline static std::string name = "Test Hack 2";
	inline static std::string description = "Test Hack 2";
	inline static std::string hackKey = "test-hack-2-hack";

	inline static void setEnabled(bool enabled) {
		Hacks::setModEnabled(hackKey, enabled);
	}
	inline static void loadValue() {
		cout << Mod::get()->getSavedValue<bool>(hackKey) << endl;
		Hacks::setModEnabled(hackKey, Mod::get()->getSavedValue<bool>(hackKey));
	}
};
