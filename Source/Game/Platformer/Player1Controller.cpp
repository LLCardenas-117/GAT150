#include "../GamePCH.h"
#include "Player1Controller.h"

FACTORY_REGISTER(Player1Controller)

void Player1Controller::Start() {
	_rigidBody = owner->GetComponent<errera::RigidBody>();
}

void Player1Controller::Update(float dt) {
	auto healthbar = errera::Instantiate("health");
	healthbar->lifespan = dt + .001;
	healthbar->transform.position = owner->transform.position + errera::vec2{ 0, -30 };
	healthbar->transform.scale = 0.1f;

	if (health == 3) {
		healthbar->GetComponent<errera::SpriteRenderer>()->textureName = "textures/full_health.png";
	}
	if (health == 2) {
		healthbar->GetComponent<errera::SpriteRenderer>()->textureName = "textures/2_hit_health.png";
	}
	if (health == 1) {
		healthbar->GetComponent<errera::SpriteRenderer>()->textureName = "textures/1_hit_health.png";
	}

	owner->scene->AddActor(std::move(healthbar));

	float dir = 0;
	auto spriteRenderer = owner->GetComponent<errera::SpriteRenderer>();

	if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1;
	if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1;

	if (dir != 0) {
		_rigidBody->ApplyForce(errera::vec2{ 1, 0 } * dir * speed);
		if (actionOver) {
			owner->GetComponent<errera::Animator>()->Play("run1");
		}
	}

	else if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_W) && actionOver) {
		_rigidBody->ApplyForce(errera::vec2{ 0, -1 } * jump);
		owner->GetComponent<errera::Animator>()->Play("jump1");
		actionOver = false;
	}

	else if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_E) && actionOver) {
		owner->GetComponent<errera::Animator>()->Play("attack1");
		auto hitbox = errera::Instantiate("hitbox");
		hitbox->tag = "player1";
		if (spriteRenderer->flipH) {
			hitbox->transform.position = owner->transform.position + errera::vec2{ -75, -10 };
		}
		else {
			hitbox->transform.position = owner->transform.position + errera::vec2{ 75, -10 };
		}
		owner->scene->AddActor(std::move(hitbox));
		actionOver = false;
	}

	else if (dir == 0 && owner->GetComponent<errera::Animator>()->Over("jump1") || owner->GetComponent<errera::Animator>()->Over("attack1")) {
		owner->GetComponent<errera::Animator>()->Play("idle1");
		actionOver = true;
	}

	if (spriteRenderer) {
		if (errera::math::fabs(_rigidBody->velocity.x) > 0.1f) {
			spriteRenderer->flipH = (_rigidBody->velocity.x < 0);
		}
	}
}

void Player1Controller::OnCollision(class errera::Actor* other) {
	if (other->name == "hitbox" && other->tag == "player2") {
		health--;
		std::cout << health << std::endl;
		if (health == 0) {
			owner->active = false;
		}
	}
}

void Player1Controller::Read(const errera::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}