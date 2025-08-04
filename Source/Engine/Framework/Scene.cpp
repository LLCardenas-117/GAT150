#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Core/StringHelper.h"

namespace errera {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt"></param>
	void Scene::Update(float dt) {
		// Update all actors
		for (auto& actor : _actors) {
			actor->Update(dt);
		}

		// Remove destroyed actors
		for (auto iter = _actors.begin(); iter != _actors.end();) {
			if ((*iter)->destroyed) {
				iter = _actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		// Check for collisions
		for (auto& actorA : _actors) {
			for (auto& actorB : _actors) {
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				float distance = (actorA->transform.position - actorB->transform.position).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : _actors) {
			actor->Draw(renderer);
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="actor"></param>
	void Scene::AddActor(std::unique_ptr<class Actor> actor) {
		actor->scene = this;
		_actors.push_back(std::move(actor));
	}

	/// <summary>
	/// 
	/// </summary>
	void Scene::RemoveAllActors() {
		_actors.clear();
	}
}