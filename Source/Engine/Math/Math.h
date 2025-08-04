#pragma once
#include <algorithm>
#include <cmath>

namespace errera::math {
	constexpr float pi = 3.1415926535897932384626433832795f;
	constexpr float twoPi = 2 * pi;
	constexpr float halfPi = pi / 2;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="rad"></param>
	/// <returns></returns>
	constexpr float radToDeg(float rad) { return rad * (180 / pi); }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="deg"></param>
	/// <returns></returns>
	constexpr float degToRad(float deg) { return deg * (pi / 180); }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	constexpr int wrap(int value, int min, int max) {
		//if (value > max) value = value - max;

		int range = max - min; // Calculate range of wrap
		int result = (value - min) % range; // Shift value so range starts at 0
		if (result < 0) result += range; // wrap forward if result is negative (value < min)

		return min + result; // Shift the result back to [min, man) range
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	inline float wrap(float value, float min, float max) {
		float range = max - min; // Calculate range of wrap
		float result = std::fmodf(value - min, range); // Shift value so range starts at 0
		if (result < 0) result += range; // wrap forward if result is negative (value < min)

		return min + result; // Shift the result back to [min, man) range
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="v"></param>
	/// <returns></returns>
	template<typename T>
	inline T sign(T v) {
		return (v < 0) ? (T)-1 : (v > 0) ? (T)1 : (T)0;
	}

	using std::min;
	using std::max;
	using std::clamp;
	using std::sqrt;
	using std::sqrtf;
	using std::sin;
	using std::sinf;
	using std::cos;
	using std::cosf;
	using std::acos;
	using std::acosf;
	using std::atan2;
	using std::atan2f;
}