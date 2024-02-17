#pragma once

#include <Geode/Geode.hpp>
#include <iostream>

// windows includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include "utils/UsefulRenames.h"
#else
    #include "../utils/UsefulRenames.h"
#endif

#include "SMRandomData.hpp"

using namespace geode::prelude;
using namespace std;

class SMMenu : Layer {
public:
    static SMMenu* create();
    SMMenu();
    CCLayer* getLayer();
    void openMenu();
    void closeMenu();
    void toggleMenu();
private:
    Size screenSize;
    void onExitButton(Object* sender);
};

// button functions! yay!

void SMMenu::onExitButton(Object* sender) {
    closeMenu();
}

// no more button functions >:(

SMMenu* SMMenu::create() {
    return new SMMenu();
}

void SMMenu::openMenu(){
    auto moveToAction = MoveTo::create(1, Vec2(0, 0));
	auto moveTo_eased = EaseElasticOut::create(moveToAction);
	SMRandomData::meAsLayer->setPosition(Vec2(0, screenSize.height));
	SMRandomData::meAsLayer->runAction(moveTo_eased);
	SMRandomData::meAsLayer->setVisible(true);
	SMRandomData::meAsLayer->setTouchPriority(-1000);
}

void SMMenu::toggleMenu(){
    SMRandomData::isOpen = !(SMRandomData::isOpen);
	//cout << "TP = -1000" << endl;
    //SMRandomData::smPanelLayer->setTouchPriority(-1000);
	if(SMRandomData::isOpen){
        openMenu();
    } else {
        closeMenu();
    }
}

void SMMenu::closeMenu(){
    SMRandomData::meAsLayer->removeFromParent();
	SMRandomData::meAsLayer = nullptr;
	SMRandomData::isOpen = true;
    //SMRandomData::meAsLayer->setVisible(false);
    //SMRandomData::smPanelLayer->setTouchPriority(0);
	//cout << "TP = 0" << endl;
}

CCLayer* SMMenu::getLayer(){
    return SMRandomData::meAsLayer;
}

SMMenu::SMMenu(){
    screenSize = CCDirector::sharedDirector()->getWinSize();

    Color4B fadeColor = {0, 0, 0, 105};
    auto fadeBgLayer = LayerColor::create(fadeColor);
    auto layer = Layer::create();
    auto infoLayer = Layer::create();
    infoLayer->setID("sm-info-layer");
    layer->setID("spacemenu-panel");
    fadeBgLayer->setID("spacemenu-ui");

    auto touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    layer->setTouchEnabled(true);
    layer->setTouchMode(kCCTouchesOneByOne);
    layer->setMouseEnabled(true);
    layer->setKeypadEnabled(true);
  	touchDispatcher->setForcePrio(touchDispatcher->getForcePrio() - 2);

    Vec2 panelSize = screenSize - Vec2(50, 50);

    auto SM_Logo = Sprite::create("SM_FullLogo.png"_spr);
    SM_Logo->setAnchorPoint(Vec2(1.0f, 1.0f));
    SM_Logo->setScale(0.67f);
    SM_Logo->setPosition(panelSize - Vec2(11, 11));
    SM_Logo->setID("sm-logo-full");

    auto creatorText = CCLabelBMFont::create("by Bigmancozmo", "goldFont.fnt");
    creatorText->setID("sm-creator-label");
    creatorText->setPosition(panelSize - Vec2(76, 56));
    creatorText->setScale(0.525f);

    auto text = CCLabelBMFont::create("Hello, World!", "bigFont.fnt");
    text->setPosition(panelSize / 2);

    auto background = CCScale9Sprite::create("GJ_square02.png");
    background->setContentSize(panelSize);
    background->setID("sm-background");

    layer->setZOrder(100);
    fadeBgLayer->setZOrder(90);

    // close button
    auto exitButtonSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    auto exitButton = CCMenuItemSpriteExtra::create(
        exitButtonSprite,
        background,
        menu_selector(SMMenu::onExitButton)
    );

    // menu
    auto menu = Menu::create();
    menu->setAnchorPoint(Vec2(0.0f, 1.0f));
    menu->setPositionY(panelSize.y);
	menu->setPositionX(0);
    menu->setID("spacemenu-ui-ccmenu");

    // add children
    layer->addChild(background);
    background->addChild(text);
    infoLayer->addChild(SM_Logo);
    infoLayer->addChild(creatorText);
    background->addChild(infoLayer);
    fadeBgLayer->addChild(layer);
    background->addChild(menu);
    menu->addChild(exitButton);

    layer->setTouchPriority(-1000);
    menu->setTouchPriority(-1100);

    // fix positioning
    layer->setPosition(layer->getPosition() + (screenSize / 2));
    fadeBgLayer->setPosition(fadeBgLayer->getPosition() - (screenSize / 2));

	fadeBgLayer->setZOrder(500);

    SMRandomData::meAsLayer = fadeBgLayer;
	SMRandomData::smPanelLayer = layer;
}