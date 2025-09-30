#pragma once

#include <cstdint>
#include <random>

class Random {
public:
    template<typename Type = uint32_t> requires std::is_arithmetic_v<Type>
    static Type get(const Type min, const Type max) {
        if constexpr (std::is_integral_v<Type>) {
            std::uniform_int_distribution<Type> dist(min, max);
            return dist(m_gen);
        } else {
            std::uniform_real_distribution<Type> dist(min, max);
            return dist(m_gen);
        }
    }

private:
    inline static std::random_device m_randDevice;
    inline static std::mt19937 m_gen{m_randDevice()};
};