#include "Rocket.h"

#include "../GamePCH.h"
#include "Engine.h"
#include "Player.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt) {
    errera::vec2 force = errera::vec2{ 1, 0 }.Rotate(errera::math::degToRad(owner->transform.rotation)) * speed;

    auto* rb = owner->GetComponent<errera::RigidBody>();
    if (rb) {
        rb->SetVelocity(force);
    }

    owner->transform.position.x = errera::math::wrap(owner->transform.position.x, 0.0f, (float)errera::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = errera::math::wrap(owner->transform.position.y, 0.0f, (float)errera::GetEngine().GetRenderer().GetHeight());

    float angle = owner->transform.rotation + errera::random::getReal(-30.0f, 30.0f);
    errera::vec2 velocity = errera::vec2{ 1,0 }.Rotate(errera::math::degToRad(angle));
    velocity *= errera::random::getReal(80.0f, 150.0f);

    errera::Particle particle;

    particle.position = owner->transform.position + errera::vec2{ -50, 0 }.Rotate(errera::math::degToRad(owner->transform.rotation));
    particle.velocity = errera::vec2{ errera::random::getReal(-80.0f, -30.0f), 0 }.Rotate(errera::math::degToRad(owner->transform.rotation + errera::random::getReal(-90.0f, 90.0f)));
    particle.color = (owner->tag == "enemy") ? errera::vec3{ 1, 0, 0 } : errera::vec3{ 0, 1, 0 };
    particle.lifespan = 0.5f;
    errera::GetEngine().GetParticleSystem().AddParticle(particle);
}

void Rocket::OnCollision(errera::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;

        /*auto sound = errera::Resources().Get<errera::AudioClip>("audio/explosion.wav", errera::GetEngine().GetAudio()).get();
        if (sound) {
            errera::GetEngine().GetAudio().PlaySound(*sound);
        }*/
    }
}

void Rocket::Read(const errera::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
}
