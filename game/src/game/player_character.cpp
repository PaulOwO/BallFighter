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
            auto playerBody = physicsManager_.GetBody(playerEntity); //TODO
            auto playerCharacter = GetComponent(playerEntity);
            const auto input = playerCharacter.input;

            const bool right = input & PlayerInputEnum::PlayerInput::RIGHT;
            const bool left = input & PlayerInputEnum::PlayerInput::LEFT;
            const bool jump = input & PlayerInputEnum::PlayerInput::JUMP;
             

            constexpr  auto dir = core::Vec2f::up();
            constexpr  auto dir_r = core::Vec2f::right();

            if (jump && playerBody.position.y <= 0) 
            {
                playerBody.velocity = { playerBody.velocity.x ,0 };
                playerBody.velocity.y += 10.0f;

            }
            const auto acceleration= ((right ? 0.0f : -3.5f) + (left ? 0.0f : 3.5f)) * dir_r;
            playerBody.velocity += acceleration * dt.asSeconds(); 
            if (playerBody.velocity.x <= -maxPlayerSpeed)
            {
                playerBody.velocity.x = -maxPlayerSpeed;
            }
            if (playerBody.velocity.x >= maxPlayerSpeed)
            {
                playerBody.velocity.x = maxPlayerSpeed;
            }

            physicsManager_.SetBody(playerEntity, playerBody);
            ComponentManager::SetComponent(playerEntity, playerCharacter);
        }
    }
}
