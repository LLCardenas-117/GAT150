#include "Enemy.h"

#include "Player.h"
#include "Rocket.h"
#include "GameData.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt){

    // Particals to the engine
    errera::Particle particle;

    particle.position = transform.position + errera::vec2{ -50, 0 }.Rotate(errera::math::degToRad(transform.rotation));
    particle.velocity = errera::vec2{ errera::random::getReal(-80.0f, -30.0f), 0 }.Rotate(errera::math::degToRad(transform.rotation + errera::random::getReal(-90.0f, 90.0f)));
    particle.color = errera::vec3{ 1.0f, 1.0f, 1.0f };
    particle.lifespan = 0.5f;
    errera::GetEngine().GetParticleSystem().AddParticle(particle);

    bool playerSeen = false;

    Actor* player = owner->scene->GetActorByName<Actor>("player");
    if (player) {
        errera::vec2 direction{ 1, 0 };
        direction = player->transform.position - owner->transform.position;
        direction = direction.Normalized();

        errera::vec2 forward = errera::vec2{ 1,0 }.Rotate(errera::math::degToRad(transform.rotation));
        float angle = errera::math::radToDeg(errera::vec2::AngleBetween(forward, direction));

        playerSeen = angle <= 30;

        if (playerSeen) {
            float angle = errera::vec2::SignedAngleBetween(forward, direction);
            angle = errera::math::sign(angle);
            transform.rotation += errera::math::radToDeg(angle * 5 * dt);
        }
        
    }

    errera::vec2 force = errera::vec2{ 1, 0 }.Rotate(errera::math::degToRad(transform.rotation)) * speed;

    auto* rb = GetComponent<errera::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

    transform.position.x = errera::math::wrap(transform.position.x, 0.0f, (float)errera::GetEngine().GetRenderer().GetWidth());
    transform.position.y = errera::math::wrap(transform.position.y, 0.0f, (float)errera::GetEngine().GetRenderer().GetHeight());

    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;
        errera::Transform missleTransform{ this->transform.position, this->transform.rotation, 0.75f };
        auto rocket = std::make_unique<Rocket>(missleTransform); 
        rocket->speed = 1000.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "enemy";

        // Components
        auto spriteRenderer = std::make_unique<errera::SpriteRenderer>();
        spriteRenderer->textureName = "textures/plasma.png";

        rocket->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<errera::RigidBody>();
        rocket->AddComponent(std::move(rb));

        auto collider = std::make_unique<errera::CircleCollider2D>();
        collider->radius = 10;
        rocket->AddComponent(std::move(collider));

        // Rocket sound
        auto sound = errera::Resources().Get<errera::AudioClip>("audio/cov-fire.wav", errera::GetEngine().GetAudio()).get();
        if (sound) {
            errera::GetEngine().GetAudio().PlaySound(*sound);
        }

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other) {
    if (tag != other->tag) {
        destroyed = true;
        scene->GetGame()->AddPoints(100);
        for (int i = 0; i < 100; i++) {
            errera::Particle particle;
            particle.position = transform.position;
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