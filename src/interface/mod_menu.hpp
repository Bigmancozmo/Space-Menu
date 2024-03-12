#pragma once

#include <Geode/Geode.hpp>
#include <iostream>
#include <geode.custom-keybinds/include/Keybinds.hpp>

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
};

bool SpaceMenu::init() {
    if (!CCLayer::init()) {
        cout << "life is sad, spacemenu didnt init" << endl;
        return false;
    }
    
    CCPoint panelSize = screenSize - CCPoint(50, 50);

    ccColor4B fadeColor = ccColor4B(0.0f, 0.0f, 0.0f, 150.0f);
    CCLayerColor* backgroundFade = CCLayerColor::create(fadeColor);
    CCMenu* menu = CCMenu::create();

    background = CCScale9Sprite::create("GJ_square02.png");
    background->setContentSize(panelSize);
    background->setID("sm-background");

    auto bgMenu = CCMenu::create();
    background->addChild(bgMenu);

    CCSprite* closeBtnSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    CCMenuItemSpriteExtra* closeBtn = CCMenuItemSpriteExtra::create(
        closeBtnSprite, bgMenu, menu_selector(SpaceMenu::onCloseButton)
    );

    // former mess :)
    // (look in commit history for context)
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


    // more mess
    this->setTouchPriority(-200);
    menu->setTouchPriority(-300);
    bgMenu->setTouchPriority(-299);

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
}

void SpaceMenu::onCloseButton(CCObject*)
{
    /*visible = false;
    meImCool->setVisible(false);
    meImCool->setTouchEnabled(false);
    meImCool->setMouseEnabled(false);
    meImCool->setKeypadEnabled(false);
    */
    InvokeBindEvent("close-spacemenu"_spr, true).post();
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
}