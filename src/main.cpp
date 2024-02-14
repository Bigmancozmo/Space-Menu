#include <Geode/Geode.hpp>

// layers
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

#include "interface/SMButton.h"

using namespace geode::prelude;
using namespace std;

void SMButton::onButton(CCObject* sender){
    FLAlertLayer::create(
        "Title",    // title
        "Hi mom!",  // content
        "OK"        // button
    )->show();
}

void createButton(CCLayer* layer){
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		
	auto spr = ButtonSprite::create("S");
	auto menu = CCMenu::create();
	
	auto btn = CCMenuItemSpriteExtra::create(
		spr, layer, menu_selector(SMButton::onButton)
	);
		btn->setID("spacemenu-button");

		btn->setAnchorPoint(CCPoint(0.5f, 0.5f));
		btn->setPosition(CCPoint(50.0f, screenSize.height - 40.0f));
		
		menu->setPosition(CCPoint(0.0f, 0.0f));
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
		
		createButton(this);

		Mod::get()->setSavedValue<bool>("has-been-used", true);

        return true;
	}
};

class $modify(CreatorLayer){
	bool init(){
		if(!CreatorLayer::init()) return false;
		createButton(this);
		return true;
	}
};

class $modify(LevelBrowserLayer){
	bool init(GJSearchObject* p0){
		if(!LevelBrowserLayer::init(p0)) return false;
		createButton(this);
		return true;
	}
};

class $modify(LevelInfoLayer){
	bool init(LevelInfoLayer* p0, bool p1){
		if(!LevelInfoLayer::init(p0, p1)) return false;
		createButton(this);
		return true;
	}
};