#ifndef BORONMATH_SIMD_COLOR255_H
#define BORONMATH_SIMD_COLOR255_H

//----------------------------------------
// Includes

// Standard library
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <emmintrin.h>
#include <immintrin.h> // NOLINT
#include <iostream>
#include <mmintrin.h>
#include <smmintrin.h>
#include <xmmintrin.h>

//----------------------------------------
// Avoid min/max naming collisions

// TODO: move implementation details to cpp file
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

//----------------------------------------
namespace BML {
class Color255;

using Col255 = Color255;

// NOLINTBEGIN(portability-simd-intrinsics)
class Color255 {
    //alignas(16) int data[4];
    alignas(16) std::array<int, 4> data{};

    void clamp() {
        data[0] = std::max(0, std::min(255, data[0]));
        data[1] = std::max(0, std::min(255, data[1]));
        data[2] = std::max(0, std::min(255, data[2]));
        data[3] = 0;
    }

public:
    //Constructors
    explicit Color255() {
        data[0] = data[1] = data[2] = data[3] = 0;
    }

    explicit Color255(int const xyz) {
        data[0] = data[1] = data[2] = xyz;
        data[3] = 0;
        clamp();
    }

    explicit Color255(int const x, int const y, int const z) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 0;
        clamp();
    }

    explicit Color255(int const* arr) {
        data[0] = arr[0];
        data[1] = arr[1];
        data[2] = arr[2];
        data[3] = 0;
        clamp();
    }

    // Copy/Move
    Color255(Color255 const&) = default;
    Color255(Color255&&) noexcept = default;
    Color255& operator=(Color255 const&) = default;
    Color255& operator=(Color255&&) noexcept = default;
    ~Color255() = default;

    [[nodiscard]] int x() const { return data[0]; }
    [[nodiscard]] int y() const { return data[1]; }
    [[nodiscard]] int z() const { return data[2]; }

    // Operators
    Color255 operator+() const {
        return *this;
    }

    Color255 operator+(int const scalar) const {
        Color255 result;
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128i const b = _mm_set1_epi32(scalar);
        __m128i const sum = _mm_add_epi32(a, b);
        _mm_store_si128(reinterpret_cast<__m128i*>(result.data.data()), sum);
        result.clamp();
        return result;
    }

    Color255 operator+(Color255 const& other) const {
        Color255 result;
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128i const b = _mm_load_si128(reinterpret_cast<__m128i const*>(other.data.data()));
        __m128i const sum = _mm_add_epi32(a, b);
        _mm_store_si128(reinterpret_cast<__m128i*>(result.data.data()), sum);
        result.clamp();
        return result;
    }

    Color255& operator+=(Color255 const& other) {
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128i const b = _mm_load_si128(reinterpret_cast<__m128i const*>(other.data.data()));
        __m128i const sum = _mm_add_epi32(a, b);
        _mm_store_si128(reinterpret_cast<__m128i*>(data.data()), sum);
        clamp();
        return *this;
    }

    //-
    Color255 operator-() const {
        return Color255(-data[0], -data[1], -data[2]);
    }

    Color255 operator-(int const scalar) const {
        Color255 result;
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128i const b = _mm_set1_epi32(scalar);
        __m128i const diff = _mm_sub_epi32(a, b);
        _mm_store_si128(reinterpret_cast<__m128i*>(result.data.data()), diff);
        result.clamp();
        return result;
    }

    Color255 operator-(Color255 const& other) const {
        Color255 result;
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128i const b = _mm_load_si128(reinterpret_cast<__m128i const*>(other.data.data()));
        __m128i const diff = _mm_sub_epi32(a, b);
        _mm_store_si128(reinterpret_cast<__m128i*>(result.data.data()), diff);
        result.clamp();
        return result;
    }

    Color255& operator-=(Color255 const& other) {
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128i const b = _mm_load_si128(reinterpret_cast<__m128i const*>(other.data.data()));
        __m128i const diff = _mm_sub_epi32(a, b);
        _mm_store_si128(reinterpret_cast<__m128i*>(data.data()), diff);
        clamp();
        return *this;
    }

    //*
    Color255 operator*(int const scalar) const {
        Color255 result;
        result.data[0] = data[0] * scalar;
        result.data[1] = data[1] * scalar;
        result.data[2] = data[2] * scalar;
        result.data[3] = 0;
        result.clamp();
        return result;
    }

    Color255 operator*(float const scalar) const {
        Color255 result;
        __m128 const a = _mm_cvtepi32_ps(_mm_load_si128(reinterpret_cast<__m128i const*>(data.data())));
        __m128 const b = _mm_set1_ps(scalar);
        __m128 const prod = _mm_mul_ps(a, b);
        __m128i const prod_int = _mm_cvtps_epi32(prod);
        _mm_store_si128(reinterpret_cast<__m128i*>(result.data.data()), prod_int);
        result.clamp();
        return result;
    }

    Color255 operator*(Color255 const& other) const {
        Color255 result;
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128i const b = _mm_load_si128(reinterpret_cast<__m128i const*>(other.data.data()));
        __m128i const prod = _mm_mullo_epi32(a, b);
        _mm_store_si128(reinterpret_cast<__m128i*>(result.data.data()), prod);
        result.clamp();
        return result;
    }

    Color255& operator*=(Color255 const& other) {
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128i const b = _mm_load_si128(reinterpret_cast<__m128i const*>(other.data.data()));
        __m128i const prod = _mm_mullo_epi32(a, b);
        _mm_store_si128(reinterpret_cast<__m128i*>(data.data()), prod);
        clamp();
        return *this;
    }

    // /
    Color255 operator/(int const scalar) const {
        if (scalar == 0) return Color255(0, 0, 0);
        Color255 result;
        result.data[0] = data[0] / scalar;
        result.data[1] = data[1] / scalar;
        result.data[2] = data[2] / scalar;
        result.data[3] = 0;
        result.clamp();
        return result;
    }

    Color255 operator/(float const scalar) const {
        if (scalar == 0.0f) return Color255(0, 0, 0);
        Color255 result;
        __m128 const a = _mm_cvtepi32_ps(_mm_load_si128(reinterpret_cast<__m128i const*>(data.data())));
        __m128 const b = _mm_set1_ps(scalar);
        __m128 const quot = _mm_div_ps(a, b);
        __m128i const quot_int = _mm_cvtps_epi32(quot);
        _mm_store_si128(reinterpret_cast<__m128i*>(result.data.data()), quot_int);
        result.clamp();
        return result;
    }

    Color255 operator/(Color255 const& other) const {
        Color255 result;
        for (int i = 0; i < 3; i++) {
            if (other.data[i] != 0) {
                result.data[i] = data[i] / other.data[i];
            }
            else {
                result.data[i] = 255;
            }
        }
        result.data[3] = 0;
        result.clamp();
        return result;
    }

    Color255& operator/=(Color255 const& other) {
        for (int i = 0; i < 3; i++) {
            if (other.data[i] != 0) {
                data[i] /= other.data[i];
            }
            else {
                data[i] = 255;
            }
        }
        data[3] = 0;
        clamp();
        return *this;
    }

    bool operator==(Color255 const& other) const {
        return data[0] == other.data[0] &&
            data[1] == other.data[1] &&
            data[2] == other.data[2];
    }

    bool operator!=(Color255 const& other) const {
        return !(*this == other);
    }

    // Util
    [[nodiscard]] float length() const {
        __m128i const int_vec = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128 const a = _mm_cvtepi32_ps(int_vec);
        __m128 const sq = _mm_mul_ps(a, a);

        __m128 sum = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(1, 0, 3, 2)));
        sum = _mm_add_ps(sum, _mm_shuffle_ps(sum, sum, _MM_SHUFFLE(2, 3, 0, 1)));
        float result{};
        _mm_store_ss(&result, sum);
        return std::sqrt(result);
    }

    [[nodiscard]] float lengthSquared() const {
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128 const a_float = _mm_cvtepi32_ps(a);
        __m128 const sq = _mm_mul_ps(a_float, a_float);

        __m128 sum = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(1, 0, 3, 2)));
        sum = _mm_add_ps(sum, _mm_shuffle_ps(sum, sum, _MM_SHUFFLE(2, 3, 0, 1)));
        float result{};
        _mm_store_ss(&result, sum);
        return result;
    }

    void normalize() {
        if (auto const len = length(); len > 0.0f) {
            auto const invLen = 1.0f / len;
            __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
            __m128 const a_float = _mm_cvtepi32_ps(a);
            __m128 const inv = _mm_set1_ps(invLen);
            __m128 const norm_float = _mm_mul_ps(a_float, inv);
            __m128i const norm_int = _mm_cvtps_epi32(norm_float);
            _mm_store_si128(reinterpret_cast<__m128i*>(data.data()), norm_int);
            clamp();
        }
    }

    [[nodiscard]] int dot(Color255 const& other) const {
        __m128i const a = _mm_load_si128(reinterpret_cast<__m128i const*>(data.data()));
        __m128i const b = _mm_load_si128(reinterpret_cast<__m128i const*>(other.data.data()));
        __m128i const prod = _mm_mullo_epi32(a, b);
        std::array<int, 4> temp{};
        _mm_store_si128(reinterpret_cast<__m128i*>(temp.data()), prod);
        return temp[0] + temp[1] + temp[2];
    }

    // Setters
    void set(int const newX, int const newY, int const newZ) {
        data[0] = newX;
        data[1] = newY;
        data[2] = newZ;
        data[3] = 0;
        clamp();
    }

    void set(Color255 const& other) {
        __m128i const v = _mm_load_si128(reinterpret_cast<__m128i const*>(other.data.data()));
        _mm_store_si128(reinterpret_cast<__m128i*>(data.data()), v);
    }

    [[nodiscard]] Color255 cross(Color255 const& other) const {
        return Color255(
            data[1] * other.data[2] - data[2] * other.data[1],
            data[2] * other.data[0] - data[0] * other.data[2],
            data[0] * other.data[1] - data[1] * other.data[0]
        );
    }

    [[nodiscard]] float distance(Color255 const& other) const {
        return (*this - other).length();
    }

    [[nodiscard]] float distanceSquared(Color255 const& other) const {
        return (*this - other).lengthSquared();
    }

    [[nodiscard]] Color255 lerp(Color255 const& other, float const t) const {
        return *this * (1.0f - t) + other * t;
    }

    [[nodiscard]] float angle(Color255 const& other) const {
        auto const dotProduct = static_cast<float>(dot(other));
        auto const lengths = length() * other.length();
        if (lengths < 1e-6f) return 0.0f;
        return std::acos(dotProduct / lengths);
    }

    [[nodiscard]] __m128 to_float() const {
        return _mm_cvtepi32_ps(_mm_load_si128(reinterpret_cast<__m128i const*>(data.data())));
    }

    [[nodiscard]] Color255 projectOnto(Color255 const& onto) const {
        float const ontoLengthSq = onto.lengthSquared();
        if (ontoLengthSq < 1e-6f) return Zero();
        auto const scale = static_cast<float>(dot(onto)) / ontoLengthSq;
        return onto * scale;
    }

    [[nodiscard]] Color255 reflect(Color255 const& normal) const {
        return *this - normal * (2.0f * static_cast<float>(dot(normal)));
    }

    [[nodiscard]] Color255 abs() const {
        return Color255(
            std::abs(data[0]),
            std::abs(data[1]),
            std::abs(data[2])
        );
    }

    [[nodiscard]] Color255 min(Color255 const& other) const {
        return Color255(
            std::min(data[0], other.data[0]),
            std::min(data[1], other.data[1]),
            std::min(data[2], other.data[2])
        );
    }

    [[nodiscard]] Color255 max(Color255 const& other) const {
        return Color255(
            std::max(data[0], other.data[0]),
            std::max(data[1], other.data[1]),
            std::max(data[2], other.data[2])
        );
    }

    [[nodiscard]] int const* data_ptr() const { return data.data(); }
    int* data_ptr() { return data.data(); }

    // Static methods
    static Color255 Zero()
    {
        return Color255{ 0, 0, 0 };
    }
    static Color255 One()
    {
        return Color255{ 255, 255, 255 };
    }
    static Color255 UnitX()
    {
        return Color255{ 255, 0, 0 };
    }
    static Color255 UnitY()
    {
        return Color255{ 0, 255, 0 };
    }
    static Color255 UnitZ()
    {
        return Color255{ 0, 0, 255 };
    }
};
// NOLINTEND(portability-simd-intrinsics)

inline std::ostream& operator<<(std::ostream& os, Color255 const& vec) {
    os << vec.x() << ", " << vec.y() << ", " << vec.z();
    return os;
}
} // namespace BML
#endif // BORONMATH_SIMD_COLOR255_H