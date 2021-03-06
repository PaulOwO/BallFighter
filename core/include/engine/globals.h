#pragma once

#include <SFML/System/Vector2.hpp>

namespace core
{
    const sf::Vector2u windowSize = { 1000, 1000 };
    constexpr std::size_t entityInitNmb = 128;
    constexpr float pixelPerMeter = 100.0f;
    constexpr float radius = 0.33f;
    constexpr float forceRestitution = 0.9f;
    constexpr float roofPush = -10;
} // namespace core
