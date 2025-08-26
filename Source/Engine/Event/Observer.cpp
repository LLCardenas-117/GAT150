#include "Observer.h"

namespace errera {
	IObserver::~IObserver() {
		OBSERVER_REMOVE_SELF;
	}
}