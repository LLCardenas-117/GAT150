#include "Rocket.h"

#include "Audio/AudioSystem.h"
#include "Core/Random.h"
#include "Engine.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"

void Rocket::Update(float dt) {

    if (tag == "enemy") {
        errera::GetEngine().GetAudio().PlaySound("unsc-fire");
    }
    else if (tag == "player") {
        errera::GetEngine().GetAudio().PlaySound("cov-fire");
    }

    errera::vec2 force = errera::vec2{ 1, 0 }.Rotate(errera::math::degToRad(transform.rotation)) * speed;

    velocity = force;

    transform.position.x = errera::math::wrap(transform.position.x, 0.0f, (float)errera::GetEngine().GetRenderer().GetWidth());
    transform.position.y = errera::math::wrap(transform.position.y, 0.0f, (float)errera::GetEngine().GetRenderer().GetHeight());

    float angle = transform.rotation + errera::random::getReal(-30.0f, 30.0f);
    errera::vec2 velocity = errera::vec2{ 1,0 }.Rotate(errera::math::degToRad(angle));
    velocity *= errera::random::getReal(80.0f, 150.0f);

    errera::Particle particle;

    particle.position = transform.position + errera::vec2{ -50, 0 }.Rotate(errera::math::degToRad(transform.rotation));
    particle.velocity = errera::vec2{ errera::random::getReal(-80.0f, -30.0f), 0 }.Rotate(errera::math::degToRad(transform.rotation + errera::random::getReal(-90.0f, 90.0f)));
    particle.color = (tag == "enemy") ? errera::vec3{ 1, 0, 0 } : errera::vec3{ 0, 1, 0 };
    particle.lifespan = 0.5f;
    errera::GetEngine().GetParticleSystem().AddParticle(particle);

    Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other) {
    if (tag != other->tag) {
        destroyed = true;
        errera::GetEngine().GetAudio().PlaySound("kahboom");
    }
}
