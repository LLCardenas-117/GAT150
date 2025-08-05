#pragma once
#include "Core/StringHelper.h"
#include "Resource.h"

#include <map>
#include <iostream>

namespace errera {
	class ResourceManager {
	public:
		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& name, TArgs&& ... args);

		static ResourceManager& Instance() {
			static ResourceManager instance;
			return instance;
		}

	private:
		//ResourceManager() = default;

	private:
		std::map<std::string, res_t<Resource>> _resources;

	};

	template<typename T, typename ... TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& name, TArgs&& ... args) {
		std::string key = tolower(name);

		auto iter = _resources.find(key);
		// Check if exits
		if (iter != _resources.end()) {
			// Get value in iterator
			auto base = iter->second;
			// Cast to data type T
			auto resource = std::dynamic_pointer_cast<T>(base);

			// Check if case was successful
			if (!resource) {
				std::cerr << "Resource type mismatch: " << key << std::endl;
				return res_t<T>();
			}

			// Return resource
			return resource;
		}

		// Load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(key, std::forward<TArgs>(args)...) == false) {
			std::cerr << "Could not load resource: " << key << std::endl;
			return res_t<T>();
		}

		// Add key to resource manager
		_resources[key] = resource;

		return resource;
	}
}