#include "../GamePCH.h"
#include "FlyingEnemyController.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {
	_rigidBody = owner->GetComponent<errera::RigidBody>();
}

void FlyingEnemyController::Update(float dt) {
	//float dir = 0;

	errera::Actor* player = owner->scene->GetActorByName<errera::Actor>("player");
	if (player) {
		//if (player->transform.position.x < owner->transform.position.x) dir = -1;
		//else dir = 1;
		errera::vec2 direction = player->transform.position - owner->transform.position;
		_rigidBody->ApplyForce(direction.Normalized() * speed);
	}

	//if (dir != 0) {
	//	_rigidBody->ApplyForce(errera::vec2{ 1, 0 } *dir * 500);
	//}
}

void FlyingEnemyController::OnCollision(class errera::Actor* other) {

}

void FlyingEnemyController::Read(const errera::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}