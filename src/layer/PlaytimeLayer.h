#pragma once

#include <Geode/ui/Popup.hpp>
using namespace geode::prelude;

class PlaytimeLayer : public geode::Popup<> {
protected:
    CCLabelBMFont* playtimeTitle;
    std::string formattedTime(float time);
    bool setup() override;
    void onInfo(CCObject* sender);     // Handles info button logic
public:
    static PlaytimeLayer* create();
};