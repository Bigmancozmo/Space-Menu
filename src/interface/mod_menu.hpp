#pragma once

#include <Geode/Geode.hpp>
#include <iostream>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "../hacks/includeHacks.h"

using namespace geode::prelude;
using namespace std;
using namespace keybinds;

class SpaceMenu : public CCLayer {
public:
    virtual bool init();
    static SpaceMenu* create();
    void show();
    void hide(CCObject*);
    bool visible = false;
private:
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCScale9Sprite* background;
    void showNoAnim();
    void openAnim();
    void onCloseButton(CCObject*);
    SpaceMenu* meImCool;
    CCLayerColor* backgroundFade;
    template<typename T>
    void loadMod(CCMenu* menu);
    void onModToggle(CCObject* sender);
};

bool SpaceMenu::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    CCPoint panelSize = screenSize - CCPoint(50, 50);

    ccColor4B fadeColor = ccColor4B(0.0f, 0.0f, 0.0f, 150.0f);
    backgroundFade = CCLayerColor::create(fadeColor);
    CCMenu* menu = CCMenu::create();

    backgroundFade->setOpacity(0);

    background = CCScale9Sprite::create("GJ_square02.png");
    background->setContentSize(panelSize);
    background->setID("sm-background");

    auto bgMenu = CCMenu::create();
    background->addChild(bgMenu);

    auto hacksMenu = CCMenu::create();
    background->addChild(hacksMenu);

    CCSprite* closeBtnSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    CCMenuItemSpriteExtra* closeBtn = CCMenuItemSpriteExtra::create(
        closeBtnSprite, bgMenu, menu_selector(SpaceMenu::onCloseButton)
    );
    closeBtn->setAnchorPoint(CCPoint(0.5f, 0.5f));
    closeBtn->setPositionX(-(panelSize.x / 2) - 20.6f);
    closeBtn->setPositionY((panelSize.y / 3.17f) + 19.0f);

    auto creatorInfoContainer = CCLayer::create();
    creatorInfoContainer->setAnchorPoint(CCPoint(1.0f, 1.0f));
    creatorInfoContainer->setPosition(panelSize - CCPoint(7.0f, 7.0f));
    creatorInfoContainer->setContentSize(CCSize(0.0f, 0.0f));
    creatorInfoContainer->setScale(0.525);

    auto fullLogoSprite = CCSprite::createWithSpriteFrameName("SM_FullLogo.png"_spr);
    fullLogoSprite->setAnchorPoint(CCPoint(1.0f, 1.0f));

    auto creatorLabel = CCLabelBMFont::create("made by bigmancozmo", "Montserrat-Medium.fnt"_spr);
    auto creatorLabelY = fullLogoSprite->getPositionY() - fullLogoSprite->getContentHeight() * fullLogoSprite->getScaleY();
    creatorLabel->setPositionY(creatorLabelY + 8.0f);
    creatorLabel->setPositionX(fullLogoSprite->getPositionX() - 8.0f);
    creatorLabel->setAnchorPoint(CCPoint(1.0f, 1.0f));

    this->showNoAnim();

    // add children
    this->addChild(backgroundFade);
    menu->setPosition(CCPoint(0.0f, 0.0f));
    this->addChild(menu);
    menu->setZOrder(500);
    menu->addChild(background);
    menu->setPosition(screenSize / 2);
    background->setPosition(CCPoint(0, screenSize.height));
    bgMenu->addChild(closeBtn);
    //bgMenu->addChild(toggler);
    creatorInfoContainer->addChild(creatorLabel);
    creatorInfoContainer->addChild(fullLogoSprite);
    background->addChild(creatorInfoContainer);

    loadMod<Noclip>(hacksMenu);

    auto touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    this->setTouchEnabled(true);
    this->setVisible(true);
    this->setTouchMode(kCCTouchesOneByOne);
    this->setMouseEnabled(true);
    this->setKeypadEnabled(true);
    touchDispatcher->setForcePrio(touchDispatcher->getForcePrio() - 25);

    this->setTouchPriority(-200);
    menu->setTouchPriority(-300);
    bgMenu->setTouchPriority(-999);
    hacksMenu->setTouchPriority(-998);

    meImCool = this;

    // keybinds
#ifdef GEODE_IS_WINDOWS
    this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
        bool oldVisibility = visible;
        if (event->isDown()) {
            this->hide(nullptr);
        }
        
        if (oldVisibility) {
            return ListenerResult::Stop;
        }
        return ListenerResult::Propagate;

    }, "close-spacemenu"_spr);
#endif

    this->openAnim();

    return true;
}

SpaceMenu* SpaceMenu::create() {
    SpaceMenu* me = new SpaceMenu();
    me->init();
    return me;
}

void SpaceMenu::openAnim()
{
    background->setPosition(CCPoint(0, screenSize.height));
    auto moveToAction = CCMoveTo::create(1, CCPoint(0, 0));
    auto eased = CCEaseElasticOut::create(moveToAction);
    background->runAction(eased);

    auto fade = CCFadeTo::create(0.1, 150);
    backgroundFade->runAction(fade);
}

void SpaceMenu::onCloseButton(CCObject*)
{
    InvokeBindEvent("close-spacemenu"_spr, true).post();
}

void SpaceMenu::onModToggle(CCObject* sender)
{
    auto hackKey = static_cast<CCMenuItemToggle*>(sender)->getID();
    Hacks::setModEnabled(hackKey, !(Hacks::getModEnabled(hackKey)));
}

template<typename T>
void SpaceMenu::loadMod(CCMenu* menu)
{
    CCLayer* hackLayer = CCLayer::create();
    CCMenu* layerMenu = CCMenu::create();

    layerMenu->setTouchPriority(-997);
    
    auto toggler = CCMenuItemToggler::createWithStandardSprites(layerMenu, menu_selector(SpaceMenu::onModToggle), 1.0f);
    toggler->setAnchorPoint(CCPoint(0.5f, 0.5f));
    
    toggler->setID(T::hackKey);

    auto label = CCLabelBMFont::create((T::name).c_str(), "bigFont.fnt");

    T::loadValue();

    hackLayer->addChild(layerMenu);
    layerMenu->setPosition(CCPoint(0.0f, 0.0f));
    layerMenu->addChild(toggler);

    if (Hacks::getModEnabled(T::hackKey)) {
        SpaceMenu::onModToggle(static_cast<CCObject*>(toggler)); // fake a button press
        toggler->activate();
    }

    layerMenu->addChild(label);
    label->setScale(0.6f);
    label->setAnchorPoint(CCPoint(0.0f, 0.5f));
    label->setPositionX((toggler->getContentWidth() / 2) + 5.5f);

    hackLayer->setContentSize(toggler->getContentSize());

    menu->addChild(hackLayer);
}

void SpaceMenu::show()
{
    visible = true;
    auto touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    this->setTouchEnabled(true);
    this->setVisible(true);
    this->setTouchMode(kCCTouchesOneByOne);
    this->setMouseEnabled(true);
    this->setKeypadEnabled(true);
    touchDispatcher->setForcePrio(touchDispatcher->getForcePrio() - 25);

    this->openAnim();
}

void SpaceMenu::showNoAnim()
{
    visible = true;
    auto touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    this->setTouchEnabled(true);
    this->setVisible(true);
    this->setTouchMode(kCCTouchesOneByOne);
    this->setMouseEnabled(true);
    this->setKeypadEnabled(true);
    touchDispatcher->setForcePrio(touchDispatcher->getForcePrio() - 25);
}

void SpaceMenu::hide(CCObject*)
{
    visible = false;
    this->setVisible(false);
    this->setTouchEnabled(false);
    this->setMouseEnabled(false);
    this->setKeypadEnabled(false);
    background->setPosition(CCPoint(0, screenSize.height));
    backgroundFade->setOpacity(0);
}