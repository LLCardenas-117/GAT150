#pragma once

#include "Math/Vector2.h"
#include "Math/Math.h"

#include <iostream>
#include <random>

namespace errera::random {
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    inline std::mt19937& generator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    inline void seed(unsigned int value) {
        generator().seed(value);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    inline int getInt(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="max"></param>
    /// <returns></returns>
    inline int getInt(int max) {
        return getInt(0, max - 1);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    inline int getInt() {
        static std::uniform_int_distribution<> dist;
        return dist(generator());
    }

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    template <typename T = float>
    inline T getReal(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="max"></param>
    /// <returns></returns>
    template <typename T = float>
    inline T getReal(T max) {
        return getReal(static_cast<T>(0), static_cast<T>(max));
    }

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <returns></returns>
    template <typename T = float>
    inline T getReal() {
        static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    inline bool getBool() {
        static std::bernoulli_distribution dist(0.5);
        return dist(generator());
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    inline vec2 onUnitCircle() {
        float radians = getReal(math::twoPi);

        return { math::cosf(radians), math::sinf(radians) };
    }
}