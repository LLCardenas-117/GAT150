#include "../GamePCH.h"
#include "Player2Controller.h"

FACTORY_REGISTER(Player2Controller)

void Player2Controller::Start() {
	_rigidBody = owner->GetComponent<errera::RigidBody>();
}

void Player2Controller::Update(float dt) {
	auto healthbar = errera::Instantiate("health");
	healthbar->lifespan = dt +.001;
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

	if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) dir = -1;
	if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) dir = +1;

	if (dir != 0) {
		_rigidBody->ApplyForce(errera::vec2{ 1, 0 } * dir * speed);
		if (actionOver) {
			owner->GetComponent<errera::Animator>()->Play("run2");
		}
	}

	else if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_UP) && actionOver) {
		actionOver = false;
		_rigidBody->ApplyForce(errera::vec2{ 0, -1 } * jump);
		owner->GetComponent<errera::Animator>()->Play("jump2");
	}

	else if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_PAGEDOWN) && actionOver) {
		owner->GetComponent<errera::Animator>()->Play("attack2");
		auto hitbox = errera::Instantiate("hitbox");
		hitbox->tag = "player2";
		if (spriteRenderer->flipH) {
			hitbox->transform.position = owner->transform.position + errera::vec2{ -75, -10 };
		}
		else {
			hitbox->transform.position = owner->transform.position + errera::vec2{ 75, -10 };
		}
		owner->scene->AddActor(std::move(hitbox));
		actionOver = false;
	}

	else if (dir == 0 && owner->GetComponent<errera::Animator>()->Over("jump2") || owner->GetComponent<errera::Animator>()->Over("attack2")) {
		owner->GetComponent<errera::Animator>()->Play("idle2");
		actionOver = true;
	}

	if (spriteRenderer) {
		if (errera::math::fabs(_rigidBody->velocity.x) > 0.1f) {
			spriteRenderer->flipH = (_rigidBody->velocity.x < 0);
		}
	}
}

void Player2Controller::OnCollision(class errera::Actor* other) {
	if (other->name == "hitbox" && other->tag == "player1") {
		healthUpdate = false;
		health--;
		std::cout << health << std::endl;
		if (health == 0) {
			owner->active = false;
		}
	}
}

void Player2Controller::Read(const errera::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}