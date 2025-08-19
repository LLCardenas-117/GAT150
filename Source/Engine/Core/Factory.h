#pragma once

#include "Framework/Object.h"
#include "Logger.h"
#include "Singleton.h"
#include "StringHelper.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname) \
class Register##classname {         \
public:                             \
    Register##classname() {         \
        errera::Factory::Instance().Register<classname>(#classname);    \
    }                               \
};                                  \
Register##classname register_instance;

namespace errera {
	class CreatorBase {
	public:
		virtual ~CreatorBase() = default;
		virtual std::unique_ptr<Object> Create() = 0;
	};

	template <typename T>
	requires std::derived_from<T, Object>
	class Creator : public CreatorBase {
	public:
		std::unique_ptr<Object> Create() override {
			return std::make_unique<T>();
		}
	};

	class Factory : public Singleton<Factory> {
	public:
		template <typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template <typename T = Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> _registry;
	};


	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& name) {
		// Make case-insensitive (lowercase)
		std::string key = tolower(name);

		// Add creator to registry
		_registry[key] = std::make_unique<Creator<T>>();

		Logger::Info("{} added to factory.", name);
	}

	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& name) {
		// Make case-insensitive (lowercase)
		std::string key = tolower(name);

		// Look for creator in registry
		auto it = _registry.find(key);
		if (it != _registry.end()) {
			// Found creator, create object
			auto object = it->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if (derived) {
				object.release();
				return std::unique_ptr<T>(derived);
			}

			Logger::Error("Type mismatch factory object: {}", name);
		}
		else {
			Logger::Error("Could not create factory object: {}", name);
		}

		return nullptr;
	}
}