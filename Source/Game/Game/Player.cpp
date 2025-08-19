#include "Player.h"

#include "../GamePCH.h"
#include "Rocket.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt) { //dt = Delta Time
    /*

    //if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_W)) errera::GetEngine().GetAudio().PlaySound("unsc-engine");

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

    auto* rb = GetComponent<errera::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

    transform.position.x = errera::math::wrap(transform.position.x, 0.0f, (float)errera::GetEngine().GetRenderer().GetWidth());
    transform.position.y = errera::math::wrap(transform.position.y, 0.0f, (float)errera::GetEngine().GetRenderer().GetHeight());

    // check fire key pressed
    // spawn rocket with staying to the players position
    fireTimer -= dt;
    if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E) && fireTimer <= 0) {
        fireTimer = fireTime;
        errera::Transform missleTransform{ this->transform.position, this->transform.rotation, 0.75f };
        auto rocket = std::make_unique<Rocket>(missleTransform);
        rocket->speed = 1000.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "player";

        // Components
        auto spriteRenderer = std::make_unique<errera::SpriteRenderer>();
        spriteRenderer->textureName = "textures/unsc-missle.png";

        rocket->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<errera::RigidBody>();
        rocket->AddComponent(std::move(rb));

        auto collider = std::make_unique<errera::CircleCollider2D>();
        collider->radius = 10;
        rocket->AddComponent(std::move(collider));

        // Rocket sound
        auto sound = errera::Resources().Get<errera::AudioClip>("audio/unsc-fire.wav", errera::GetEngine().GetAudio()).get();
        if (sound) {
            errera::GetEngine().GetAudio().PlaySound(*sound);
        }

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
    */
}

void Player::OnCollision(errera::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;
		dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
        
        /*auto sound = errera::Resources().Get<errera::AudioClip>("audio/explosion.wav", errera::GetEngine().GetAudio()).get();
        if (sound) {
            errera::GetEngine().GetAudio().PlaySound(*sound);
        }*/
    }
}
