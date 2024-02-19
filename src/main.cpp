// geode includes
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/GauntletLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/SecretRewardsLayer.hpp>

// spacemenu includes
#include "interface/SMMenu.hpp"
#include "interface/SMButton.h"
#include "utils/UsefulRenames.h"
#include "data/SMRandomData.hpp"

// std includes
#include <iostream>
#include <sstream>
#include <string>

// dependeny includes
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;
using namespace std;
using namespace keybinds;

// vars
Layer* onButtonScene = nullptr;
SMMenu* spaceMenuLayer = nullptr;
Size screenSize;

void SMButton::errorOccuredOpening(const char* error){
	stringstream ss;
	ss << "An error occurred opening SpaceMenu!\n";
	ss << error;
	ss << "\nAn <cl>error report</c> has been sent to <cg>Bigmancozmo</c>.";
	FLAlertLayer::create("SpaceMenu", ss.str().c_str(), "OK")->show();
}

void SMButton::onButton(Object* sender){
	if(onButtonScene != nullptr) {
		if((spaceMenuLayer == nullptr) || (SMRandomData::meAsLayer == nullptr) || (SMRandomData::smPanelLayer == nullptr)){
			spaceMenuLayer = SMMenu::create();
			onButtonScene->getParent()->addChild(spaceMenuLayer->getLayer());
		}
		spaceMenuLayer->openMenu();
	} else {
		errorOccuredOpening("<cg>onButtonScene</c> was <cl>nullptr</c>.");
	}
}

void createButton(Layer* layer){
	#ifndef GEODE_IS_WINDOWS
	screenSize = CCDirector::sharedDirector()->getWinSize();
	auto spr = ButtonSprite::create("S");
	auto menu = Menu::create();
	
	auto btn = CCMenuItemSpriteExtra::create(
		spr, layer, menu_selector(SMButton::onButton)
	);
	btn->setID("spacemenu-button");

	btn->setAnchorPoint(Vec2(0.5f, 0.5f));
	btn->setPosition(Vec2(50.0f, screenSize.height - 40.0f));
		
	menu->setPosition(Vec2(0.0f, 0.0f));
	menu->setZOrder(16); // Position the menu in front of everything else
	menu->setID("spacemenu-button-menu");

	menu->addChild(btn);
	layer->addChild(menu);
	#endif
}

class $modify(MenuLayer) {
	bool init(){
		if(!(MenuLayer::init())) return false;

		auto hasBeenUsed = Mod::get()->getSavedValue<bool>("has-been-used");

		if(!hasBeenUsed){
			#ifndef __ANDROID__
				auto alert = FLAlertLayer::create(
            		"SpaceMenu",
            		"Welcome to SpaceMenu!\n<cb>Press right-shift to begin!</c>",
            		"OK"
        		);
				alert->m_scene = this;
				alert->show();
			#else
				auto alert = FLAlertLayer::create(
            		"SpaceMenu",
            		"Welcome to SpaceMenu!\n<cb>Press the S button to begin!</c>",
            		"OK"
        		);
				alert->m_scene = this;
				alert->show();
			#endif
		}
		
		onButtonScene = this;
		createButton(this);

		Mod::get()->setSavedValue<bool>("has-been-used", true);

        return true;
	}
};

class $modify(CreatorLayer){
	bool init(){
		if(!CreatorLayer::init()) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

class $modify(LevelBrowserLayer){
	bool init(GJSearchObject* p0){
		if(!LevelBrowserLayer::init(p0)) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

class $modify(LevelInfoLayer){
	bool init(GJGameLevel* p0, bool p1){
		if(!LevelInfoLayer::init(p0, p1)) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

class $modify(GauntletSelectLayer){
	bool init(int p0){
		if(!GauntletSelectLayer::init(p0)) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

class $modify(LevelSelectLayer){
	bool init(int p0){
		if(!LevelSelectLayer::init(p0)) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

class $modify(PauseLayer){
	void customSetup(){
		PauseLayer::customSetup();
		onButtonScene = this;
		createButton(this);
	}
};

class $modify(GJGarageLayer){
	bool init(){
		if(!GJGarageLayer::init()) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

class $modify(LevelSearchLayer){
	bool init(int p0){
		if(!LevelSearchLayer::init(p0)) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

class $modify(GJShopLayer){
	bool init(ShopType p0){
		if(!GJShopLayer::init(p0)) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

class $modify(GauntletLayer){
	bool init(GauntletType p0){
		if(!GauntletLayer::init(p0)) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

class $modify(LeaderboardsLayer){
	bool init(LeaderboardState p0){
		if(!LeaderboardsLayer::init(p0)) return false;
		onButtonScene = this;
		createButton(this);
		return true;
	}
};

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__ANDROID__)
	class $modify(SecretRewardsLayer){ // doesnt work on mac
		bool init(bool p0){
			if(!SecretRewardsLayer::init(p0)) return false;
			onButtonScene = this;
			createButton(this);
			return true;
		}
	};
#endif

#ifdef GEODE_IS_WINDOWS
$execute {
	BindManager::get()->registerBindable({
        "open"_spr,
        "Open SpaceMenu",
        "Does exactly what you think it does.",
        { Keybind::create(KEY_RightShift, Modifier::None) },
        "SpaceMenu/General"
    });
	
	new EventListener([=](InvokeBindEvent* event) {
    	if(!SMRandomData::isOpen){
			SMButton::onButton(nullptr);
		}
		SMRandomData::isOpen = true;
	return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "open"_spr));
}
#endif
