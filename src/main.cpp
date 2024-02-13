#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(SMModMenu, MenuLayer) {
	void onMenu(CCObject* sender){
		FLAlertLayer::create("GEODE", "hello", "OK")->show();
	}

	bool init(){
		if(!MenuLayer::init()) return false;

		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		
		auto spr = ButtonSprite::create("S");
		auto menu = CCMenu::create();
		
		auto btn = CCMenuItemSpriteExtra::create(
			spr, this, menu_selector(SMModMenu::onMenu)
		);
		btn->setID("spacemenu-button");
	
		btn->setAnchorPoint(CCPoint(0.5f, 0.5f));
		btn->setPosition(CCPoint(50.0f, screenSize.height - 40.0f));
	
		menu->setPosition(CCPoint(0.0f, 0.0f));
	
		menu->addChild(btn);
		this->addChild(menu);
		
        return true;
	}
};