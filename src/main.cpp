#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include "SMButton.h"

using namespace geode::prelude;
using namespace std;

void SMButton::onButton(CCObject* sender){
    FLAlertLayer::create(
        "Title",    // title
        "Hi mom!",  // content
        "OK"        // button
    )->show();
}

void createButtom(CCLayer* layer){
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

		cout << "SpaceMenu has spotted a Main Menu!" << endl;
		cout << "Adding button!" << endl;

        return true;
	}
};