#include <game/player_character.h>
#include <game/game_manager.h>

namespace game
{
    PlayerCharacterManager::PlayerCharacterManager(core::EntityManager& entityManager, PhysicsManager& physicsManager, GameManager& gameManager) :
        ComponentManager(entityManager),
        physicsManager_(physicsManager),
        gameManager_(gameManager)

    {

    }

    void PlayerCharacterManager::FixedUpdate(sf::Time dt)
    {
        for (core::Entity playerEntity = 0; playerEntity < entityManager_.GetEntitiesSize(); playerEntity++)
        {
            if (!entityManager_.HasComponent(playerEntity,
                static_cast<core::EntityMask>(ComponentType::PLAYER_CHARACTER)))
                continue;
            auto playerBody = physicsManager_.GetBody(playerEntity);
            auto playerCharacter = GetComponent(playerEntity);
            const auto input = playerCharacter.input;

            const bool right = input & PlayerInputEnum::PlayerInput::RIGHT;
            const bool left = input & PlayerInputEnum::PlayerInput::LEFT;
            const bool jump = input & PlayerInputEnum::PlayerInput::JUMP;

            auto dir = core::Vec2f::up();
            auto dir_r = core::Vec2f::right();

            const auto acceleration =  (jump ? 0.1f : 0.0f) * dir;
            const auto acceleration_r = ((right ? 0.0f : -2.5f) + (left ? 0.0f : 2.5f)) * dir_r;
            playerBody.velocity += acceleration + acceleration_r * dt.asSeconds();

            physicsManager_.SetBody(playerEntity, playerBody);
            SetComponent(playerEntity, playerCharacter);
        }
    }
}
