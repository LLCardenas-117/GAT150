#include "EnginePCH.h"

#include "Core/StringHelper.h"

namespace errera {
	void EventManager::AddObserver(const Event::id_t& id, IObserver& observer) {
		_observers[tolower(id)].push_back(&observer);
	}

	void EventManager::RemoveObserver(IObserver& observer) {
		IObserver* observerPtr = &observer;

		// Itrerate through all event types
		for (auto& eventType : _observers) {
			// Get list of observers for event type
			auto observers = eventType.second;

			// Remove matching observers from this event type
			std::erase_if(observers, [observerPtr](auto observer) {
				return (observer == observerPtr);
			});
		}
	}

	void EventManager::Notify(const Event& event) {
	}
}

