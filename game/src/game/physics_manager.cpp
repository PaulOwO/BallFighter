#include <game/physics_manager.h>
#include <fmt/format.h>
#include <utils/log.h>



namespace game
{

    PhysicsManager::PhysicsManager(core::EntityManager& entityManager) :
        bodyManager_(entityManager), boxManager_(entityManager), entityManager_(entityManager)
    {

    }

    bool Box2Box(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h)
    {
        return r1x + r1w >= r2x &&    // r1 right edge past r2 left
            r1x <= r2x + r2w &&    // r1 left edge past r2 right
            r1y + r1h >= r2y &&    // r1 top edge past r2 bottom
            r1y <= r2y + r2h;
    }

    void PhysicsManager::FixedUpdate(sf::Time dt)
    {
        for (core::Entity entity = 0; entity < entityManager_.GetEntitiesSize(); entity++)
        {
            if (!entityManager_.HasComponent(entity, static_cast<core::EntityMask>(core::ComponentType::BODY2D)))
                continue;
            auto body = bodyManager_.GetComponent(entity);
            core::Vec2f G = { 0, -9.81 };
            core::Vec2f max_pos = { (core::windowSize.x / core::pixelPerMeter /2), (core::windowSize.y / core::pixelPerMeter / 2)};
            //core::Vec2f min_pos = core::Vec2f::zero();
            core::Vec2f min_pos = { -(core::windowSize.x / core::pixelPerMeter / 2), -(core::windowSize.y / core::pixelPerMeter / 2)};

            body.velocity += G * dt.asSeconds();
            body.position += body.velocity * dt.asSeconds();

            if (body.position.x <= min_pos.x)
            {
                body.position.x = min_pos.x;
                body.velocity.x = 15;
            }
            if (body.position.y <= min_pos.y)            //correct position and velocity
            {
                body.position.y = min_pos.y;
                body.velocity.y = - body.velocity.y /2;
            }
            if (body.position.x >= max_pos.x)
            {
                body.position.x = max_pos.x;
                body.velocity.x = -15;
            }
            if (body.position.y >= max_pos.y)
            {
                body.position.y = max_pos.y;
                body.velocity.y = -10;
            }
                

            if (entity == 1)
           core::LogWarning(fmt::format("player{} position x :{} y :{}, ",entity,body.position.x, body.position.y));   //stdcout position

            bodyManager_.SetComponent(entity, body);
        }
        for (core::Entity entity = 0; entity < entityManager_.GetEntitiesSize(); entity++)
        {
            if (!entityManager_.HasComponent(entity,
                                                   static_cast<core::EntityMask>(core::ComponentType::BODY2D) |
                                                   static_cast<core::EntityMask>(core::ComponentType::BOX_COLLIDER2D)) ||
                entityManager_.HasComponent(entity, static_cast<core::EntityMask>(ComponentType::DESTROYED)))
                continue;
            for (core::Entity otherEntity = entity; otherEntity < entityManager_.GetEntitiesSize(); otherEntity++)
            {
                if (entity == otherEntity)
                    continue;
                if (!entityManager_.HasComponent(otherEntity,
                                                 static_cast<core::EntityMask>(core::ComponentType::BODY2D) | static_cast<core::EntityMask>(core::ComponentType::BOX_COLLIDER2D)) ||
                    entityManager_.HasComponent(entity, static_cast<core::EntityMask>(ComponentType::DESTROYED)))
                    continue;
                const Body& body1 = bodyManager_.GetComponent(entity);
                const Box& box1 = boxManager_.GetComponent(entity);

                const Body& body2 = bodyManager_.GetComponent(otherEntity);
                const Box& box2 = boxManager_.GetComponent(otherEntity);

               /* if (Box2Box(
                    body1.position.x - box1.extends.x,
                    body1.position.y - box1.extends.y,
                    box1.extends.x * 2.0f,
                    box1.extends.y * 2.0f,
                    body2.position.x - box2.extends.x,
                    body2.position.y - box2.extends.y,
                    box2.extends.x * 2.0f,
                    box2.extends.y * 2.0f))
                {
                    onTriggerAction_.Execute(entity, otherEntity);
                }*/

            }
        }
    }

    void PhysicsManager::SetBody(core::Entity entity, const Body& body)
    {
        bodyManager_.SetComponent(entity, body);
    }

    const Body& PhysicsManager::GetBody(core::Entity entity) const
    {
        return bodyManager_.GetComponent(entity);
    }

    void PhysicsManager::AddBody(core::Entity entity)
    {
        bodyManager_.AddComponent(entity);
    }

    void PhysicsManager::AddBox(core::Entity entity)
    {
        boxManager_.AddComponent(entity);
    }

    void PhysicsManager::SetBox(core::Entity entity, const Box& box)
    {
        boxManager_.SetComponent(entity, box);
    }

    const Box& PhysicsManager::GetBox(core::Entity entity) const
    {
        return boxManager_.GetComponent(entity);
    }

    void PhysicsManager::RegisterTriggerListener(OnTriggerInterface& collisionInterface)
    {
        onTriggerAction_.RegisterCallback(
            [&collisionInterface](core::Entity entity1, core::Entity entity2) { collisionInterface.OnTrigger(entity1, entity2); });
    }

    void PhysicsManager::CopyAllComponents(const PhysicsManager& physicsManager)
    {
        bodyManager_.CopyAllComponents(physicsManager.bodyManager_.GetAllComponents());
        boxManager_.CopyAllComponents(physicsManager.boxManager_.GetAllComponents());
    }
}
