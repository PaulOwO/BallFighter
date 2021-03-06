#include <game/physics_manager.h>
#include <fmt/format.h>
#include <utils/log.h>
#include <cmath>
#include <game/game_manager.h>
#include <game/player_character.h>



namespace game
{

    PhysicsManager::PhysicsManager(core::EntityManager& entityManager) :
        bodyManager_(entityManager), entityManager_(entityManager)
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
            core::Vec2f max_pos = { (areaSize.x / core::pixelPerMeter /2), (areaSize.y / core::pixelPerMeter / 2)};
            core::Vec2f min_pos = { -(areaSize.x / core::pixelPerMeter / 2), -(areaSize.y / core::pixelPerMeter / 2)};

            body.velocity += G * dt.asSeconds();
            body.position += body.velocity * dt.asSeconds();

            if (body.position.x <= min_pos.x + core::radius)
            {
                body.position.x = min_pos.x + core::radius;
                body.velocity.x = -body.velocity.x * 2;
            }
            if (body.position.y <= min_pos.y + core::radius)            //correct position and velocity
            {
                body.position.y = min_pos.y + core::radius;
                body.velocity.y = - body.velocity.y /2;
            }
            if (body.position.x >= max_pos.x - core::radius)
            {
                body.position.x = max_pos.x - core::radius;
                body.velocity.x = -body.velocity.x * 2;
            }
            if (body.position.y >= max_pos.y - core::radius)
            {
                body.position.y = max_pos.y - core::radius;
                body.velocity.y = core::roofPush;
            }
            bodyManager_.SetComponent(entity, body);

           // if (entity == 0)
           //core::LogWarning(fmt::format("player{} position x :{} y :{}, ",entity,body.position.x, body.position.y));   //stdcout position

            auto body1 = bodyManager_.GetComponent(0);
            auto body2 = bodyManager_.GetComponent(1);

            if (BodyIntersect(body1, body2))
            {
                //core::LogWarning(fmt::format("Contact!"));
                ResolveBodyIntersect(body1, body2);
                bodyManager_.SetComponent(0, body1);
                bodyManager_.SetComponent(1, body2);
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

    void PhysicsManager::RegisterTriggerListener(OnTriggerInterface& collisionInterface)
    {
        onTriggerAction_.RegisterCallback(
            [&collisionInterface](core::Entity entity1, core::Entity entity2) { collisionInterface.OnTrigger(entity1, entity2); });
    }

    void PhysicsManager::CopyAllComponents(const PhysicsManager& physicsManager)
    {
        bodyManager_.CopyAllComponents(physicsManager.bodyManager_.GetAllComponents());
    }

    bool PhysicsManager::BodyIntersect(Body body1, Body body2)
    {
        return Body::CalculateDistance(body1, body2) < (core::radius + core::radius );
    }

    void PhysicsManager::ResolveBodyIntersect(Body& body1, Body& body2)
    {
        float v1n = ComputeNormal(body1.position, ContactPoint(body1, body2)).x * body1.velocity.x +
            ComputeNormal(body1.position, ContactPoint(body1, body2)).y * body1.velocity.y;
        float v1t = ComputeTangent(body1.position, ContactPoint(body1, body2)).x * body1.velocity.x +
            ComputeTangent(body1.position, ContactPoint(body1, body2)).y * body1.velocity.y;
        float v2n = ComputeNormal(body2.position, ContactPoint(body1, body2)).x * body2.velocity.x +
            ComputeNormal(body2.position, ContactPoint(body1, body2)).y * body2.velocity.y;
        float v2t = ComputeTangent(body2.position, ContactPoint(body1, body2)).x * body2.velocity.x +
            ComputeTangent(body2.position, ContactPoint(body1, body2)).y * body2.velocity.y;

        body1.velocity.x = ComputeNormal(body1.position, ContactPoint(body1, body2)).x * v2n + ComputeTangent(
            body1.position, ContactPoint(body1, body2)).x * v1t * -core::forceRestitution;
        body1.velocity.y = ComputeNormal(body1.position, ContactPoint(body1, body2)).y * v2n + ComputeTangent(
            body1.position, ContactPoint(body1, body2)).y * v1t * -core::forceRestitution;
        body2.velocity.x = ComputeNormal(body2.position, ContactPoint(body1, body2)).x * v1n + ComputeTangent(
            body2.position, ContactPoint(body1, body2)).x * v2t * -core::forceRestitution;
        body2.velocity.y = ComputeNormal(body2.position, ContactPoint(body1, body2)).y * v1n + ComputeTangent(
            body2.position, ContactPoint(body1, body2)).y * v2t * -core::forceRestitution;

			if (body2.position.y >= body1.position.y + 1.5 * core::radius)
			{
				core::LogWarning(fmt::format("p1 death!"));
                body1.looser = true;
			}
            if (body1.position.y >= body2.position.y + 1.5 * core::radius)
            {
                core::LogWarning(fmt::format("p2 death!"));
                body2.looser = true;
            }

        body1.position = RelocateCenter(body1, ContactPoint(body1, body2));
        body2.position = RelocateCenter(body2, ContactPoint(body1, body2));
        body1.velocity = body1.velocity * -core::forceRestitution;
        body2.velocity = body2.velocity * -core::forceRestitution;
    }

    core::Vec2f PhysicsManager::ContactPoint(const Body& body1, const Body& body2) const
    {
        double ratio = (core::radius) / ((core::radius) + (core::radius));
        return (body2.position - body1.position) * ratio + body1.position;
    }

     core::Vec2f PhysicsManager::RelocateCenter(const Body& body, const core::Vec2f& v)
    {
        double ratio = (core::radius) / (body.position - v).Length();
        return (body.position - v) * ratio + v;
    }


    float Body::CalculateDistance(Body body1, Body body2)
    {
        const float dx = body2.position.x - body1.position.x;
        const float dy = body2.position.y - body1.position.y;
        return std::sqrt(dx * dx + dy * dy);
    }
}
