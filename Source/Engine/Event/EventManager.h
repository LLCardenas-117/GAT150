#pragma once

#include "Core/Singleton.h"
#include "Event.h"
#include "Observer.h"

#include <map>

namespace errera {
	class EventManager : public Singleton<EventManager> {
	public:
		void AddObserver(const Event::id_t& id, IObserver& observer);

		void RemoveObserver(IObserver& observer);

		void Notify(const Event& event);

	private:
		std::map<Event::id_t, std::list<IObserver*>> _observers;
	};
}