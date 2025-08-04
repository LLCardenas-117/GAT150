#pragma once
#include "Math.h"
#include <cassert>

namespace errera {
	template<typename T>

	struct Vector2 {
		union {
			struct { T x, y; };
			struct { T u, v; };
		};

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		Vector2& operator += (float s) { x += s; y += s; return *this; }
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

		//square root (x * x + y * y)

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float LengthSquare() const { return (x * x) + (y * y); }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float Length() const { return errera::math::sqrtf(LengthSquare()); }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Vector2 Normalized() const { return *this / Length(); }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float Angle() const { return errera::math::atan2f(y, x); };

		/// <summary>
		/// 
		/// </summary>
		/// <param name="radians"></param>
		/// <returns></returns>
		Vector2 Rotate(float radians) const {
			Vector2 v;

			v.x = x * errera::math::cosf(radians) - y * errera::math::sinf(radians);
			v.y = x * errera::math::sinf(radians) + y * errera::math::cosf(radians);

			return v;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static float Dot(const Vector2& a, const Vector2& b) {
			return a.x * b.x + a.y * b.y;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static float Cross(const Vector2& a, const Vector2& b) {
			return a.x * b.y - a.y * b.x;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static float AngleBetween(const Vector2& a, const Vector2& b) {
			return math::acosf(Dot(a, b));
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static float SignedAngleBetween(const Vector2& a, const Vector2& b) {
			float x = Dot(a, b);
			float y = Cross(a, b);

			return math::atan2f(y, x);
		}
	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}
