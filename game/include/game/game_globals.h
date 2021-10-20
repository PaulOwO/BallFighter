#pragma once
#include <SFML/Graphics/Color.hpp>
#include <array>

#include "engine/component.h"
#include "engine/entity.h"
#include "maths/angle.h"
#include "maths/vec2.h"


namespace game
{
    using PlayerNumber = std::uint8_t;
    const PlayerNumber INVALID_PLAYER = std::numeric_limits<PlayerNumber>::max();
    using ClientId = std::uint16_t;
    using Frame = std::uint32_t;

    const std::uint32_t maxPlayerNmb = 2;
    const short playerHealth = 5;
    const float playerSpeed = 1.0f;

    const std::array<sf::Color, std::max(maxPlayerNmb, 4u)> playerColors =
    {
      {
            sf::Color::Red,
            sf::Color::Blue,
            sf::Color::Yellow,
            sf::Color::Cyan
        }
    };

    constexpr std::array<core::Vec2f, std::max(4u, maxPlayerNmb)> spawnPositions
    {
            core::Vec2f(0,1),
            core::Vec2f(0,-1),
            core::Vec2f(1,0),
            core::Vec2f(-1,0),
    };

    enum class ComponentType : core::EntityMask
    {
        PLAYER_CHARACTER = static_cast<core::EntityMask>(core::ComponentType::OTHER_TYPE),
        PLAYER_INPUT = static_cast<core::EntityMask>(core::ComponentType::OTHER_TYPE) << 3u,
        DESTROYED = static_cast<core::EntityMask>(core::ComponentType::OTHER_TYPE) << 4u,
    };

    using PlayerInput = std::uint8_t;

    namespace PlayerInputEnum
    {
        enum PlayerInput : std::uint8_t
        {
            NONE = 0u,
            LEFT = 1u << 2u,
            RIGHT = 1u << 3u,
            JUMP = 1u << 4u,
        };
    }
}
