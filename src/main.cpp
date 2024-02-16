// geode includes
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>

// spacemenu includes
#include "interface/SMMenu.hpp"
#include "interface/SMButton.h"
#include "utils/UsefulRenames.h"

// std includes
#include <iostream>
#include <sstream>
#include <string>

using namespace geode::prelude;
using namespace std;

// vars
Layer* onButtonScene = nullptr;
Layer* spaceMenuLayer = nullptr;
CCSize screenSize;
bool isOpen = false;

void SMButton::disableMenuClicks(){
	CCObject* obj = NULL;
	CCARRAY_FOREACH(onButtonScene->getChildren(), obj)
	{
		CCNode* node = reinterpret_cast<CCNode*>(obj);
	    //node->setTouchEnabled(false);
	}
}

void SMButton::enableMenuClicks(){
	
}

void SMButton::errorOccuredOpening(const char* error){
	stringstream ss;
	ss << "An error occurred opening SpaceMenu!\n";
	ss << error;
	ss << "\nAn <cl>error report</c> has been sent to <cg>Bigmancozmo</c>.";
	FLAlertLayer::create("SpaceMenu", ss.str().c_str(), "OK")->show();
}

void SMButton::onButton(CCObject* sender){
	isOpen = !isOpen;
	if(onButtonScene != nullptr) {
		if(spaceMenuLayer == nullptr){
			spaceMenuLayer = SMMenu::create();
			onButtonScene->addChild(spaceMenuLayer);
		}
		if(isOpen){
			auto moveToAction = MoveTo::create(1, screenSize / 2);
			auto moveTo_eased = EaseElasticOut::create(moveToAction);
			
			spaceMenuLayer->setPosition(screenSize / 2 + Vec2(0, screenSize.height));
			spaceMenuLayer->setVisible(true);
			disableMenuClicks();
			spaceMenuLayer->runAction(moveTo_eased);
		} else {
			spaceMenuLayer->setVisible(false);
			enableMenuClicks();
		}
	} else {
		errorOccuredOpening("<cg>onButtonScene</c> was <cl>nullptr</c>.");
	}
}

void createButton(Layer* layer){
	if(spaceMenuLayer != nullptr){
		spaceMenuLayer->removeFromParent();
		spaceMenuLayer = nullptr;
		isOpen = false;
	}

	screenSize = CCDirector::sharedDirector()->getWinSize();
	auto spr = ButtonSprite::create("S");
	auto menu = CCMenu::create();
	
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
}

class $modify(MenuLayer) {
	bool init(){
		if(!(MenuLayer::init())) return false;

		auto hasBeenUsed = Mod::get()->getSavedValue<bool>("has-been-used");

		if(!hasBeenUsed){
			auto alert = FLAlertLayer::create(
            	"SpaceMenu",
            	"Welcome to SpaceMenu!\n<cb>Press right-shift to begin!</c>",
            	"OK"
        	);
			alert->m_scene = this;
			alert->show();
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