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


            physicsManager_.SetBody(playerEntity, playerBody);
            SetComponent(playerEntity, playerCharacter);
        }
    }
}
