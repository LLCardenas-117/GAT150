#include "Enemy.h"

#include "../GamePCH.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"

FACTORY_REGISTER(Enemy)

void Enemy::Start() {
    OBSERVER_ADD(player_dead);

    _rigidBody = owner->GetComponent<errera::RigidBody>();
    fireTimer = fireTime;
}

void Enemy::Update(float dt){
    // Particals to the engine
    errera::Particle particle;

    particle.position = owner->transform.position + errera::vec2{ -50, 0 }.Rotate(errera::math::degToRad(owner->transform.rotation));
    particle.velocity = errera::vec2{ errera::random::getReal(-80.0f, -30.0f), 0 }.Rotate(errera::math::degToRad(owner->transform.rotation + errera::random::getReal(-90.0f, 90.0f)));
    particle.color = errera::vec3{ 1.0f, 1.0f, 1.0f };
    particle.lifespan = 0.5f;
    errera::GetEngine().GetParticleSystem().AddParticle(particle);

    bool playerSeen = false;

    errera::Actor* player = owner->scene->GetActorByName<errera::Actor>("player");
    if (player) {
        errera::vec2 direction{ 1, 0 };
        direction = player->transform.position - owner->transform.position;
        direction = direction.Normalized();

        errera::vec2 forward = errera::vec2{ 1,0 }.Rotate(errera::math::degToRad(owner->transform.rotation));
        float angle = errera::math::radToDeg(errera::vec2::AngleBetween(forward, direction));

        playerSeen = angle <= 30;

        if (playerSeen) {
            float angle = errera::vec2::SignedAngleBetween(forward, direction);
            angle = errera::math::sign(angle);
            owner->transform.rotation += errera::math::radToDeg(angle * 5 * dt);
        }
        
    }

    errera::vec2 force = errera::vec2{ 1, 0 }.Rotate(errera::math::degToRad(owner->transform.rotation)) * speed;

    if (_rigidBody) {
        _rigidBody->velocity += force * dt;
    }

    owner->transform.position.x = errera::math::wrap(owner->transform.position.x, 0.0f, (float)errera::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = errera::math::wrap(owner->transform.position.y, 0.0f, (float)errera::GetEngine().GetRenderer().GetHeight());

    
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;
        errera::Transform transform{ owner->transform.position, owner->transform.rotation, 0.75 };

        auto rocket = errera::Instantiate("enemy-rocket", transform);
        owner->scene->AddActor(std::move(rocket));

        
    }
}

void Enemy::OnCollision(errera::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;
        EVENT_NOTIFY_DATA(add_points, 100);

        for (int i = 0; i < 100; i++) {
            errera::Particle particle;
            particle.position = owner->transform.position;
			particle.velocity = errera::random::onUnitCircle() * errera::random::getReal(10.0f, 200.0f);
            particle.color = errera::vec3{ 1, 1, 1 };
            particle.lifespan = 2;
            errera::GetEngine().GetParticleSystem().AddParticle(particle);
        }

        auto sound = errera::Resources().Get<errera::AudioClip>("audio/explosion.wav", errera::GetEngine().GetAudio()).get();
        if (sound) {
            errera::GetEngine().GetAudio().PlaySound(*sound);
        }
    }
}

void Enemy::OnNotify(const errera::Event& event) {
    if (errera::equalsIqnoreCase(event.id, "player_dead")) {
        owner->destroyed = true;
    }
}

void Enemy::Read(const errera::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, fireTime);
    JSON_READ(value, fireTimer);
}