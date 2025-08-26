#include "Player.h"

#include "../GamePCH.h"
#include "Rocket.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt) { //dt = Delta Time
    //if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_W)) errera::GetEngine().GetAudio().PlaySound("unsc-engine");

    // Engine particle
	errera::Particle particle;

    particle.position = owner->transform.position + errera::vec2{ -50, 0 }.Rotate(errera::math::degToRad(owner->transform.rotation));
    particle.velocity = errera::vec2{ errera::random::getReal(-80.0f, -30.0f), 0 }.Rotate(errera::math::degToRad(owner->transform.rotation + errera::random::getReal(-90.0f, 90.0f)));
	particle.color = errera::vec3{ 1.0f, 1.0f, 1.0f };
	particle.lifespan = 0.5f;
    errera::GetEngine().GetParticleSystem().AddParticle(particle);
    
    // Rotation
    float rotate = 0;
    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;
    
    owner->transform.rotation += (rotate * rotationRate) * dt;

    // Thrust
    float thrust = 0;

    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    errera::vec2 direction{ 1, 0 };
    errera::vec2 force = direction.Rotate(errera::math::degToRad(owner->transform.rotation)) * thrust * speed;

    auto* rb = owner->GetComponent<errera::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

    owner->transform.position.x = errera::math::wrap(owner->transform.position.x, 0.0f, (float)errera::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = errera::math::wrap(owner->transform.position.y, 0.0f, (float)errera::GetEngine().GetRenderer().GetHeight());

    
    // check fire key pressed
    // spawn rocket with staying to the players position
    fireTimer -= dt;
    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E) && fireTimer <= 0) {
        fireTimer = fireTime;
        errera::Transform transform{ owner->transform.position, owner->transform.rotation, 0.75 };

        auto rocket = errera::Instantiate("player-rocket", transform);
        owner->scene->AddActor(std::move(rocket));
    }
}

void Player::OnCollision(errera::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;
        EVENT_NOTIFY(player_dead);
		//dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
        
        /*auto sound = errera::Resources().Get<errera::AudioClip>("audio/explosion.wav", errera::GetEngine().GetAudio()).get();
        if (sound) {
            errera::GetEngine().GetAudio().PlaySound(*sound);
        }*/
    }
}

void Player::Read(const errera::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, rotationRate);
    JSON_READ(value, fireTime);
}
