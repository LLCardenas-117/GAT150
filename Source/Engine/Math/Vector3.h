#pragma once
#include "Math.h"
#include <cassert>

namespace errera {
	template<typename T>

	struct Vector3 {
		union {
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vector3() = default;
		Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		T operator [] (unsigned int index) const { assert(index < 3); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 3); return (&x)[index]; }

		Vector3 operator + (const Vector3& v) const { return Vector3{ x + v.x, y + v.y, z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ x - v.x, y - v.y, z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ x * v.x, y * v.y, z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ x / v.x, y / v.y, z / v.z }; }

		Vector3 operator + (float s) const { return Vector3{ x + s, y + s, z + s }; }
		Vector3 operator - (float s) const { return Vector3{ x - s, y - s, z - s }; }
		Vector3 operator * (float s) const { return Vector3{ x * s, y * s, z * s }; }
		Vector3 operator / (float s) const { return Vector3{ x / s, y / s, z / s }; }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		Vector3& operator += (float s) { x += s; y += s; z += s; return *this; }
		Vector3& operator -= (float s) { x -= s; y -= s; z -= s; return *this; }
		Vector3& operator *= (float s) { x *= s; y *= s; z *= s; return *this; }
		Vector3& operator /= (float s) { x /= s; y /= s; z /= s; return *this; }

		//square root (x * x + y * y + z * z)

		float LengthSquare() const { return (x * x) + (y * y) + (z * z); }
		float Length() const { return errera::math::sqrtf(LengthSquare()); }
	};

	template <typename T>
	std::ostream& operator << (std::ostream& stream, const Vector3<T>& v) {
		stream << "{" << v.r << ", " << v.g << ", " << v.b << "}";
		return stream;
	}

	template <typename T>
	std::istream& operator >> (std::istream& stream, Vector3<T>& v) {
		char ch = '\0';

		// { r, g, b}

		// {
		if (!(stream >> std::ws >> ch) || ch != '{') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// r
		if (!(stream >> std::ws >> v.r)) {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// ,
		if (!(stream >> std::ws >> ch) || ch != ',') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// g
		if (!(stream >> std::ws >> v.g)) {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// ,
		if (!(stream >> std::ws >> ch) || ch != ',') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// b
		if (!(stream >> std::ws >> v.b)) {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		// }
		if (!(stream >> std::ws >> ch) || ch != '}') {
			stream.setstate(std::ios::failbit);
			return stream;
		};

		return stream;
	}

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}