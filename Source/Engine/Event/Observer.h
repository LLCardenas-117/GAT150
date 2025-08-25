#pragma once

namespace errera {
	class IObserver {
	public:
		virtual ~IObserver() = default;

		virtual void OnNotify(const Event& event) = 0;
	};
}