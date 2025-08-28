#include "../GamePCH.h"
#include "PlayerController.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start() {
	_rigidBody = owner->GetComponent<errera::RigidBody>();
}

void PlayerController::Update(float dt) {
	float dir = 0;
	if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1;
	if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1;

	if (dir != 0) {

		_rigidBody->ApplyForce(errera::vec2{ 1, 0 } * dir * speed);
	}

	if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		_rigidBody->ApplyForce(errera::vec2{ 0, -1 } * 100000);
	}
}

void PlayerController::OnCollision(class errera::Actor* other) {

}

void PlayerController::Read(const errera::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}