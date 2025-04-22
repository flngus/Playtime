#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/EndLevelLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayerHook, PlayLayer) {
    struct Fields {
        std::chrono::steady_clock::time_point levelOpened;
    };
    
    void setupHasCompleted() {
        m_fields->levelOpened = std::chrono::steady_clock::now();

        PlayLayer::setupHasCompleted();
    }

    void updateTime() {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime- m_fields->levelOpened).count();
        Mod::get()->setSavedValue("in-game-playtime", Mod::get()->getSavedValue<float>("in-game-playtime") + elapsed);
        log::debug("updateTime called");
    }

    void onQuit() {
        log::debug("PlayLayer::onQuit");
        PlayLayerHook::updateTime();
        PlayLayer::onQuit();
    }
};

class $modify(PauseLayer) {
    void onEdit(CCObject* sender) {
        static_cast<PlayLayerHook*>(PlayLayer::get())->updateTime();

        log::debug("PauseLayer::onEdit");
        PauseLayer::onEdit(sender);
    }
};

class $modify(EndLevelLayer) {
    void onEdit(CCObject* sender) {
        static_cast<PlayLayerHook*>(PlayLayer::get())->updateTime();

        log::debug("EndLevelLayer::onEdit");
        EndLevelLayer::onEdit(sender);
    }
};