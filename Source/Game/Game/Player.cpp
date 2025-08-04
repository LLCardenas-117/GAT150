#include "Player.h"

#include "Audio/AudioSystem.h"
#include "Core/Random.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "GameData.h"
#include "Input/InputSystem.h"
#include "Math/Vector3.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Renderer.h"
#include "Rocket.h"
#include "SpaceGame.h"

void Player::Update(float dt) { //dt = Delta Time
    if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_W)) errera::GetEngine().GetAudio().PlaySound("unsc-engine");

    // Engine particle
	errera::Particle particle;

    particle.position = transform.position + errera::vec2{ -50, 0 }.Rotate(errera::math::degToRad(transform.rotation));
    particle.velocity = errera::vec2{ errera::random::getReal(-80.0f, -30.0f), 0 }.Rotate(errera::math::degToRad(transform.rotation + errera::random::getReal(-90.0f, 90.0f)));
	particle.color = errera::vec3{ 1.0f, 1.0f, 1.0f };
	particle.lifespan = 0.5f;
    errera::GetEngine().GetParticleSystem().AddParticle(particle);
    
    // Rotation
    float rotate = 0;
    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;
    
    transform.rotation += (rotate * rotationRate) * dt;

    // Thrust
    float thrust = 0;

    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    errera::vec2 direction{ 1, 0 };
    errera::vec2 force = direction.Rotate(errera::math::degToRad(transform.rotation)) * thrust * speed;

    velocity += force * dt;

    transform.position.x = errera::math::wrap(transform.position.x, 0.0f, (float)errera::GetEngine().GetRenderer().GetWidth());
    transform.position.y = errera::math::wrap(transform.position.y, 0.0f, (float)errera::GetEngine().GetRenderer().GetHeight());

    // check fire key pressed
    // spawn rocket with staying to the players position
    fireTimer -= dt;
    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E) && fireTimer <= 0) {
        fireTimer = fireTime;

        std::shared_ptr<errera::Model> missleModel = std::make_shared<errera::Model>(GameData::playerMisslePoints, errera::vec3{ 1.0f, 0.0f, 0.0f });
        errera::Transform missleTransform{ this->transform.position, this->transform.rotation, 1.5f };
        auto rocket = std::make_unique<Rocket>(missleTransform, missleModel);
        rocket->speed = 1000.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "player";

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
}

void Player::OnCollision(Actor* other) {
    if (tag != other->tag) {
        destroyed = true;
		dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
        errera::GetEngine().GetAudio().PlaySound("kahboom");
    }
}
