#pragma once

//----------------------------------------
// Includes

// Standard library
#include <cstdlib> // NOLINT
#include <iostream>

// BoronMath
#include "BoronMath/GPU/GPUVector4/GPUVector4.h"

//----------------------------------------
struct GPUInt3
{
    int x;
    int y;
    int z;
};

inline std::ostream& operator<<(std::ostream& os, GPUInt3 const& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

inline GPUInt3 operator+(GPUInt3 const& a, GPUInt3 const& b) {
    return {
        .x=a.x + b.x,
        .y=a.y + b.y,
        .z=a.z + b.z
    };
}

inline GPUInt3 operator-(GPUInt3 const& a, GPUInt3 const& b)
{
    return GPUInt3{
        .x=a.x - b.x,
        .y=a.y - b.y,
        .z=a.z - b.z
    };
}

inline GPUInt3 operator*(GPUInt3 const& a, int const scalar)
{
    return GPUInt3{
        .x=a.x * scalar,
        .y=a.y * scalar,
        .z=a.z * scalar
    };
}

inline GPUInt3 operator/(GPUInt3 const& a, int const scalar)
{
    return GPUInt3{
        .x=a.x / scalar,
        .y=a.y / scalar,
        .z=a.z / scalar
    };
}

inline int dot(GPUInt3 const& a, GPUInt3 const& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline int MagnitudeGPUInt3(GPUInt3 const& a, GPUInt3 const& b) {
    auto const dx = std::abs(a.x - b.x);
    auto const dz = std::abs(a.z - b.z);
    auto const dy = std::abs(a.y - b.y);

    return dx + dz + dy;
}

inline void StoreGPUInt3(GPUInt3& Int, GPUVector4 const& vec) {
    Int.x = static_cast<int>(vec.x);
    Int.y = static_cast<int>(vec.y);
    Int.z = static_cast<int>(vec.z);
}