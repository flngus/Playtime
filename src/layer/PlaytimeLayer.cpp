/* TODO:
- add editor and total times
- cleanup code
- fix some bugs
- yeah
*/

#include "PlaytimeLayer.h"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

bool PlaytimeLayer::setup(std::string const&) {
    this->setTitle("Playtime");

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto bg = CCScale9Sprite::create("square02b_001.png");
    bg->setContentSize({280.f, 54.f});
    bg->setColor(ccColor3B(0, 0, 0));
    bg->setOpacity(75);
    m_mainLayer->addChildAtPosition(bg, Anchor::Top, {0, -93});

    playtimeTitle = CCLabelBMFont::create("Total In-Game Time", "bigFont.fnt");
    playtimeTitle->setScale(0.8);
    auto textArea = TextArea::create(PlaytimeLayer::formattedTime(Mod::get()->getSavedValue<double>("in-game-playtime")), "chatFont.fnt", 1, 200.f, {0.5, 0.5}, 20.f, false);
    m_mainLayer->addChildAtPosition(playtimeTitle, Anchor::Top, {0, -48});
    m_mainLayer->addChildAtPosition(textArea, Anchor::Top, {0, -93});

    auto infoIconBtnSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    
    auto infoIconBtn = CCMenuItemSpriteExtra::create(
        infoIconBtnSpr, this, menu_selector(PlaytimeLayer::onInfo)
    );
    m_buttonMenu->addChildAtPosition(infoIconBtn, Anchor::TopRight, {-20, -20});

    auto okSpr = ButtonSprite::create("OK", "goldFont.fnt", "GJ_button_01.png", 0.8f);
    auto okBtn = CCMenuItemSpriteExtra::create(
        okSpr, this, menu_selector(PlaytimeLayer::onClose)
    );
    m_buttonMenu->addChildAtPosition(okBtn, Anchor::Bottom, {0, 25});

    return true;
}

std::string PlaytimeLayer::formattedTime(float time) {
    std::string ret = "";
    int hour = static_cast<int>(time / 3600);
    time = std::fmod(time, 3600);
    int minutes = static_cast<int>(time / 60);
    time = std::fmod(time, 60);
    int sec = static_cast<int>(time);
    int ms = static_cast<int>((time - sec) * 100);

    if(time <= 0) {
        ret = "Start <cg>playing</c> to count your <cy>playtime</c>!";
    }
    else {
        if (hour > 0)
            ret = fmt::format("<cr>{:02}</c>:<cy>{:02}</c>:<cg>{:02}</c>.<cl>{:02}</c>", hour, minutes, sec, ms);
        else if (minutes > 0)
            ret = fmt::format("<cy>{:02}</c>:<cg>{:02}</c>.<cl>{:02}</c>", minutes, sec, ms);
        else
            ret = fmt::format("<cg>{}</c>.<cl>{:03}</c>s", sec, static_cast<int>((time - sec) * 1000));
    }

    return ret;
}

void PlaytimeLayer::onInfo(CCObject* sender) {
    FLAlertLayer::create("Playtime", "Displays your <cy>playtime</c> for the <cg>game</c>.\nYour <cy>playtime</c> is split up between <cg>total time</c>, <cl>in-game time</c> and <co>editor time</c>.", "OK")->show();
}

PlaytimeLayer* PlaytimeLayer::create(std::string const& text) {
    auto ret = new PlaytimeLayer();
    if (ret && ret->initAnchored(350.f, 169.f, text, "GJ_square01.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
