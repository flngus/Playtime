#include "util.h"

namespace util {
    void updateTime(const std::string& save, std::chrono::steady_clock::time_point initPoint) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - initPoint).count();
        Mod::get()->setSavedValue(save, Mod::get()->getSavedValue<float>(save) + elapsed);
        log::debug("updateTime called for {}", save);
    }
}