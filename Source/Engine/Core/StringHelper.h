#pragma once

#include <string>

namespace errera {
	inline std::string tolower(const std::string& str) {
		std::string result = str;

		// Convert to lowercase
		for (char& c : result) {
			c = std::tolower(c);
		}

		return result;
	}

	inline std::string toupper(const std::string& str) {
		std::string result = str;

		// Convert to uppercase
		for (char& c : result) {
			c = std::toupper(c);
		}

		return result;
	}

	inline bool equalsIqnoreCase(const std::string& str1, const std::string& str2) {
		if (str1.length() != str2.length()) return false;

		return std::equal(str1.begin(), str1.end(), str2.begin(), [](char a, char b) {
			return (std::tolower(a) == std::tolower(b));
		});
	}
}
