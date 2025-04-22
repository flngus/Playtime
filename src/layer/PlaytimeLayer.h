#pragma once

#include <Geode/ui/Popup.hpp>
using namespace geode::prelude;

class PlaytimeLayer : public geode::Popup<std::string const&> {
protected:
    CCLabelBMFont* playtimeTitle;
    std::string formattedTime(float time);
    bool setup(std::string const& value) override;
    void onInfo(CCObject* sender);     // Handles info button logic
public:
    static PlaytimeLayer* create(std::string const& text);
};