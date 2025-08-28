#include "../GamePCH.h"
#include "EnemyController.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {
	_rigidBody = owner->GetComponent<errera::RigidBody>();
}

void EnemyController::Update(float dt) {
	float dir = 0;

	errera::Actor* player = owner->scene->GetActorByName<errera::Actor>("player");
	if (player) {
		if (player->transform.position.x < owner->transform.position.x) dir = -1;
		else dir = 1;
	}

	if (dir != 0) {
		_rigidBody->ApplyForce(errera::vec2{ 1, 0 } * dir * 500);
	}

	// Save for possible multiplayer code
	/*if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) dir = -1;
	if (errera::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) dir = +1;

	if (dir != 0) {

		_rigidBody->ApplyForce(errera::vec2{ 1, 0 } * dir * speed);
	}

	if (errera::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_UP)) {
		_rigidBody->ApplyForce(errera::vec2{ 0, -1 } * 100000);
	}*/
}

void EnemyController::OnCollision(class errera::Actor* other) {

}

void EnemyController::Read(const errera::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}