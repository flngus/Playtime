#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace util {
    void updateTime(std::string const& save, std::chrono::steady_clock::time_point initPoint);
}